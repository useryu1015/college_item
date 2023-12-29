#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"
#include "delay.h"


#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//???????0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//???????1
#define WK_UP   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//???????2 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP 


/* PB: 4 5 6 7 */

#define BEEP PAout(11)

void KEY_Init(void);
u8 KEY_Scan(u8 mode);



#endif
