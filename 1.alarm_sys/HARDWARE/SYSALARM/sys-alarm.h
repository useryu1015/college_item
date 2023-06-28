#ifndef __SYSALARM_
#define __SYSALARM_
#include "sys.h"

#define UPDATEsec ClockSec
#define UPDATEmin	ClockMin

#define STOP	-1

#define VISIT	1
#define STEAL	2

#define MAXV 20					// ��¼����ʱ����������
#define MAXS 20					// ��¼����ʱ����������

#define BREAKTIME	30		// �ظ���¼���ʱ��	 ��λ������	
#define CLOSETIME	6			// �رվ���ϵͳʱ��  ��λ����


void Time_Init(void);										// ��ʼ����¼ʱ��Ϊ���ա�״̬
void CLOSE_Alarm_System(int time);			// �رվ���ϵͳ time����ʱʱ��
void Write_Time(u8 value);
unsigned int Time_Compare(u8 value, u8 i);
void Alarm_System(int Key);							// ����ϵͳ��
void Show_AlarmTime(void);							// ��ʾ����ʱ�䣻
void Key_Switch(void);									// ��������&�����ƿ��أ�
void LED_Switch(int KEY);
void User_Password(void);								// ����Ա�����֤ϵͳ		6λ����


#endif

