/**********************
* 11/13	
*	按键设置模块
*
**********************/
#include "clock.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
//#include "key4x4.h"


struct timing timings[MAXTIMING];							// 存储闹钟的结构体


/*

// 闹钟设置；
// 暂不考虑日期，暂用过大内存；									/****************************** 11-24 闹钟设置部分！！！！！！！！！*******************************************************************************************
void Alarm_Set(char value, int num)
{
	switch (value)
	{
		case 0: 
			//timings[0].hour = 
			break;
		case 1: 
			
			break;
		case 2: 
			
			break;
		case 3: 
			
			break;
		case 4: 
			
			break;
		case 5: 
			
			break;
		case 6:
			
			break;
		case 7:
			
			break;
	}
	
	
	
}

// 当到达指定时间，反馈1；
// clock: 闹钟结构体；选择；
// 放置于中断函数实时性更强；但XXXX
int Alarm_Switch(u8 clock)
{
	if (timings[clock].hour == ClockHour && timings[clock].min == ClockMin)
		return 1;
	else 
		return 0;
}



// 修改对应时间(value)的值为num;
void Time_Set(char value, int num)
{
	switch (value)
	{
		case 0: 
			ClockHour = (ClockHour % 10) + num * 10;	// 修改小时的十位； 时
			break;
		case 1: 
			ClockHour = (ClockHour / 10) * 10 + num;	// 修改小时的个位；
			break;
		case 2: 
			ClockMin = (ClockMin % 10) + num * 10;		// 修改小时的十位； 分
			break;
		case 3: 
			ClockMin = (ClockMin / 10) * 10 + num;		// 修改小时的十位；
			break;
		case 4: 
			ClockSec = (ClockSec % 10) + num * 10;		// 修改小时的十位；	秒
			break;
		case 5: 
			ClockSec = (ClockSec / 10) * 10 + num;		// 修改小时的十位；
			break;
	}
	
}

// 修改对应日期(value)的值为num;
void Date_Set(char value, int num)
{
	int Year = DateYear / 100;
	Year *= 100;
	
	// 表达式： Year = (DateYear / 100) * 100;
	
	switch (value)
	{
		case 0: 
			DateYear = Year + num * 10 + (DateYear % 10);	// 修改日期的十位；
			break;
		case 1: 
			DateYear = Year + ((DateYear%100)/10)*10 + num;	// 日期 个位；				// 11/14 验证此表达式是否有BUG；*************
			break;
		case 2: 
			DateMonth = (DateMonth % 10) + num * 10;		
			break;
		case 3: 
			DateMonth = (DateMonth / 10) * 10 + num;		
			break;
		case 4: 
			DateDay = (DateDay % 10) + num * 10;		
			break;
		case 5: 
			DateDay = (DateDay / 10) * 10 + num;		
			break;
	}
	
}

// 设置时间——UI界面与控制												//**********************************************11/13************************************
void Menu_Time_Set(void)
{
	int Key16 = 0;
	int MoveY = 0;			// 设置Y轴范围0-5的时间；
	
	printf("设置时间和日期： Day = %d  \r\n",DateDay);
	OLED_Clear(0);
	OLED_ShowString(0,0,"SetTime:",16);
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Time();							// 显示时间
		Move_Point(MoveY, 0);			// 显示箭头
		delay_ms(15);		
		
		switch (Key16)
		{
			case KEY_1: Time_Set(MoveY, 1); MoveY++; break;			// 修改时间(MoveY)的值为1；  // 移动标签到下一个目标；
			case KEY_2: Time_Set(MoveY, 2); MoveY++; break;
			case KEY_3: Time_Set(MoveY, 3); MoveY++; break;
			case KEY_4: Time_Set(MoveY, 4); MoveY++; break;			// 注意： KEY_4 按键反馈的值是5，而并非4； 可修改定义；
			case KEY_5: Time_Set(MoveY, 5); MoveY++; break;
			case KEY_6: Time_Set(MoveY, 9); MoveY++; break;
			case KEY_7: Time_Set(MoveY, 7); MoveY++; break;
			case KEY_8: Time_Set(MoveY, 8); MoveY++; break;
			case KEY_9: Time_Set(MoveY, 9); MoveY++; break;
			case KEY_0: Time_Set(MoveY, 0); MoveY++; break;			// 修改时间(MoveY)的值为0；
			case KEY_A: CLOSE_TIM	break;												// 暂停时间；
			case KEY_B: MoveY++; OLED_Clear8x8(20,5,16,1); break;
			case KEY_C: MoveY--; OLED_Clear8x8(20,5,16,1);	break;
			case KEY_D: OPEN_TIM; GO_HOME break;
			case KEY_ENTER: MoveY++; break;
		}
		
		if (MoveY > 5)MoveY = 0;			// 箭头向标超出范围时，复位；
		if (MoveY < 0)MoveY = 5;
		
		delay_ms(20);
	}
	
	OPEN_TIM												// 使能定时器时钟；
	OLED_Clear(0);									// 清屏函数；
	Show_ChildMenu(0);							// 返回上一级；
}

// 设置日期——UI界面与控制												//**********************************************11/13************************************
void Menu_Date_Set(void)
{
	int Key16 = 0;
	int MoveY = 0;			// 设置Y轴范围0-5的时间；
	
	printf("设置Chile_日期  Day = %d  \r\n",DateDay);
	OLED_Clear(0);
	OLED_ShowString(0,0,"SetDate:",16);
	
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Date(2);						// 显示时间
		Move_Point(MoveY, 1);			// 显示箭头
		delay_ms(10);		
		
		switch (Key16)
		{
			case KEY_1: Date_Set(MoveY, 1); MoveY++; break;			// 修改时间(MoveY)的值为1；  // 移动标签到下一个目标；
			case KEY_2: Date_Set(MoveY, 2); MoveY++; break;
			case KEY_3: Date_Set(MoveY, 3); MoveY++; break;
			case KEY_4: Date_Set(MoveY, 4); MoveY++; break;			// 注意： KEY_4 按键反馈的值是5，而并非4； 可修改定义；
			case KEY_5: Date_Set(MoveY, 5); MoveY++; break;
			case KEY_6: Date_Set(MoveY, 9); MoveY++; break;
			case KEY_7: Date_Set(MoveY, 7); MoveY++; break;
			case KEY_8: Date_Set(MoveY, 8); MoveY++; break;
			case KEY_9: Date_Set(MoveY, 9); MoveY++; break;
			case KEY_0: Date_Set(MoveY, 0); MoveY++; break;			// 修改时间(MoveY)的值为0；
			//case KEY_A: CLOSE_TIM	break;
			case KEY_B: MoveY++; OLED_Clear8x8(20,5,16,1); break;
			case KEY_C: MoveY--; OLED_Clear8x8(20,5,16,1);	break;
			case KEY_D: GO_HOME break;
			case KEY_ENTER: MoveY++; OLED_Clear8x8(20,5,16,1); break;
		}
		
		if (MoveY > 5)MoveY = 0;			// 箭头向标超出范围时，复位；
		if (MoveY < 0)MoveY = 5;
		
		delay_ms(10);
	}
	
	OLED_Clear(0);			// 清屏函数；
	Show_ChildMenu(0);							// 返回上一级；
}




// 设置闹钟——UI界面与控制												//**********************************************11/24************************************
void Menu_Alarm_Set(int value)
{
	int Key16 = 0;
	int MoveY = 0;			// 设置Y轴范围0-5的时间；
	
		// 初始化闹钟参数； // 当前时间；
	timings[value].month = DateMonth;
	timings[value].day = DateDay;
	timings[value].hour = ClockHour;
	timings[value].min = ClockMin;

	printf("设置Chile_闹钟");
	OLED_Clear(0);
	OLED_ShowString(0,0,"Alarm Set: NULL",16);		
	OLED_ShowString(20,2,"TIME",8);		// 24
	OLED_ShowString(73,2,"DATE",8);		// 75
	
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Alarm();
		Move_Point(MoveY, 2);			// 显示箭头
		delay_ms(10);		
		
		switch (Key16)
		{
			case KEY_1: Alarm_Set(MoveY, 1); MoveY++; break;			// 修改时间(MoveY)的值为1；  // 移动标签到下一个目标；
			case KEY_2: Alarm_Set(MoveY, 2); MoveY++; break;
			case KEY_3: Alarm_Set(MoveY, 3); MoveY++; break;
			case KEY_4: Alarm_Set(MoveY, 4); MoveY++; break;			// 注意： KEY_4 按键反馈的值是5，而并非4； 可修改定义；
			case KEY_5: Alarm_Set(MoveY, 5); MoveY++; break;
			case KEY_6: Alarm_Set(MoveY, 9); MoveY++; break;
			case KEY_7: Alarm_Set(MoveY, 7); MoveY++; break;
			case KEY_8: Alarm_Set(MoveY, 8); MoveY++; break;
			case KEY_9: Alarm_Set(MoveY, 9); MoveY++; break;
			case KEY_0: Alarm_Set(MoveY, 0); MoveY++; break;			// 修改时间(MoveY)的值为0；
			case KEY_B: MoveY++; OLED_Clear8x8(20,5,16,1); break;
			case KEY_C: MoveY--; OLED_Clear8x8(20,5,16,1); break;
			case KEY_D: GO_HOME break;
			case KEY_ENTER: OLED_Clear(0); Show_ChildMenu_Alarm(); break;
		}
		
		if (MoveY > 7)MoveY = 0;			// 箭头向标超出范围时，复位；
		if (MoveY < 0)MoveY = 5;
		
		delay_ms(10);
	}
	
	OLED_Clear(0);			// 清屏函数；
	Show_ChildMenu_Alarm();							// 返回上一级；
}


*/