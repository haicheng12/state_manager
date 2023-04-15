#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "state.h"
#include "context.h"

using namespace HsmState;
// 对象工厂
class Factory
{
public:
	static State *CreateState(Context *context, std::string name, std::string parent_name = "")
	{
		State *state = nullptr;
		if (name == "StartState") // 开始状态
		{
			state = new StartState();
		}
		else if (name == "HungerState") // 饥饿状态
		{
			state = new HungerState();
		}
		else if (name == "Dinner") // 晚饭状态
		{
			state = new Dinner();
		}
		else if (name == "DoTheCookingState") // 做饭状态
		{
			state = new DoTheCookingState();
		}
		else if (name == "EatState") // 吃饭状态
		{
			state = new EatState();
		}
		else if (name == "SleepState") // 睡觉状态
		{
			state = new SleepState();
		}
		else if (name == "WorkState") // 工作状态
		{
			state = new WorkState();
		}
		else if (name == "LoafOnAJob") // 摸鱼状态
		{
			state = new LoafOnAJob();
		}

		context->CreateState(state, name, parent_name);
		return state;
	}
};

#endif