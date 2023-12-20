/*****************************************
 * �����˿��Ƴ���
 * 
*****************************************/

/********** ����Ӣ�� *********************
	axle:		��
	angle:	�Ƕ�
	PT(point location): ��λ
	origin:	ԭ��
	object��Ŀ��
	pallet������
*****************************************/

#include "delay.h"
#include "led.h"
#include "usart.h"
#include "stm32f10x_tim.h"
#include "sg90.h"
#include "robot.h"


/****** ȫ�ֱ��� ********/

// �����˵�λ�洢ջ
struct PTInit{
 u8 axle1;
 u8 axle2;
 u8 axle3;
 u8 axle4;
 //u32 null; //mpu ?????? ??????
};


// ��λ����������
struct PT_RobotInit PT[PTSUM];

// ʵʱ�洢�͵��ã���ǰ����ĽǶȣ�
volatile struct PT_RobotInit RealAngle = {90,90,90,90};		



volatile u32 RobotSpeed = 10000;


// which: ѡ��ı�ĵ�λ�� 0~19��0��ԭ���λ����
// ���û����˵�λ��
void Set_RobotPT(u8 which)
{
	PT[which].axle1 = RealAngle.axle1;
	PT[which].axle2 = RealAngle.axle2;
	PT[which].axle3 = RealAngle.axle3;
	PT[which].axle4 = RealAngle.axle4;
}

// ��ʼ����λ �Ƕȣ�   // ������������ axle1Ϊ��1��Ŀ��Ƕȣ�
void Init_RobotPT(u8 which, u8 axle1, u8 axle2, u8 axle3, u8 axle4)
{
	PT[which].axle1 = axle1;
	PT[which].axle2 = axle2;
	PT[which].axle3 = axle3;
	PT[which].axle4 = axle4;
}


// ObjAnghle: Ŀ��Ƕȣ� ��1
// NowAngle�� ��ǰ��ʵʱ�Ƕȣ�
// Speed�� ��ʱ���ã�
// ʹ����1��Ŀ��Ƕ�1����λ��
u8 Enable_axle1(u8 ObjAngle, float Speed)
{
	if(ObjAngle != RealAngle.axle1){
		RealAngle.axle1 += ObjAngle > RealAngle.axle1 ? +1 : -1; 
		ANGLE1(RealAngle.axle1);   // ʹ�ܶ�Ӧ����ת��ÿ��1�ȣ�
		
		//printf("ʹ�� axle1 = %d\r\n", RealAngle.axle1);
		return BUSY;
	}
	else return READY;		// ����Ŀ��λ�ã����������źţ�
}

// ObjAnghle: Ŀ��Ƕȣ� ��1
// NowAngle�� ��ǰ��ʵʱ�Ƕȣ�
// Speed�� ��ʱ���ã�
// ʹ����1��Ŀ��Ƕ�1����λ��
u8 Enable_axle2(u8 ObjAngle, float Speed)
{
	if(ObjAngle != RealAngle.axle2){
		RealAngle.axle2 += ObjAngle > RealAngle.axle2 ? +1 : -1; 
		ANGLE1(RealAngle.axle2);   // ʹ�ܶ�Ӧ����ת��ÿ��1�ȣ�
		
		//printf("ʹ�� axle1 = %d\r\n", RealAngle.axle1);
		return BUSY;
	}
	else return READY;		// ����Ŀ��λ�ã����������źţ�
}

// ObjAnghle: Ŀ��Ƕȣ� ��1
// NowAngle�� ��ǰ��ʵʱ�Ƕȣ�
// Speed�� ��ʱ���ã�
// ʹ����1��Ŀ��Ƕ�1����λ��
u8 Enable_axle3(u8 ObjAngle, float Speed)
{
	if(ObjAngle != RealAngle.axle1){
		RealAngle.axle3 += ObjAngle > RealAngle.axle3 ? +1 : -1; 
		ANGLE1(RealAngle.axle3);   // ʹ�ܶ�Ӧ����ת��ÿ��1�ȣ�
		
		//printf("ʹ�� axle1 = %d\r\n", RealAngle.axle1);
		return BUSY;
	}
	else return READY;		// ����Ŀ��λ�ã����������źţ�
}


// ObjAnghle: Ŀ��Ƕȣ� ��1
// NowAngle�� ��ǰ��ʵʱ�Ƕȣ�
// Speed�� ��ʱ���ã�
// ʹ����1��Ŀ��Ƕ�1����λ��
u8 Enable_axle4(u8 ObjAngle, float Speed)
{
	if(ObjAngle != RealAngle.axle4){
		RealAngle.axle4 += ObjAngle > RealAngle.axle4 ? +1 : -1; 
		ANGLE1(RealAngle.axle4);   // ʹ�ܶ�Ӧ����ת��ÿ��1�ȣ�
		
		//printf("ʹ�� axle4 = %d\r\n", RealAngle.axle1);
		return BUSY;
	}
	else return READY;		// ����Ŀ��λ�ã����������źţ�
}


// ��е���ƶ�������1�����̣�
u8 Module_Pallet1()
{
	u8 status;
	
	
	// step1 ʹ�ܻ����˵�ԭ�㣻
	do
	{
		status = READY;
		
		
		status += Enable_axle1(PT[0].axle1,0);			// ʹ����1 ��ԭ�㣻
//		status += Enable_axle2(PT[0].axle2,0);
//		status += Enable_axle3(PT[0].axle3,0);
//		status += Enable_axle4(PT[0].axle4,0); 

		printf("Ŀ���λ��ԭ�� ״̬��%d \r\n", status);
		printf(" axle1=%d, axle2=%d, \r\n", RealAngle.axle1, RealAngle.axle2);
		
		delay_us(RobotSpeed);				
	}while (!READY);
	
	
	// step2 ʹ�ܻ����˵�pallet1����
	do
	{
		status = READY;
		
		status += Enable_axle1(PT[1].axle1,0);
		
		printf("Ŀ���λ������1\r\n");
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



// �����˸��� ����
//struct Robots{
//	
//	u8 RealAngle[AXLESUM];			// ʵʱ�Ƕȣ�
//	u8 ObjAngle[AXLESUM];;			// Ŀ��Ƕȣ�
////	u8 axle;
////	u8 speed;					
//};
	
//struct Robots robot[PTSUM];		// ������е��PTSUM����λ���ݣ�

//void origin_PT(u8 angle)
//{
//	robot[0].RealAngle[ONE] = angle;
//	//robot[1].RealAngle[ONE] = 180;

//}


// angle: �Ƕ�
// axle����
// ʹ�ܻ�е��
//void Enable_Robot(u8 angle, u8 axle, u8 speed)
//{
//	while (robot[axle].ObjAngle[angle] != robot[axle].RealAngle[angle])
//	{

////		if (robot[axle].ObjAngle[angle] != robot[axle].RealAngle[angle])

//		robot[axle].ObjAngle[angle] > robot[axle].RealAngle[angle] ? robot[axle].RealAngle[angle]++ : robot[axle].RealAngle[angle]--;
//		//robot[axle].ObjAngle[angle] = robot[axle].RealAngle[angle];
//		printf("������ %d \r\n", robot[axle].RealAngle[angle]);
//		
//		ANGLE1(robot[axle].RealAngle[angle]);
//		
//		delay_ms(3);
//	}
//	
//}	















