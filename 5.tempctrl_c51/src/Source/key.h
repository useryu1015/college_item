#ifndef __KEY_H_
#define __KEY_H_

#include "delay.h"

/**********************
���ű�������
***********************/
sbit TOUCH_KEY=P5^4; 	   //����������IO��P5.4
extern uint8 key_state;
extern void KEY_Scan(void);

#endif
