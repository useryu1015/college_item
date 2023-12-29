#ifndef __LED_H_
#define __LED_H_

#include "delay.h"

/*********************************************
引脚别名定义
**********************************************/			
sbit LED_D1=P2^6;		  //用户指示灯D1用IO口P26	
sbit LED_D2=P2^7;     //用户指示灯D2用IO口P27	
sbit LED_D3=P7^2;     //用户指示灯D3用IO口P72	
sbit LED_D4=P7^1;     //用户指示灯D4用IO口P71	

extern void led_on(uint8 led_idx);
extern void led_off(uint8 led_idx);
extern void led_toggle(uint8 led_idx);
extern void leds_on(void);
extern void leds_off(void);
extern void LED_Blink(void);

#endif
