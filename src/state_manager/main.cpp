#include "state_manager/Context.h"
#include "state_manager/State.h"
#include "state_manager/OneDayStateTest.h"
#include "state_manager/Factory.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>

int main()
{
	Context *context = new Context();

	// 创建状态机
	Factory::CreateState(context, "StartState");
	Factory::CreateState(context, "HungerState");
	Factory::CreateState(context, "Dinner");
	Factory::CreateState(context, "DoTheCookingState", "Dinner");
	Factory::CreateState(context, "EatState", "Dinner");
	Factory::CreateState(context, "SleepState");
	Factory::CreateState(context, "WorkState");
	Factory::CreateState(context, "LoafOnAJob");

	// 开始状态机
	context->Start("StartState");

	int time = 0;
	while (run)
	{
		time++;
		std::this_thread::sleep_for(
			std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(10)));

		context->Update();

		// 如果为工作状态，每隔60分钟发出偷懒事件
		if (context->GetCurStateName() == "WorkState" && time % 60 == 0)
		{
			EventData e = EventData((int)belazy);
			context->SendEvent(e);
		}
	}

	if (context)
	{
		delete context;
		context = nullptr;
	}

	std::cout << "状态 关闭" << std::endl;
	return 0;
}