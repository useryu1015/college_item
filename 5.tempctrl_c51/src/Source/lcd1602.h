#ifndef __LCD1602_H_
#define __LCD1602_H_

#include "delay.h"

/**********************
���ű�������
***********************/			
sbit lcd1602_rs=P3^5;        //1602������/ָ��ѡ������� 
sbit lcd1602_rw=P3^4;        //1602�Ķ�д������ 
sbit lcd1602_en=P3^2;        //1602��ʹ�ܿ����� 

extern void lcd_wcom(uint8 com);
extern void lcd_wdat(uint8 dat); 
extern void lcd_init(void);
extern void DisplayOneChar(uint8 X, uint8 Y, uint8 DData);
extern void DisplayListChar(uint8 X, uint8 Y, uint8 code *DData);

#endif
