# state_manager 状态机

```
开发人员：杨工

开发记录：
————2023年4月12日
1、第一个版本，ROS封装

————2023年4月15日
1、添加日志系统

————2023年4月16日
1、精简状态系统，只保留工作状态和睡觉状态，工作状态完成之后马上切换睡觉状态，工作状态中间穿插摸鱼状态
2、日志系统精确到毫秒
```

**程序逻辑**
```
1、整体分为三个状态：工作状态、摸鱼状态、睡觉状态
2、状态机程序开始，先切换到工作状态，工作总时间为10秒
3、工作状态的期间，到了第5秒，切换到摸鱼状态，摸鱼时间为1秒
4、摸鱼状态完成，切换到工作状态，等待工作状态10秒的时间结束，切换睡觉状态
5、一直保持睡觉状态
```
