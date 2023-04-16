#include "state_manager/context.h"
#include "state_manager/state.h"

namespace HSMState
{
	Context::Context() // 连接前后
	{
	}

	Context::~Context() // 连接前后
	{
		if (cur_node_state_.state_ != nullptr)
		{
			cur_node_state_.state_->stop();
		}

		for (auto iter : states_)
		{
			if (iter.second.state_)
			{
				delete iter.second.state_;
				iter.second.state_ = nullptr;
			}
		}
		states_.clear();
	}

	// 开始状态机
	bool Context::start(std::string name)
	{
		std::unordered_map<std::string, NodeState>::iterator iter_map = states_.find(name);
		if (iter_map != states_.end())
		{
			cur_node_state_ = iter_map->second;
			cur_name_ = iter_map->first;
			iter_map->second.state_->start();
		}
		return false;
	}

	// 创建一个状态
	// [in] state 状态对象，在Context销毁时，内部释放state
	// [in] name  状态名称，为空名称为typedname的值
	// [in] father_name 父状态的名称
	// [out] 返回state
	State *Context::createState(State *state, std::string name, std::string father_name)
	{
		NodeState node_state;
		node_state.state_ = state;
		node_state.state_->setContext(this);
		node_state.father_name_ = father_name;
		states_[name] = node_state;
		return state;
	}

	// 更新当前状态
	void Context::update()
	{
		cur_node_state_.state_->update();
	}

	// 同步事件
	// 发送一个事件，提供给root状态和当前状态处理
	// 如果当前状态是子状态，则还会给父状态处理
	void Context::sendEvent(EventData event_data)
	{
		recursiveSend(cur_node_state_, event_data);
	}

	// 异步事件
	void Context::sendAsyncEvent(EventData event_data)
	{
		// todo 待实现
	}

	std::string Context::getCurStateName()
	{
		return cur_name_;
	}

	// 递归send
	void Context::recursiveSend(NodeState &node_state, EventData &event_data)
	{
		EventDeal event_deal = node_state.state_->runEventFunc(event_data);
		if (event_deal == EventDeal::CONTINUE && !node_state.father_name_.empty())
		{
			std::unordered_map<std::string, NodeState>::iterator iter_map = states_.find(node_state.father_name_);
			if (iter_map != states_.end())
			{
				recursiveSend(iter_map->second, event_data);
			}
		}
	}

	void Context::transForState(std::string name)
	{
		std::string str_name = std::string(name);
		std::unordered_map<std::string, NodeState>::iterator iter_map = states_.find(str_name);
		if (iter_map != states_.end())
		{
			// 停止上一个状态
			cur_node_state_.state_->stop();

			// 初始化下一个状态
			cur_node_state_ = iter_map->second;
			cur_name_ = iter_map->first;
			cur_node_state_.state_->start();
		}
	}
}