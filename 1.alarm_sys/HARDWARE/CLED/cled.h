#ifndef __CLED_H
#define __CLED_H
#include "sys.h"


// ��ɫLED��IO�ڶ��壻
#define CLED_RED		PDout(1)		// ��ɫ
#define CLED_GREEN	PDout(3)		// ��ɫ
#define CLED_BLUE		PDout(5)		// ��ɫ

#define RED		1
#define	GREEN	2
#define BLUE	3
#define OFF		0

void CLED_Init(void);						// ��ɫLED�Ƴ�ʼ��
void CLED_Color(int color);			// ѡ�������ɫ


void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_DISABLE(u8 number);
		 				    
#endif


/****** ����ϵͳ˵��(����)��********
1. �����ƣ�
	a. ��������˸ ������ʾ��
	b. �̵Ƴ����� Ĭ����������״ָ̬ʾ��	
		 �ÿ��أ� �����û�ʵʱ����Ҳ�������

************************************/











