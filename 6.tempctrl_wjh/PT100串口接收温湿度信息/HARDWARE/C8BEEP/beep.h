#ifndef __BEEP_H
#define __BEEP_H
#include "stm32f10x.h"
#include "delay.h"


/* ??GPIO?,???PB11 */
#define DHT11_IO 		GPIOB
#define DHT11_PIN		GPIO_Pin_11

#define BEEP PAout(11)

void BEEP_Init(void);

#endif
