#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


// 报警灯
#define LED0 PFout(6)// PB5 HW1状态指示灯；
#define LED1 PFout(8)// PE5	HW2指示灯；
#define LED2 PGout(5)// PG5 室内走廊照明灯；


void LED_Init(void);//初始化
void HW_LED_StateFlag(void);// 红外指示灯状态判断函数；
		 				    
#endif
