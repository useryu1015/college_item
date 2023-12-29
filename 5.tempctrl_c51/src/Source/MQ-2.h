#ifndef __MQ2_H_
#define __MQ2_H_

#include "delay.h"

/**********************
引脚别名定义
***********************/			
sbit Sensor_IN=P3^7; 	   //MQ-2传感器用

extern uint8 MQ2_state;
extern void MQ2_heartbeat(void);

#endif
