#include "led.h"
#include "HC-SR501.h"
#include "usart.h"
#include "cled.h"

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOF, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_ResetBits(GPIOF,GPIO_Pin_6);						 //PB.5 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOF, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOF,GPIO_Pin_8); 						 //PE.5 输出高 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOG, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOG,GPIO_Pin_5); 						 //PG.5 输出高 	
}

// 红外传感器状态指示灯；
// 常亮： 传感器使能状态；			
// 触发方式： 低电平点亮；
void HW_LED_StateFlag(void)
{
	if (HW1 == 1) LED0 = 1;
	else LED0 = 0;
	
	if (HW2 == 1) LED1 = 1;
	else LED1 = 0;
}


/*****  11/30  ******
指示灯常亮： 红外传感器检测到人时；

1. PB5  HW1状态指示灯；
2. PE5  HW2状态指示灯；

3. OLED显示，警报关闭；



********************/





