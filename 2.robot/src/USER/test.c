#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "timer.h" 
//ALIENTEK��ӢSTM32F103������ ʵ��9
//PWM��� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
int main(void)
{					   
	u16 led0pwmval=0;
	u8 dir=1;
	
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
  	
	TIM3_PWM_Init(899,0);	//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
	
   	while(1)
	{
 		delay_ms(10);		// 400*10 ms һ�����䣻
		
		// ʹCCR2�ȵ�������ݼ���
		if(dir)			// ��0��
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
		
		printf("CCR2 ������ %d \r\n", led0pwmval);  // ���ڲ鿴CCRx ��
	}
}


