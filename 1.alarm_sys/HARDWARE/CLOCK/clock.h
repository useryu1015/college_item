#ifndef __CLOCK_H
#define __CLOCK_H
#include "sys.h"
#include "usart.h"
#include "stdbool.h"

#define MAXTIMING 20							// 最大时间点记录数量； 时分秒；

// stm32定时器做时钟有误差；
#define YEAR	2020
#define MONTH	2
#define DAY		21

#define OPEN_TIM	{TIM_Cmd(TIM6,ENABLE);}			// 使能时钟定时器；	
#define CLOSE_TIM	{TIM_Cmd(TIM6,DISABLE);}    // 失能TIMx外设；

#define GO_HOME {OLED_Clear(0); Show_Home();}	// 回到主界面 并清屏；


void ClockInit(void);						// 定时器初始化；	
void clock_NVIC(void);						// 已被 HcInit包含；

/***************** MyFunction *************/
// 显示模块
void Show_Home(void);									// 主界面
void Show_Menu(void);									// 菜单
void Show_ChildMenu(char vaule);			// 子菜单
void Show_Chinese(void);
void Show_Date(u8 value);
void Show_Time(void);	
void Show_Time2(void);


// 时钟更新与设置
void Time_Update(u8 style);      //如果想让时钟正常递增， 此函数必须一直被调用；
void Date_Update(void);
void Menu_Time_Set(void);
void Menu_Date_Set(void);
void Move_Point(char sign, char value);
void Move_Menu_Point(u8 x, u8 y, int value, int ms);

// 闹钟部分
void Show_ChildMenu_Alarm(void);			// 闹钟主控界面
void Set_Alarm_Switch(void);					// 闹钟开关 -- bool sign
void Set_Alarm_Choose(int * value);		// 闹钟选型 -- 0-19 （1-20）
void Show_Alarm(void);								// 显示闹钟 -- 时 分 月份 日期
void Menu_Alarm_Set(int value);				// 闹钟设置界面
void Alarm_Set(char value, int num);	// 闹钟设置函数

/************************ 全局变量 ****************************/
// 时钟参数
extern u16 msCount;
extern u8 ClockHour,
					ClockMin,
					ClockSec;

extern u16 DateYear,
						DateMonth,
						DateDay;

// 用于定时（闹钟）、计时（警报）等；
// 11-24 多个.c文件共享时，不能在.c文件声明？？？ 
struct timing{
	u8 month;
	u8 day;
	u8 hour;
	u8 min;
	bool sign;
	// u8 sec;  // 闹钟不用考虑秒数！！！！
	// char *		// 链表； // 不适合单片机；也不擅长；
};

extern struct timing timings[MAXTIMING];

#endif

