#include "state_manager/context.h"
#include "state_manager/state.h"

namespace HsmState
{
	// 设置时间响应回调函数
	void State::set_event_func(std::function<EventDeal(EventData &)> func)
	{
		event_func_ = func;
	}

	EventDeal State::RunEventFunc(EventData &event_data)
	{
		if (event_func_ == nullptr)
			return keep_on;
		return event_func_(event_data);
	}

	void State::SetContext(Context *context)
	{
		context_ = context;
	}

	void State::TransState(std::string name)
	{
		context_->TransForState(name);
	}
}