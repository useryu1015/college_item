/*****************************************
 * 机器人控制程序
 * 
*****************************************/

/********** 常用英语 *********************
	axle:		轴
	angle:	角度
	PT(point location): 点位
	origin:	原点
	object：目标
	pallet：托盘
*****************************************/

#include "delay.h"
#include "led.h"
#include "usart.h"
#include "stm32f10x_tim.h"
#include "sg90.h"
#include "robot.h"


/****** 全局变量 ********/

// 机器人点位存储栈
struct PTInit{
 u8 axle1;
 u8 axle2;
 u8 axle3;
 u8 axle4;
 //u32 null; //mpu ?????? ??????
};


// 点位数量声明；
struct PT_RobotInit PT[PTSUM];

// 实时存储和调用，当前各轴的角度；
volatile struct PT_RobotInit RealAngle = {90,90,90,90};		



volatile u32 RobotSpeed = 10000;


// which: 选择改变的点位； 0~19：0是原点点位数据
// 设置机器人点位；
void Set_RobotPT(u8 which)
{
	PT[which].axle1 = RealAngle.axle1;
	PT[which].axle2 = RealAngle.axle2;
	PT[which].axle3 = RealAngle.axle3;
	PT[which].axle4 = RealAngle.axle4;
}

// 初始化点位 角度；   // 参数名待修正 axle1为轴1的目标角度；
void Init_RobotPT(u8 which, u8 axle1, u8 axle2, u8 axle3, u8 axle4)
{
	PT[which].axle1 = axle1;
	PT[which].axle2 = axle2;
	PT[which].axle3 = axle3;
	PT[which].axle4 = axle4;
}


// ObjAnghle: 目标角度； 轴1
// NowAngle： 当前、实时角度；
// Speed： 暂时不用；
// 使能轴1到目标角度1个单位；
u8 Enable_axle1(u8 ObjAngle, float Speed)
{
	if(ObjAngle != RealAngle.axle1){
		RealAngle.axle1 += ObjAngle > RealAngle.axle1 ? +1 : -1; 
		ANGLE1(RealAngle.axle1);   // 使能对应轴旋转；每次1度；
		
		//printf("使能 axle1 = %d\r\n", RealAngle.axle1);
		return BUSY;
	}
	else return READY;		// 到达目标位置，反馈就绪信号；
}

// ObjAnghle: 目标角度； 轴1
// NowAngle： 当前、实时角度；
// Speed： 暂时不用；
// 使能轴1到目标角度1个单位；
u8 Enable_axle2(u8 ObjAngle, float Speed)
{
	if(ObjAngle != RealAngle.axle2){
		RealAngle.axle2 += ObjAngle > RealAngle.axle2 ? +1 : -1; 
		ANGLE1(RealAngle.axle2);   // 使能对应轴旋转；每次1度；
		
		//printf("使能 axle1 = %d\r\n", RealAngle.axle1);
		return BUSY;
	}
	else return READY;		// 到达目标位置，反馈就绪信号；
}

// ObjAnghle: 目标角度； 轴1
// NowAngle： 当前、实时角度；
// Speed： 暂时不用；
// 使能轴1到目标角度1个单位；
u8 Enable_axle3(u8 ObjAngle, float Speed)
{
	if(ObjAngle != RealAngle.axle1){
		RealAngle.axle3 += ObjAngle > RealAngle.axle3 ? +1 : -1; 
		ANGLE1(RealAngle.axle3);   // 使能对应轴旋转；每次1度；
		
		//printf("使能 axle1 = %d\r\n", RealAngle.axle1);
		return BUSY;
	}
	else return READY;		// 到达目标位置，反馈就绪信号；
}


// ObjAnghle: 目标角度； 轴1
// NowAngle： 当前、实时角度；
// Speed： 暂时不用；
// 使能轴1到目标角度1个单位；
u8 Enable_axle4(u8 ObjAngle, float Speed)
{
	if(ObjAngle != RealAngle.axle4){
		RealAngle.axle4 += ObjAngle > RealAngle.axle4 ? +1 : -1; 
		ANGLE1(RealAngle.axle4);   // 使能对应轴旋转；每次1度；
		
		//printf("使能 axle4 = %d\r\n", RealAngle.axle1);
		return BUSY;
	}
	else return READY;		// 到达目标位置，反馈就绪信号；
}


// 机械臂移动到托盘1的流程；
u8 Module_Pallet1()
{
	u8 status;
	
	
	// step1 使能机器人到原点；
	do
	{
		status = READY;
		
		
		status += Enable_axle1(PT[0].axle1,0);			// 使能轴1 到原点；
//		status += Enable_axle2(PT[0].axle2,0);
//		status += Enable_axle3(PT[0].axle3,0);
//		status += Enable_axle4(PT[0].axle4,0); 

		printf("目标点位：原点 状态：%d \r\n", status);
		printf(" axle1=%d, axle2=%d, \r\n", RealAngle.axle1, RealAngle.axle2);
		
		delay_us(RobotSpeed);				
	}while (!READY);
	
	
	// step2 使能机器人到pallet1处；
	do
	{
		status = READY;
		
		status += Enable_axle1(PT[1].axle1,0);
		
		printf("目标点位：托盘1\r\n");
		printf(" axle1=%d, axle2=%d, \r\n", RealAngle.axle1, RealAngle.axle2);
		delay_us(RobotSpeed);				
	}while (!READY);
	
	
}

void Enable_Put()
{
	
	
}


void Enable_Get()
{
	
	
}



// 机器人各轴 数据
//struct Robots{
//	
//	u8 RealAngle[AXLESUM];			// 实时角度；
//	u8 ObjAngle[AXLESUM];;			// 目标角度；
////	u8 axle;
////	u8 speed;					
//};
	
//struct Robots robot[PTSUM];		// 创建机械手PTSUM个点位数据；

//void origin_PT(u8 angle)
//{
//	robot[0].RealAngle[ONE] = angle;
//	//robot[1].RealAngle[ONE] = 180;

//}


// angle: 角度
// axle：轴
// 使能机械手
//void Enable_Robot(u8 angle, u8 axle, u8 speed)
//{
//	while (robot[axle].ObjAngle[angle] != robot[axle].RealAngle[angle])
//	{

////		if (robot[axle].ObjAngle[angle] != robot[axle].RealAngle[angle])

//		robot[axle].ObjAngle[angle] > robot[axle].RealAngle[angle] ? robot[axle].RealAngle[angle]++ : robot[axle].RealAngle[angle]--;
//		//robot[axle].ObjAngle[angle] = robot[axle].RealAngle[angle];
//		printf("现在是 %d \r\n", robot[axle].RealAngle[angle]);
//		
//		ANGLE1(robot[axle].RealAngle[angle]);
//		
//		delay_ms(3);
//	}
//	
//}	















