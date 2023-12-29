#ifndef __UART_H_
#define __UART_H_

#include "delay.h"
#include <stdio.h>

extern void Uart1_Init(void);
extern void SendDataByUart1(uint8 dat);
extern void SendStringByUart1(uint8 *s);


#endif
