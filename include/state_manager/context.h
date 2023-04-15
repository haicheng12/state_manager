#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "event.h"
#include <string>
#include <unordered_map>
#include <thread>

namespace HSMState
{
	class State;
	struct NodeState
	{
		NodeState &operator=(const NodeState &n)
		{
			state_ = n.state_;
			father_name_ = n.father_name_;
			return *this;
		}
		State *state_;
		std::string father_name_;
	};

	class Context
	{
	public:
		friend class State;

		Context();

		~Context();
		// 开始状态机
		bool start(std::string name);

		// 创建一个状态
		// [in] state 状态对象，在Context销毁时，内部释放state
		// [in] name  状态名称，为空名称为typedname的值
		// [in] father_name 父状态的名称
		// [out] 返回state
		State *createState(State *state, std::string name, std::string father_name = "");

		// 更新当前状态
		void update();

		// 同步事件
		// 发送一个事件，提供给root状态和当前状态处理
		// 如果当前状态是子状态，则还会给父状态处理
		void sendEvent(EventData event_data);

		// 异步事件
		void sendAsyncEvent(EventData event_data);

		// 获取当前状态名称
		std::string getCurStateName();

	private:
		// 状态切换
		void transForState(std::string name);

		// 递归send
		void recursiveSend(NodeState &node_state, EventData &event_data);

		std::unordered_map<std::string, NodeState> states_; // 状态列表
		NodeState cur_node_state_;							// 当前状态名
		std::string cur_name_;

		std::string root_name_; // 根状态名
	};
}

#endif // !STATE_H_
