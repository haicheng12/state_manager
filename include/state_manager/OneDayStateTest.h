#ifndef _ONE_DAY_STATE_TEST_H_
#define _ONE_DAY_STATE_TEST_H_

#include "Context.h"
#include "State.h"
#include "Event.h"
#include <iostream>

using namespace HsmState;
bool run = true;

enum EventS
{
	belazy = 0, // 偷懒事件
};

// 开始状态
class StartState : public State
{
public:
	void start()
	{
		std::cout << "开始状态 开始" << std::endl;
	}

	void stop()
	{
		std::cout << "开始状态 停止" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			TransState("HungerState");
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
		std::cout << "饥饿状态 开始" << std::endl;
	}

	void stop()
	{
		std::cout << "饥饿状态 停止" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			TransState("Dinner");
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
		std::cout << "晚饭状态 开始" << std::endl;
	}

	void stop()
	{
		std::cout << "晚饭状态 停止" << std::endl;
	}

	void update()
	{
		TransState("DoTheCookingState");
	}
};

// 做饭状态
class DoTheCookingState : public State
{
public:
	void start()
	{
		std::cout << "做饭状态 开始" << std::endl;
	}

	void stop()
	{
		std::cout << "做饭状态 停止" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 60)
		{
			TransState("EatState");
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
		std::cout << "吃饭状态 开始" << std::endl;
	}

	void stop()
	{
		std::cout << "吃饭状态 停止" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 5)
		{
			TransState("SleepState");
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
		std::cout << "睡觉状态 开始" << std::endl;
	}

	void stop()
	{
		std::cout << "睡觉状态 停止" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 30)
		{
			TransState("WorkState");
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
		std::cout << "工作状态 开始" << std::endl;

		std::function<EventDeal(EventData &)> func = std::bind(&WorkState::DealEvent, this, std::placeholders::_1);
		;
		set_event_func(func);
	}

	void stop()
	{
		std::cout << "工作状态 停止" << std::endl;
	}

	EventDeal DealEvent(EventData &event_data)
	{
		switch ((EventS)event_data.event_type_)
		{
		case belazy:
			TransState("LoafOnAJob");
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
			run = false;
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
		std::cout << "工作摸鱼状态 开始" << std::endl;
	}

	void stop()
	{
		std::cout << "工作摸鱼状态 停止" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			TransState("WorkState");
		}
	}

	int time = 0;
};

#endif // !_ONE_DAY_STATE_TEST_H