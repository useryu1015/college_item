#ifndef __CLED_H
#define __CLED_H
#include "sys.h"


// 三色LED的IO口定义；
#define CLED_RED		PDout(1)		// 红色
#define CLED_GREEN	PDout(3)		// 绿色
#define CLED_BLUE		PDout(5)		// 蓝色

#define RED		1
#define	GREEN	2
#define BLUE	3
#define OFF		0

void CLED_Init(void);						// 彩色LED灯初始化
void CLED_Color(int color);			// 选择点亮颜色


void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_DISABLE(u8 number);
		 				    
#endif


/****** 警报系统说明(分析)：********
1. 报警灯：
	a. 红蓝灯闪烁 警报提示；
	b. 绿灯常亮： 默认正常工作状态指示；	
		 用开关？ 便于用户实时检测且不常亮；

************************************/











