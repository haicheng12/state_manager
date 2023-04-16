#ifndef _ONE_DAY_STATE_TEST_H_
#define _ONE_DAY_STATE_TEST_H_

#include "context.h"
#include "state.h"
#include "event.h"
#include <iostream>

#include "logger/logger.h"

using namespace Sakura::Logger;
using namespace HSMState;

enum EventS
{
	is_lazy = 0, // 偷懒事件
};

// 开始状态
class StartState : public State
{
public:
	void start()
	{
		info("状态机系统 开始");
	}

	void stop()
	{
		info("状态机系统 停止");
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			transState("HungerState");
		}
	}

	int time = 0;
};

// 饥饿状态
class HungerState : public State
{
public:
	void start()
	{
		info("饥饿状态 开始");
	}

	void stop()
	{
		info("饥饿状态 停止");
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			transState("Dinner");
		}
	}

	int time = 0;
};

// 晚饭状态
class Dinner : public State
{
public:
	void start()
	{
		info("晚饭状态 开始");
	}

	void stop()
	{
		info("晚饭状态 停止")
	}

	void update()
	{
		transState("DoTheCookingState");
	}
};

// 做饭状态
class DoTheCookingState : public State
{
public:
	void start()
	{
		info("做饭状态 开始");
	}

	void stop()
	{
		info("做饭状态 停止");
	}

	void update()
	{
		time++;
		if (time == 60)
		{
			transState("EatState");
		}
	}

	int time = 0;
};

// 吃饭状态
class EatState : public State
{
public:
	void start()
	{
		info("吃饭状态 开始");
	}

	void stop()
	{
		info("吃饭状态 停止");
	}

	void update()
	{
		time++;
		if (time == 5)
		{
			transState("SleepState");
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
		if (time == 30)
		{
			transState("WorkState");
		}
	}

	int time = 0;
};

// 工作状态
class WorkState : public State
{
public:
	void start()
	{
		info("工作状态 开始");

		std::function<EventDeal(EventData &)> func = std::bind(&WorkState::DealEvent, this, std::placeholders::_1);
		;
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
		case is_lazy:
			transState("LoafOnAJob");
			break;
		default:
			break;
		}
		return keep_on;
	}

	void update()
	{
		time++;
		if (time == 180)
		{
			// run = false;
			return;
		}
	}

	int time = 0;
};

// 工作摸鱼状态
class LoafOnAJob : public State
{
public:
	void start()
	{
		time = 0;
		info("工作摸鱼状态 开始");
	}

	void stop()
	{
		info("工作摸鱼状态 停止");
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			transState("WorkState");
		}
	}

	int time = 0;
};

#endif // !_ONE_DAY_STATE_TEST_H