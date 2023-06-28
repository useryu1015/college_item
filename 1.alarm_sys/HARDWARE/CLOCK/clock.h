#ifndef __CLOCK_H
#define __CLOCK_H
#include "sys.h"
#include "usart.h"
#include "stdbool.h"

#define MAXTIMING 20							// ���ʱ����¼������ ʱ���룻

// stm32��ʱ����ʱ������
#define YEAR	2020
#define MONTH	2
#define DAY		21

#define OPEN_TIM	{TIM_Cmd(TIM6,ENABLE);}			// ʹ��ʱ�Ӷ�ʱ����	
#define CLOSE_TIM	{TIM_Cmd(TIM6,DISABLE);}    // ʧ��TIMx���裻

#define GO_HOME {OLED_Clear(0); Show_Home();}	// �ص������� ��������


void ClockInit(void);						// ��ʱ����ʼ����	
void clock_NVIC(void);						// �ѱ� HcInit������

/***************** MyFunction *************/
// ��ʾģ��
void Show_Home(void);									// ������
void Show_Menu(void);									// �˵�
void Show_ChildMenu(char vaule);			// �Ӳ˵�
void Show_Chinese(void);
void Show_Date(u8 value);
void Show_Time(void);	
void Show_Time2(void);


// ʱ�Ӹ���������
void Time_Update(u8 style);      //�������ʱ������������ �˺�������һֱ�����ã�
void Date_Update(void);
void Menu_Time_Set(void);
void Menu_Date_Set(void);
void Move_Point(char sign, char value);
void Move_Menu_Point(u8 x, u8 y, int value, int ms);

// ���Ӳ���
void Show_ChildMenu_Alarm(void);			// �������ؽ���
void Set_Alarm_Switch(void);					// ���ӿ��� -- bool sign
void Set_Alarm_Choose(int * value);		// ����ѡ�� -- 0-19 ��1-20��
void Show_Alarm(void);								// ��ʾ���� -- ʱ �� �·� ����
void Menu_Alarm_Set(int value);				// �������ý���
void Alarm_Set(char value, int num);	// �������ú���

/************************ ȫ�ֱ��� ****************************/
// ʱ�Ӳ���
extern u16 msCount;
extern u8 ClockHour,
					ClockMin,
					ClockSec;

extern u16 DateYear,
						DateMonth,
						DateDay;

// ���ڶ�ʱ�����ӣ�����ʱ���������ȣ�
// 11-24 ���.c�ļ�����ʱ��������.c�ļ����������� 
struct timing{
	u8 month;
	u8 day;
	u8 hour;
	u8 min;
	bool sign;
	// u8 sec;  // ���Ӳ��ÿ���������������
	// char *		// ���� // ���ʺϵ�Ƭ����Ҳ���ó���
};

extern struct timing timings[MAXTIMING];

#endif

