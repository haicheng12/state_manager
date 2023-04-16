#ifndef _ONE_DAY_STATE_TEST_H_
#define _ONE_DAY_STATE_TEST_H_

#include "state_manager/context.h"
#include "state_manager/state.h"
#include "state_manager/event.h"
#include <iostream>

#include "logger/logger.h"

using namespace Sakura::Logger;
using namespace HSMState;

enum EventS
{
	is_lazy = 0, // 偷懒事件
};

bool state_run_ = true;

// 工作状态
class WorkState : public State
{
public:
	void start()
	{
		info("工作状态 开始");
		std::function<EventDeal(EventData &)> func = std::bind(&WorkState::DealEvent, this, std::placeholders::_1);
		setEventFunc(func);
	}

	void stop()
	{
		info("工作状态 停止");
	}

	EventDeal DealEvent(EventData &event_data)
	{
		switch ((EventS)event_data.event_type_)
		{
		case EventS::is_lazy:
			transState("LoafOnAJob");
			break;
		default:
			break;
		}
		return EventDeal::CONTINUE;
	}

	void update()
	{
		time++;
		if (time == 100)
		{
			transState("SleepState");
			time = 0;
		}
	}

	int time = 0;
};

// 摸鱼状态
class LoafOnAJob : public State
{
public:
	void start()
	{
		time = 0;
		info("摸鱼状态 开始");
	}

	void stop()
	{
		info("摸鱼状态 停止");
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			transState("WorkState");
			time = 0;
		}
	}

	int time = 0;
};

// 睡觉状态
class SleepState : public State
{
public:
	void start()
	{
		info("睡觉状态 开始");
	}

	void stop()
	{
		info("睡觉状态 停止");
	}

	void update()
	{
		time++;
		if (time == 100)
		{
			transState("WorkState");
			time = 0;
			// state_run_ = false;
		}
	}

	int time = 0;
};

#endif // !_ONE_DAY_STATE_TEST_H