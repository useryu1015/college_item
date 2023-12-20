#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"

#include "beep.h"
#include "led.h"
#include "cled.h"					// ��ɫ��Դ������
#include "oled.h"
#include "key.h"
#include "key4x4.h"				// 16������ģ��
#include "clock.h"				// ʱ��ϵͳ
#include "sys-alarm.h"		// ���⾯��ϵͳ
#include "HC-SR501.h"		  // ������⴫����
#include "rc522.h"				// IC��Ƶ��
#include "speaker.h"			// ����ģ��
#include "ds18b20.h"			// �¶ȴ�����

int main(void)
{
	
	/***��ʼ��Ҳ���ȼ��� Խ��Ҫ�ķ���Խ����*******/
	delay_init();			// ��ʱ������ʼ��	 
	uart_init(115200);		// ���ڳ�ʼ��Ϊ115200
	
	LED_Init();			// ������ ��ʼ��
	CLED_Init();		// ��ɫLED�Ƴ�ʼ��
	OLED_Init();		// OLED��ʾ ��ʼ��
	ClockInit();		// ʱ�ӳ�ʼ��
	HCSR501_Init();		// ������⴫���� ��ʼ��
	KEY4x4_Init();		// ���󰴼�IO�ڳ�ʼ��
	KEY_Init();			// ������ʼ��
	Time_Init();		// ��ʼ����¼ʱ��Ϊ���ա�״̬
	RC522_Init();		// ��ƵIC����ʼ��
	DS18B20_Init();		// �¶ȴ�������ʼ��
	SPEAK_Init();		// ����ģ���ʼ��
	BEEP_Init();		// ��������ʼ��
	
	TIM3_Int_Init(4999-3000,7199);			//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  // 0.5s һ��ת���� 
	
	OLED_Clear(0);									// ����
	
	while (1)
	{		
		Show_Home();
	}
	
}

