#include "state_manager/context.h"
#include "state_manager/state.h"

namespace HSMState
{
	// 设置时间响应回调函数
	void State::setEventFunc(std::function<EventDeal(EventData &)> func)
	{
		event_func_ = func;
	}

	EventDeal State::runEventFunc(EventData &event_data)
	{
		if (event_func_ == nullptr)
			return keep_on;
		return event_func_(event_data);
	}

	void State::setContext(Context *context)
	{
		context_ = context;
	}

	void State::transState(std::string name)
	{
		context_->transForState(name);
	}
}