#ifndef __LED_H_
#define __LED_H_

#include "delay.h"

/*********************************************
���ű�������
**********************************************/			
sbit LED_D1=P2^6;		  //�û�ָʾ��D1��IO��P26	
sbit LED_D2=P2^7;     //�û�ָʾ��D2��IO��P27	
sbit LED_D3=P7^2;     //�û�ָʾ��D3��IO��P72	
sbit LED_D4=P7^1;     //�û�ָʾ��D4��IO��P71	

extern void led_on(uint8 led_idx);
extern void led_off(uint8 led_idx);
extern void led_toggle(uint8 led_idx);
extern void leds_on(void);
extern void leds_off(void);
extern void LED_Blink(void);

#endif
