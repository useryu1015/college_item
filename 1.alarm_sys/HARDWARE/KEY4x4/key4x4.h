#ifndef __KEY4x4_H
#define __KEY4x4_H	 
#include "sys.h"

#define KEY_X(X)	PEin(X)				// ��������ʹ��PD����GPIO��������ֲ��
#define KEY_Y(Y)	PEout(Y)

#define ALL_DOWN_KEY_Y	{	KEY_Y(11) = 0; KEY_Y(12) = 0; KEY_Y(13) = 0; KEY_Y(14) = 0;}

// 4X4��������
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
 
void KEY4x4_Init(void);		// IO�ڳ�ʼ��
u8 KEY4x4_Scan(void);  		// ���󰴼���������	// ������������󰴼�ʹ�ã���
u8 KEY16_Scan(void);

/**************
����ɨ�跽������
����ʹ��8������IO�ڣ� ������IO��һ�˽�VCC/VSS��

�����ܣ�	
	ɨ����������IO�������/�͵�ƽ��VCC/VSS
	���ݶ�Ӧ���꣬return��Ӧ��ţ�
	
// 4X4��������2
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
