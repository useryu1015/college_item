#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


// ������
#define LED0 PFout(6)// PB5 HW1״ָ̬ʾ�ƣ�
#define LED1 PFout(8)// PE5	HW2ָʾ�ƣ�
#define LED2 PGout(5)// PG5 �������������ƣ�


void LED_Init(void);//��ʼ��
void HW_LED_StateFlag(void);// ����ָʾ��״̬�жϺ�����
		 				    
#endif
