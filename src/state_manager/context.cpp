#include "state_manager/context.h"
#include "state_manager/state.h"

namespace HsmState
{
	Context::Context()
	{
	}

	Context::~Context()
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
	bool Context::Start(std::string name)
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
	State *Context::CreateState(State *state, std::string name, std::string father_name)
	{
		NodeState node_state;
		node_state.state_ = state;
		node_state.state_->SetContext(this);
		node_state.father_name_ = father_name;
		states_[name] = node_state;
		return state;
	}

	// 更新当前状态
	void Context::Update()
	{
		cur_node_state_.state_->update();
	}

	// 同步事件
	// 发送一个事件，提供给root状态和当前状态处理
	// 如果当前状态是子状态，则还会给父状态处理
	void Context::SendEvent(EventData event_data)
	{
		RecursiveSend(cur_node_state_, event_data);
	}

	// 异步事件
	void Context::SendAsyncEvent(EventData event_data)
	{
		// todo 待实现
	}

	std::string Context::GetCurStateName()
	{
		return cur_name_;
	}

	// 递归send
	void Context::RecursiveSend(NodeState &node_state, EventData &event_data)
	{
		EventDeal event_deal = node_state.state_->RunEventFunc(event_data);
		if (event_deal == keep_on && !node_state.father_name_.empty())
		{
			std::unordered_map<std::string, NodeState>::iterator iter_map = states_.find(node_state.father_name_);
			if (iter_map != states_.end())
			{
				RecursiveSend(iter_map->second, event_data);
			}
		}
	}

	void Context::TransForState(std::string name)
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