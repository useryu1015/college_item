#ifndef __HCSR501_H
#define __HCSR501_H	
#include "sys.h"

// ������⴫����
#define HW1 PCin(0)		// PC0  ����
#define HW2 PCin(4)		// PC4	����

extern int HW_Sign;


void HCSR501_Init(void);
void HW_Scan(void);

#endif 

