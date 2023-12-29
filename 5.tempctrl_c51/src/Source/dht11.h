#ifndef __DHT11_H__
#define __DHT11_H__

#include "delay.h"	
#include <string.h>           // �����ͷ�ļ���?,��ʹ��strstr�⺯��

/**********************
���ű�������
***********************/	
sbit DATA_PIN=P7^0;       //DHT11�������ţ������ű������������?


typedef struct DHT11_VALUE 
{
    uint8  tempH;  //�¶ȸ��ֽڣ�ʮλ��
    uint8  tempL;  //�¶ȵ�λ�ڣ���λ��
    uint8  humyH;  //ʪ�ȸ��ֽڣ�ʮλ��
    uint8  humyL;  //ʪ�ȸ��ֽڣ���λ��

}DHT11VALUE;

extern void Read_DHT11(void);        //��ʪ�ȴ���������      
extern void DHT11_TEST(void);        //����ʵʱ��ʾ��ʪ��
extern DHT11VALUE DHT11Value;
#endif 