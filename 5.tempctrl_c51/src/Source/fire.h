#ifndef __FIRE_H_
#define __FIRE_H_

#include "delay.h"

/**********************
引脚别名定义
***********************/			
sbit Sensor_IN2=P3^6; 	   //MQ-2传感器用           // ques: choose pin

extern uint8 fire_state;
extern void fire_heartbeat(void);

#endif
