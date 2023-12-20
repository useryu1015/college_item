#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "timer.h" 
//ALIENTEK精英STM32F103开发板 实验9
//PWM输出 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
int main(void)
{					   
	u16 led0pwmval=0;
	u8 dir=1;
	
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200);	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
  	
	TIM3_PWM_Init(899,0);	//不分频。PWM频率=72000/(899+1)=80Khz
	
   	while(1)
	{
 		delay_ms(10);		// 400*10 ms 一次跳变；
		
		// 使CCR2先递增；后递减；
		if(dir)			// 非0；
			led0pwmval++;
		else 
			led0pwmval--;	 
		
 		if(led0pwmval>400)
			dir=0;
		if(led0pwmval==0)
			dir=1;	   			

			if(led0pwmval < 30)
				delay_ms(100);
		
		LED0_PWM_VAL = led0pwmval;	 		//  CCR2
		
		printf("CCR2 现在是 %d \r\n", led0pwmval);  // 串口查看CCRx ；
	}
}


