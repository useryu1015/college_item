#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"

#include "beep.h"
#include "led.h"
#include "cled.h"					// 多色光源二极管
#include "oled.h"
#include "key.h"
#include "key4x4.h"				// 16键按键模块
#include "clock.h"				// 时钟系统
#include "sys-alarm.h"		// 红外警报系统
#include "HC-SR501.h"		  // 人体红外传感器
#include "rc522.h"				// IC射频卡
#include "speaker.h"			// 语音模块
#include "ds18b20.h"			// 温度传感器

int main(void)
{
	
	/***初始化也优先级： 越重要的放在越后面*******/
	delay_init();			// 延时函数初始化	 
	uart_init(115200);		// 串口初始化为115200
	
	LED_Init();			// 警报灯 初始化
	CLED_Init();		// 彩色LED灯初始化
	OLED_Init();		// OLED显示 初始化
	ClockInit();		// 时钟初始化
	HCSR501_Init();		// 人体红外传感器 初始化
	KEY4x4_Init();		// 矩阵按键IO口初始化
	KEY_Init();			// 按键初始化
	Time_Init();		// 初始化记录时间为”空“状态
	RC522_Init();		// 射频IC卡初始化
	DS18B20_Init();		// 温度传感器初始化
	SPEAK_Init();		// 语音模块初始化
	BEEP_Init();		// 蜂鸣器初始化
	
	TIM3_Int_Init(4999-3000,7199);			//10Khz的计数频率，计数到5000为500ms  // 0.5s 一次转换； 
	
	OLED_Clear(0);									// 清屏
	
	while (1)
	{		
		Show_Home();
	}
	
}

