#ifndef __RELAY_H_
#define __RELAY_H_

#include "delay.h"

/**********************
引脚别名定义
***********************/			
sbit Sensor_OUT=P2^0; 	   //蜂鸣器用

extern void beep_heartbeat(void);

#endif
