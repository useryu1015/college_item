#ifndef __KEY4x4_H
#define __KEY4x4_H	 
#include "sys.h"

#define KEY_X(X)	PEin(X)				// 尽量避免使用PD以上GPIO，便于移植；
#define KEY_Y(Y)	PEout(Y)

#define ALL_DOWN_KEY_Y	{	KEY_Y(11) = 0; KEY_Y(12) = 0; KEY_Y(13) = 0; KEY_Y(14) = 0;}

// 4X4按键定义
#define KEY_1	1
#define KEY_2	2
#define KEY_3	3
#define KEY_4	5
#define KEY_5	6
#define KEY_6	7
#define KEY_7	9
#define KEY_8	10
#define KEY_9	11
#define KEY_0	14
#define KEY_RETURN	13
#define KEY_ENTER		15
#define KEY_A	4
#define KEY_B	8 
#define KEY_C	12
#define KEY_D	16
 
void KEY4x4_Init(void);		// IO口初始化
u8 KEY4x4_Scan(void);  		// 矩阵按键反馈函数	// 可配置任意矩阵按键使用！！
u8 KEY16_Scan(void);

/**************
按键扫描方案二：
按键使用8个输入IO口， 且所有IO口一端接VCC/VSS；

程序框架：	
	扫描检测哪两个IO口输入高/低电平；VCC/VSS
	根据对应坐标，return对应编号；
	
// 4X4按键定义2
#define KEY_1	1
#define KEY_2	2
#define KEY_3	3
#define KEY_4	4
#define KEY_5	5
#define KEY_6	6
#define KEY_7	7
#define KEY_8	8 
#define KEY_9	9 
#define KEY_0	10
#define KEY_RETURN	11
#define KEY_ENTER		12
#define KEY_A	13
#define KEY_B	14
#define KEY_C	15
#define KEY_D	16
	
**************/

#endif
