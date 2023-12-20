#ifndef __ROBOT_H
#define __ROBOT_H	 

#include "sys.h"

#define READY	0			// 机器人准备就绪；
#define BUSY	1			// 机器人忙碌中...

#define ANGLE1(X) TIM_SetCompare1(TIM3,17500 + X * 2000/180);			// 角度取值范围：  0-180 --> 17500~19500     公式： 17500+ 2000/180 * 角度
#define ANGLE2(X) TIM_SetCompare2(TIM3,17500 + X * 2000/180);			// BUG: 公式带小数，略微影响精度；
#define ANGLE3(X) TIM_SetCompare3(TIM3,17500 + X * 2000/180);
#define ANGLE4(X) TIM_SetCompare4(TIM3,17500 + X * 2000/180);

#define PTSUM	20						// 定义机械手有多少个点位；

#define AXLESUM FOUR										// 定义机械手有多少个轴
enum AXLE{ONE=0,TWO,THREE,FOUR,ALL};		// 枚举定义机械手各个轴

void Init_RobotPT(u8 which, u8 axle1, u8 axle2, u8 axle3, u8 axle4);
u8 Enable_axle1(u8 ObjAngle, float Speed);
void Set_RobotPT(u8 which);
u8 Module_Pallet1();

//extern struct Robots robot;
//void Enable_Robot(u8 angle, u8 axle, u8 speed);
//void origin_PT(u8 angle);

#endif

