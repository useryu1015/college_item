#ifndef __DELAY_H_
#define __DELAY_H_

#define MAIN_Fosc		11059200UL	//定义主时钟
#include	"STC8.H"
#include  "intrins.h"

#define  uint32   unsigned long
#define  uint16   unsigned int  
#define  uint8    unsigned char  

#define  TRUE    1
#define  FALSE   0

#define LED_1          1
#define LED_2          2
#define LED_3          3
#define LED_4          4

extern void delay_ms(uint16 x);
extern void Delay10us(void);	
#endif
