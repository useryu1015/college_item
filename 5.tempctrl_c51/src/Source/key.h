#ifndef __KEY_H_
#define __KEY_H_

#include "delay.h"

/**********************
引脚别名定义
***********************/
sbit TOUCH_KEY=P5^4; 	   //触摸按键用IO口P5.4
extern uint8 key_state;
extern void KEY_Scan(void);

#endif
