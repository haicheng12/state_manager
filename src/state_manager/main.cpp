#include "state_manager/context.h"
#include "state_manager/state.h"
#include "state_manager/one_day_state_test.h"
#include "state_manager/factory.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>

#include <ros/ros.h> //ros头文件

#include "state_manager/logger.h"

using namespace Sakura::Logger;

int main(int argc, char **argv)
{
	// std::cout<<"hello Sakura"<<std::endl;
	Logger::getInstance()->open("/home/ubuntu/log/test.log");
	Logger::getInstance()->setMax(1024);
	// Logger::getInstance()->setLevel(Logger::INFO);
	// Logger::getInstance()->log(Logger::DEBUG,__FILE__,__LINE__,"hello Sakura");
	// Logger::getInstance()->log(Logger::DEBUG,__FILE__,__LINE__,"name is %s,age is %d","旋涡鸣人",18);

	// debug("hello Sakura");
	// debug("name is %s,age is %d", "旋涡鸣人", 18);
	// info("info message");
	// warn("warn message");
	// erro("erro message");
	// fatal("fatal message");

	ros::init(argc, argv, "state_manager");
	ros::NodeHandle n;

	Context *context = new Context();

	// 创建状态机
	Factory::createState(context, "StartState");
	Factory::createState(context, "HungerState");
	Factory::createState(context, "Dinner");
	Factory::createState(context, "DoTheCookingState", "Dinner");
	Factory::createState(context, "EatState", "Dinner");
	Factory::createState(context, "SleepState");
	Factory::createState(context, "WorkState");
	Factory::createState(context, "LoafOnAJob");

	// 开始状态机
	context->start("StartState");

	int time = 0;

	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		time++;

		context->update();

		// 如果为工作状态，每隔60分钟发出偷懒事件
		if (context->getCurStateName() == "WorkState" && time % 60 == 0)
		{
			EventData e = EventData((int)is_lazy);
			context->sendEvent(e);
		}

		ros::spinOnce();
		loop_rate.sleep();
	}

	if (context)
	{
		delete context;
		context = nullptr;
	}

	info("状态 关闭");

	return 0;
}