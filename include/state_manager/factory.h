#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "state.h"
#include "context.h"

using namespace HSMState;
// 对象工厂
class Factory
{
public:
	static State *createState(Context *context, std::string name, std::string parent_name = "")
	{
		State *state = nullptr;

		if (name == "WorkState") // 工作状态
		{
			state = new WorkState();
		}
		else if (name == "LoafOnAJob") // 摸鱼状态
		{
			state = new LoafOnAJob();
		}
		else if (name == "SleepState") // 睡觉状态
		{
			state = new SleepState();
		}
		context->createState(state, name, parent_name);
		return state;
	}
};

#endif