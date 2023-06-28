#include "cled.h"
#include "usart.h"
#include "led.h"
#include "HC-SR501.h"
#include "beep.h"
#include "speaker.h"
#include "sys-alarm.h"

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void CLED_Init(void)
{
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 	//使能PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	//IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					 				//根据设定参数初始化GPIOB.5
	
 GPIO_SetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5);	//PB.5 输出高
}





// 利用定时器中断，达到闪烁效果；	
// 优点：与delay相比不影响主程序执行、不占用主程序；	增加实时性；
// 警报灯IO口：	 PC0 PC4
// 所有灯使用一个定时器控制影响：	
// 1. 同时闪烁，同时翻转； 
// 2. 注意：中断内容过多；
void TIM3_Int_Init(u16 arr,u16 psc)			// 定时器3的中断服务程序；
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //	使能TIMx					 
}


// 定时器3中断服务程序
// 控制警报灯闪烁
// 此中断只控制警报灯闪烁！！！ 不要画蛇添足！！
void TIM3_IRQHandler(void)    // TIM3中断
{
	static int ColorSign = 0;				// 中断变量声明？？？？
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );   //清除TIMx更新中断标志 
			//printf("TIM3_中断服务已执行   \r\n");
			
			if (HW1 == 1)
			{
				CLED_Color((ColorSign==0)?RED:BLUE);			// 显示红蓝双色 翻转；
				ColorSign = !ColorSign;
				
				SPEAK = 1;																// 语音警报使能
			}
			else
			{
				CLED_Color(OFF);					// 关闭
				CLED_Color(GREEN);				// 绿色
				
				SPEAK = 0;								// 关闭语音
			}
				
			if (HW2 == 1 && HW1 == 1)
				BEEP = !BEEP;							// 蜂鸣器翻转警报；
			else
				BEEP = 0;   							// 关闭蜂鸣器；
			
			//Key_Switch();								// 警报开关&照明灯开关； 
			//HW_LED_StateFlag();					// 红外传感器状态指示灯；   // HW使能，IO输出高电平；
			//该函数移动到clock中断函数中；  原因：该中断会依据警报系统自动关闭；
		}
}



// 控制点亮CLED状态(颜色)
// Tips: 永远保持只有一个为低电平！ 避免对led影响；
void CLED_Color(int color)
{
	switch (color)
	{
		case RED: 	CLED_RED = 0;CLED_GREEN = 1;CLED_BLUE = 1; break;
		case GREEN:	CLED_RED = 1;CLED_GREEN = 0;CLED_BLUE = 1; break;
		case BLUE:	CLED_RED = 1;CLED_GREEN = 1;CLED_BLUE = 0; break;
		case OFF: 	CLED_RED = 1;CLED_GREEN = 1;CLED_BLUE = 1; break;
	}
}


//			if (HW_Sign&0x0001)			// 判断 0001位状态；
//				LED0 =! LED0;
//			else
//				LED0 = 1;
//			
//			if (HW_Sign&0x0002)			// 判断 0010位状态；
//				LED1 =! LED1;
//			else
//				LED1 = 1;


// 不用管；
void TIM3_DISABLE(u8 number)
{
	TIM_Cmd(TIM3, DISABLE);  // 失能TIMx
	LED0 = 1;
	LED1 = 1;
}



