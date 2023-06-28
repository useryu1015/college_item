#include "clock.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "key.h"
#include "key4x4.h"
#include "led.h"

u16 msCount = 0;//ms计数			// 计数器的圈数？？

// 万年历-时间
u8 ClockHour = 20,						// volatile 修饰符为什么报错...
		ClockMin = 59,
		ClockSec = 58;

// 万年历-日期
u16 DateYear	= YEAR,
		DateMonth = MONTH,
		DateDay		= DAY;

struct month{
	char mname[15];
	char name3[4];
	int days;
	int month;
};

static struct month months[12] = 
{
		"January" ,   "jan" , 31 , 1 ,
		"February" ,  "feb" , 28 , 2 ,
		"March" ,     "mar" , 31 , 3 ,
		"April" ,     "apr" , 30 , 4 ,
		"May" ,	      "may" , 31 , 5 ,
		"June" ,      "jun" , 30 , 6 ,
		"July" ,      "jul" , 31 , 7 ,
		"August" , 	  "aug" , 31 , 8 ,
		"September" , "sep" , 30 , 9 , 
		"October" ,   "oct" , 31 , 10 ,
		"November" ,  "nov" , 30 , 11 ,
		"December" ,  "dec" , 31 , 12 ,
};


void ClockInit(void)					// 初始化定时器————计数器；			还可用来制作秒表，万年历等；
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //生成用于定时器设置的结构体
	 
		//定时器初始化 使用基本定时器TIM6
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);   //使能对应RCC时钟
		//配置定时器基础结构体
		TIM_DeInit(TIM2);
		TIM_TimeBaseStructure.TIM_Period = (1000-1); //设置在下一个更新事件装入活动的自动重装载寄存器周期的值         计数到1000为1ms
		TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //设置用来作为TIMx时钟频率除数的预分频值  1M的计数频率 1US计数
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//不分频
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位		 
		
		TIM_ClearFlag(TIM6, TIM_FLAG_Update);  			 //清除更新中断，免得一打开中断立即产生中断
		TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);   	 //打开定时器更新中断
		clock_NVIC();
    //TIM_Cmd(TIM6,DISABLE);     	//关闭使能TIMx外设
		TIM_Cmd(TIM6, ENABLE); 			//使能TIMx外设
}
 

//NVIC配置
void clock_NVIC()
{
			NVIC_InitTypeDef NVIC_InitStructure;
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
			NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;         		//选择串口1中断
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  	//抢占式中断优先级设置为1
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         	//响应式中断优先级设置为1
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        			//使能中断
			NVIC_Init(&NVIC_InitStructure);
}
 
//定时器6中断服务程序
void TIM6_IRQHandler(void)   //TIM6中断							// DEBUG？？？ 这个函数是何时运行；被谁调用的；？？     计算圈数的标志？
{
		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
						TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //清除TIMx更新中断标志 
						msCount++;
			
						if (msCount > 998)			// 减少不必要的进程/函数跳转；
						{
							Time_Update(24);			// 防止跳转时，主程序未执行更新；   	// 会增加CPU负担？
							
							if (ClockHour >= 23 && ClockMin >= 58)
								Date_Update();
							
							HW_LED_StateFlag();		// 红外传感器状态指示灯；   // HW使能，IO输出高电平；   /******************/
						}
		}
}

/*********************************************************************************************************************************************************
*
*																					  自定义函数部分
*
*********************************************************************************************************************************************************/


/******************************************
* 时钟更新模块；
* 进制转换；
* 11/23: 该部分已放置于定时器中断；
******************************************/

// 更新时间；
// style: 时钟显示12 / 24 小时 进制选择；
void Time_Update(u8 style)
{
	//static int sign = 0;
	
	if (msCount >= 1000)		// 当计数到1000毫秒时，秒数递增； 
	{
		msCount = 0;
		ClockSec++;
	}
	
	if (ClockSec >= 60)			// 分钟递增；
	{
		ClockSec = 0;
		ClockMin++;
	}
	
	if (ClockMin >= 60)			// 小时递增；
	{
		ClockMin = 0;
		ClockHour++;
	}
	
	if (ClockHour >= style && style == 24)	// 为递增日期做准备；
	{
		ClockHour = 0;				// 其他时间早已被清零；不用再初始化； 
		DateDay++;
	}
	
}

// 更新日期；
void Date_Update(void)
{

// 方案一： 
//	static int Leap_Year = 1;				// 闰年标签；	
//	if (DateYear % 4 == 0)
//	{
//		Leap_Year = 0;							// 关闭下一条判断；
//		
//		if (DateDay > months[DateMonth-1].days + 1)
//			//update...
//	}
		
	//if (DateYear % 4 == 0)
	if((DateYear%4==0&&DateYear%100!=0)||(DateYear%400==0&&DateYear%3200!=0)||DateYear%172800==0)				// 百度的闰年判断方式；
	{
		months[1].days = 29;						// 闰年时，（结构体）2月天数修改为 29；
	}
	else
		months[1].days = 28;
	
	
	if (DateDay > months[DateMonth-1].days)					// 当日期大于当前月的最大天数时，递增月；
	{
		DateDay = 1;
		DateMonth++;
	}
	
	if (DateMonth > 12)
	{
		DateMonth = 1;
		DateYear++;
	}
	
}





// 控制向标 移动；		带闪烁；
// sign: Y坐标的标号；
// value: 修改的功能； 如：
//			 	0. 修改时间；
//				1. 修改日期；
void Move_Point(char sign, char value)
{
	static int num = 0;
	const int row = 2;							// 箭头坐标微调；
	
	// 声明数组成员数据，信息依据时间显示的十位，Y轴坐标；
	const int MoveY[3][8] = {{22,32,48,58,74,84},			
													 {37+row,45+row,63+row,71+row,89+row,97+row},
													 {22+row,32+row,48+row,58+row,73+row,81+row,99+row,107+row}};
	
	num++;
	
//	if (msCount > 500)
//		OLED_ShowString(MoveY[value][sign] -2,5,"^",8);
//	else
//		OLED_Clear8x8(20,5,16,1);						// 11/13 BUG: 不能正常clear ********************************* 11/13 ***********\
	
	if (num % 16 < 10)
		OLED_ShowString(MoveY[value][sign] -2,5,"-",8);
	else
		OLED_Clear8x8(20,5,16,1);	
}

// 界面选择的指示箭头；
// x: 0-127
// y: 0-7
// value： 箭头尺寸； 						// 0X：箭头款式；
// ms: 箭头闪烁频率，单位ms；			// 伪频率： Now只改变了显示与隐含的比例；并非闪烁频率；
// Move_Menu_Point(x,y,1616,0)		// 可以实现 指定位置箭头清零！！！ 实现箭头移动的笨方法；		// 也可以用OLED_Clear8*8 指定位置清零；
void Move_Menu_Point(u8 x, u8 y, int value, int ms)
{
	
	// 尺寸： 8*8
	if (value == 8)
	{
		if (msCount < ms)
			OLED_ShowCHinese8x8(x,y,2);	// 显示大号箭头；8*8
		else
			OLED_ShowCHinese8x8(x,y,0);	// 显示空白..		
	}
	
	
	// 尺寸16*16
	if (value == 161608 || value >= 161600)
	{
		if (msCount < ms)
			OLED_ShowCHinese(x,y,value%100);	// 显示大号箭头；8*8
		else
			OLED_Clear8x8(x,y,2,2);	  	// 显示空白..		
	}
}




/********** 12/15 获取星期值 （正点原子摘抄）********/
//获得现在是星期几
//功能描述:输入公历日期得到星期(只允许1901-2099年)
//输入参数：公历年月日 
//返回值：星期号		
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	 		// 没看懂；

u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// 如果为21世纪,年份数加100  
	if (yearH>19)yearL+=100;
	// 所过闰年数只算1900年之后的  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}



/****************
*
*			END
*
****************/



// 11/15  程序编写风格过于紧凑....   没品；
// 		就是可读性太差；逻辑关系不自然；太乱；.....


























/**************
*
* 其他显示风格
* 滚动时钟：	移动坐标；
*	指针时钟：	创建BMP图，一帧一帧显示；
*
***************/

	

