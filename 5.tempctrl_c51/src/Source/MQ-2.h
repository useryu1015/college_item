#ifndef __MQ2_H_
#define __MQ2_H_

#include "delay.h"

/**********************
���ű�������
***********************/			
sbit Sensor_IN=P3^7; 	   //MQ-2��������

extern uint8 MQ2_state;
extern void MQ2_heartbeat(void);

#endif
