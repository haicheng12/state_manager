#include "state_manager/context.h"
#include "state_manager/state.h"
#include "one_day_state/one_day_state_test.h"
#include "state_manager/factory.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>

#include <ros/ros.h> //ros头文件

#include "logger/logger.h" //日志头文件

using namespace Sakura::Logger;

int main(int argc, char **argv)
{
	// std::cout<<"hello Sakura"<<std::endl;
	Logger::getInstance()->open("/home/ubuntu/log/state_manager.log");
	Logger::getInstance()->setMax(5120000); // log最大存储空间 5M
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
	Factory::createState(context, "WorkState");
	Factory::createState(context, "LoafOnAJob");
	Factory::createState(context, "SleepState");

	// 开始状态机
	context->start("WorkState");

	int time = 0;

	ros::Rate loop_rate(10);

	while (ros::ok())
	{
		if (state_run_)
		{
			time++;

			context->update();

			// 如果为工作状态，每隔一段时间发出偷懒事件
			if (context->getCurStateName() == "WorkState" && time == 50)
			{
				EventData e = EventData((int)EventS::is_lazy);
				context->sendEvent(e);
			}
			if (context->getCurStateName() == "SleepState")
			{
				time = 0;
			}
		}

		ros::spinOnce();
		loop_rate.sleep();
	}

	if (context)
	{
		delete context;
		context = nullptr;
	}

	info("程序关闭");

	return 0;
}