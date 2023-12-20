#ifndef __HCSR501_H
#define __HCSR501_H	
#include "sys.h"

// 人体红外传感器
#define HW1 PCin(0)		// PC0  室外
#define HW2 PCin(4)		// PC4	室内

extern int HW_Sign;


void HCSR501_Init(void);
void HW_Scan(void);

#endif 

