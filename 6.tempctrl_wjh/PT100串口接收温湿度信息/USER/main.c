#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"

#include "DHT11.h"
#include "bmp.h"
#include "oled.h"
#include "sys.h"
#include "clock.h"
#include "beep.h"
#include "key.h"


/*****
	* 当超过以下定义时！（等于同理）
	* 蜂鸣器警报；
	* 可自行DIY数组
	*/
#define MAX_TEMP	20	// 最大温度！！！
#define MIN_TEMP	0	// 最小温度！！！
	
#define MAX_HUMI	80	// 最大湿度
#define MIN_HUMI	60	// 最小湿度


u8 temp = 0,humi = 0;
u8 pt_data[] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};

void sys_control(void);
void monit_sys_init();

// 串口发送数据函数
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{
 
	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);						//发送数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//等待发送完成
	}
 
}

// 接收数据
void recv_PT100(){
	if (usart1Len != 0){
		
		// Usart_SendString(USART1, usart1Buf, 9);
		//if (usart1Buf[3] == 0)		// 获取数据异常， 直接退出
		//	return;
		
		temp = usart1Buf[3];
		usart1Len = 0;						// 重启 接收中断
	}
	
}


// 请求数据 
void get_PT100(){
	int i;
	
	for (i=0; i<9; i++){
		USART_SendData(USART1, pt_data[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		//等待发送完成
	}
	
	delay_ms(10);
	
	recv_PT100();		// 处理PT100 发送来的数据
	
}


int main(void)
{

	monit_sys_init();		// 系统初始化
	
	while (1){
		sys_control();			// 系统程序入口
	}
	
}
	

void task_1000(){
	
	get_PT100();			// 获取温度值，并refresh到temp
	ClockSec++;						// 更新时间的秒数；
	
	// 显示伪日期：					// 可自定义；
	OLED_ShowString(0,0,"2022/06/01",16); 										// 这里设置 时间！！
	// 显示温度：
	OLED_ShowString(25,4,"T:",16); 
	OLED_ShowNum(60,4,temp,2,16);
	
	Time_Update(24);										// 时间更新函数；
	Date_Update();											// 日期更新函数；
}

// 按键函数
void task_50(){
	
		int	key = KEY_Scan(0);
		switch(key)
		{
			case KEY0_PRES:
				temp = 1;
				monit_sys_init();
				break;
			case KEY1_PRES:
				temp = 19;
				break;
			case WKUP_PRES:				
				temp = -5;
				break;
			default:
				//temp = 10;
				delay_ms(10);	
		}
	
}


void sys_control(void){
	
	u32 run_time = 1;
	
	while(1){
		run_time += 1;
		
		if (!(run_time%1)) task_50();
		if (!(run_time%10)) task_1000();
		
		run_time += 1;
		run_time &= 0x7FFF;
		delay_ms(100);
	}
}

// 重启系统函数
void monit_sys_init(){
	
	int i;
	
	delay_init();
	OLED_Init();
	BEEP_Init();			// 蜂鸣器初始化；
	OLED_Clear();			// 清屏函数；
	KEY_Init();				// 按键初始化
	uart_init(9600);		// 初始化串口
	printf("wecome to DHT11");
	
	get_PT100();			// 获取温度值，并refresh到temp
	
	for (i=0; i<3; i++){
		OLED_Clear();			// 清屏函数；
		delay_ms(200);
		OLED_ShowString(20,4,"SYS Init.",16); 
		delay_ms(200);	
		OLED_ShowString(20,4,"SYS Init..",16); 	
		delay_ms(200);		
		OLED_ShowString(20,4,"SYS Init...",16); 		
	}
	
	OLED_Clear();			// 清屏函数；
}
 




























	

