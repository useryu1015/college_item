#ifndef __SYSALARM_
#define __SYSALARM_
#include "sys.h"

#define UPDATEsec ClockSec
#define UPDATEmin	ClockMin

#define STOP	-1

#define VISIT	1
#define STEAL	2

#define MAXV 20					// 记录逗留时间点的最大次数
#define MAXS 20					// 记录警报时间点的最大次数

#define BREAKTIME	30		// 重复记录最短时间	 单位：分钟	
#define CLOSETIME	6			// 关闭警报系统时间  单位：秒


void Time_Init(void);										// 初始化记录时间为”空“状态
void CLOSE_Alarm_System(int time);			// 关闭警报系统 time：延时时间
void Write_Time(u8 value);
unsigned int Time_Compare(u8 value, u8 i);
void Alarm_System(int Key);							// 警报系统；
void Show_AlarmTime(void);							// 显示警报时间；
void Key_Switch(void);									// 警报开关&照明灯开关；
void LED_Switch(int KEY);
void User_Password(void);								// 管理员身份认证系统		6位密码


#endif

