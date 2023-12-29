#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "bmp.h"
#include "oled.h"
#include "sys.h"
#include "clock.h"
#include "beep.h"
#include "key.h"
#include "max6675.h"
#include "led.h"


//u8 temp = 0,humi = 0;
//u8 pt_data[] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};

void sys_control(void);
void monit_sys_init();

int main(void)
{

	
	monit_sys_init();		// 系统初始化

	while(1){
		sys_control();
	}
	
}
	

void task_max66_process(){
	
	int max66 = read_max6675() *100;			// 获取温度值
	u8 tmpH,tmpL;
	
	tmpH = (u8)(max66/100);
	tmpL = (u8)(max66 % 100);		// 获取小数点后两位数
	
	RGB_max66state();			// RGB显示传感器状态
	ClockSec++;						// 更新时间的秒数；
	
	// 显示伪日期：					// 可自定义；
	OLED_ShowString(0,0," MAX6675",16); 										// 这里设置 时间！！
	// 显示温度：
		
	OLED_ShowString(40,2,"Temp:",16); 
	OLED_ShowNum(60,4,tmpH,2,16);
	OLED_ShowString(78,4,".",16);
	if(tmpL==0){
		OLED_ShowString(84,4,"00",16);
	} else{
		OLED_ShowNum(84,4,tmpL,2,16);
	}
	
	
//	Time_Update(24);										// 时间更新函数；
//	Date_Update();											// 日期更新函数；
}

// 按键函数
void task_50(){
	
		int	key = KEY_Scan(0);
		switch(key)
		{
			case KEY0_PRES:
//				temp = 1;
				monit_sys_init();
				break;
			case KEY1_PRES:
//				temp = 19;
				break;
			case WKUP_PRES:				
//				temp = -5;
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
		if (!(run_time%5)) task_max66_process();		// 温控程序
		
		run_time += 1;
		run_time &= 0x7FFF;
		delay_ms(100);
	}

	
}

// 重启 初始化系统函数
void monit_sys_init(){
	
	int i;
	
	delay_init();
	OLED_Init();
	BEEP_Init();				// 蜂鸣器初始化；
	OLED_Clear();			// 清屏函数；
	KEY_Init();				// 按键初始化
	LED_Init();				// RGB INIT
  
	SPI_MAX6675_Init();/* MAX6675 SPI init */

	uart_init(115200);		// 初始化串口
	printf("wecome to max6675 \r\n");
	
	for (i=0; i<2; i++){
		OLED_Clear();			// 清屏函数；
		OLED_ShowString(20,4,"loading",16); 
		delay_ms(200);	
		OLED_ShowString(20,4,"loading.",16); 
		delay_ms(200);			
		OLED_ShowString(20,4,"loading..",16); 	
		delay_ms(200);		
		OLED_ShowString(20,4,"loading...",16);
		delay_ms(200);
	}
	OLED_Clear();			// 清屏函数；
}
 




























	

