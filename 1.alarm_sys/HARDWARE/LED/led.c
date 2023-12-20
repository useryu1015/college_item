#include "led.h"
#include "HC-SR501.h"
#include "usart.h"
#include "cled.h"

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOF, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_ResetBits(GPIOF,GPIO_Pin_6);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOF, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOF,GPIO_Pin_8); 						 //PE.5 ����� 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOG, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOG,GPIO_Pin_5); 						 //PG.5 ����� 	
}

// ���⴫����״ָ̬ʾ�ƣ�
// ������ ������ʹ��״̬��			
// ������ʽ�� �͵�ƽ������
void HW_LED_StateFlag(void)
{
	if (HW1 == 1) LED0 = 1;
	else LED0 = 0;
	
	if (HW2 == 1) LED1 = 1;
	else LED1 = 0;
}


/*****  11/30  ******
ָʾ�Ƴ����� ���⴫������⵽��ʱ��

1. PB5  HW1״ָ̬ʾ�ƣ�
2. PE5  HW2״ָ̬ʾ�ƣ�

3. OLED��ʾ�������رգ�



********************/





