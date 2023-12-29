/**********************
* 11/13	
*	��������ģ��
*
**********************/
#include "clock.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
//#include "key4x4.h"


struct timing timings[MAXTIMING];							// �洢���ӵĽṹ��


/*

// �������ã�
// �ݲ��������ڣ����ù����ڴ棻									/****************************** 11-24 �������ò��֣�����������������*******************************************************************************************
void Alarm_Set(char value, int num)
{
	switch (value)
	{
		case 0: 
			//timings[0].hour = 
			break;
		case 1: 
			
			break;
		case 2: 
			
			break;
		case 3: 
			
			break;
		case 4: 
			
			break;
		case 5: 
			
			break;
		case 6:
			
			break;
		case 7:
			
			break;
	}
	
	
	
}

// ������ָ��ʱ�䣬����1��
// clock: ���ӽṹ�壻ѡ��
// �������жϺ���ʵʱ�Ը�ǿ����XXXX
int Alarm_Switch(u8 clock)
{
	if (timings[clock].hour == ClockHour && timings[clock].min == ClockMin)
		return 1;
	else 
		return 0;
}



// �޸Ķ�Ӧʱ��(value)��ֵΪnum;
void Time_Set(char value, int num)
{
	switch (value)
	{
		case 0: 
			ClockHour = (ClockHour % 10) + num * 10;	// �޸�Сʱ��ʮλ�� ʱ
			break;
		case 1: 
			ClockHour = (ClockHour / 10) * 10 + num;	// �޸�Сʱ�ĸ�λ��
			break;
		case 2: 
			ClockMin = (ClockMin % 10) + num * 10;		// �޸�Сʱ��ʮλ�� ��
			break;
		case 3: 
			ClockMin = (ClockMin / 10) * 10 + num;		// �޸�Сʱ��ʮλ��
			break;
		case 4: 
			ClockSec = (ClockSec % 10) + num * 10;		// �޸�Сʱ��ʮλ��	��
			break;
		case 5: 
			ClockSec = (ClockSec / 10) * 10 + num;		// �޸�Сʱ��ʮλ��
			break;
	}
	
}

// �޸Ķ�Ӧ����(value)��ֵΪnum;
void Date_Set(char value, int num)
{
	int Year = DateYear / 100;
	Year *= 100;
	
	// ���ʽ�� Year = (DateYear / 100) * 100;
	
	switch (value)
	{
		case 0: 
			DateYear = Year + num * 10 + (DateYear % 10);	// �޸����ڵ�ʮλ��
			break;
		case 1: 
			DateYear = Year + ((DateYear%100)/10)*10 + num;	// ���� ��λ��				// 11/14 ��֤�˱��ʽ�Ƿ���BUG��*************
			break;
		case 2: 
			DateMonth = (DateMonth % 10) + num * 10;		
			break;
		case 3: 
			DateMonth = (DateMonth / 10) * 10 + num;		
			break;
		case 4: 
			DateDay = (DateDay % 10) + num * 10;		
			break;
		case 5: 
			DateDay = (DateDay / 10) * 10 + num;		
			break;
	}
	
}

// ����ʱ�䡪��UI���������												//**********************************************11/13************************************
void Menu_Time_Set(void)
{
	int Key16 = 0;
	int MoveY = 0;			// ����Y�᷶Χ0-5��ʱ�䣻
	
	printf("����ʱ������ڣ� Day = %d  \r\n",DateDay);
	OLED_Clear(0);
	OLED_ShowString(0,0,"SetTime:",16);
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Time();							// ��ʾʱ��
		Move_Point(MoveY, 0);			// ��ʾ��ͷ
		delay_ms(15);		
		
		switch (Key16)
		{
			case KEY_1: Time_Set(MoveY, 1); MoveY++; break;			// �޸�ʱ��(MoveY)��ֵΪ1��  // �ƶ���ǩ����һ��Ŀ�ꣻ
			case KEY_2: Time_Set(MoveY, 2); MoveY++; break;
			case KEY_3: Time_Set(MoveY, 3); MoveY++; break;
			case KEY_4: Time_Set(MoveY, 4); MoveY++; break;			// ע�⣺ KEY_4 ����������ֵ��5��������4�� ���޸Ķ��壻
			case KEY_5: Time_Set(MoveY, 5); MoveY++; break;
			case KEY_6: Time_Set(MoveY, 9); MoveY++; break;
			case KEY_7: Time_Set(MoveY, 7); MoveY++; break;
			case KEY_8: Time_Set(MoveY, 8); MoveY++; break;
			case KEY_9: Time_Set(MoveY, 9); MoveY++; break;
			case KEY_0: Time_Set(MoveY, 0); MoveY++; break;			// �޸�ʱ��(MoveY)��ֵΪ0��
			case KEY_A: CLOSE_TIM	break;												// ��ͣʱ�䣻
			case KEY_B: MoveY++; OLED_Clear8x8(20,5,16,1); break;
			case KEY_C: MoveY--; OLED_Clear8x8(20,5,16,1);	break;
			case KEY_D: OPEN_TIM; GO_HOME break;
			case KEY_ENTER: MoveY++; break;
		}
		
		if (MoveY > 5)MoveY = 0;			// ��ͷ��곬����Χʱ����λ��
		if (MoveY < 0)MoveY = 5;
		
		delay_ms(20);
	}
	
	OPEN_TIM												// ʹ�ܶ�ʱ��ʱ�ӣ�
	OLED_Clear(0);									// ����������
	Show_ChildMenu(0);							// ������һ����
}

// �������ڡ���UI���������												//**********************************************11/13************************************
void Menu_Date_Set(void)
{
	int Key16 = 0;
	int MoveY = 0;			// ����Y�᷶Χ0-5��ʱ�䣻
	
	printf("����Chile_����  Day = %d  \r\n",DateDay);
	OLED_Clear(0);
	OLED_ShowString(0,0,"SetDate:",16);
	
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Date(2);						// ��ʾʱ��
		Move_Point(MoveY, 1);			// ��ʾ��ͷ
		delay_ms(10);		
		
		switch (Key16)
		{
			case KEY_1: Date_Set(MoveY, 1); MoveY++; break;			// �޸�ʱ��(MoveY)��ֵΪ1��  // �ƶ���ǩ����һ��Ŀ�ꣻ
			case KEY_2: Date_Set(MoveY, 2); MoveY++; break;
			case KEY_3: Date_Set(MoveY, 3); MoveY++; break;
			case KEY_4: Date_Set(MoveY, 4); MoveY++; break;			// ע�⣺ KEY_4 ����������ֵ��5��������4�� ���޸Ķ��壻
			case KEY_5: Date_Set(MoveY, 5); MoveY++; break;
			case KEY_6: Date_Set(MoveY, 9); MoveY++; break;
			case KEY_7: Date_Set(MoveY, 7); MoveY++; break;
			case KEY_8: Date_Set(MoveY, 8); MoveY++; break;
			case KEY_9: Date_Set(MoveY, 9); MoveY++; break;
			case KEY_0: Date_Set(MoveY, 0); MoveY++; break;			// �޸�ʱ��(MoveY)��ֵΪ0��
			//case KEY_A: CLOSE_TIM	break;
			case KEY_B: MoveY++; OLED_Clear8x8(20,5,16,1); break;
			case KEY_C: MoveY--; OLED_Clear8x8(20,5,16,1);	break;
			case KEY_D: GO_HOME break;
			case KEY_ENTER: MoveY++; OLED_Clear8x8(20,5,16,1); break;
		}
		
		if (MoveY > 5)MoveY = 0;			// ��ͷ��곬����Χʱ����λ��
		if (MoveY < 0)MoveY = 5;
		
		delay_ms(10);
	}
	
	OLED_Clear(0);			// ����������
	Show_ChildMenu(0);							// ������һ����
}




// �������ӡ���UI���������												//**********************************************11/24************************************
void Menu_Alarm_Set(int value)
{
	int Key16 = 0;
	int MoveY = 0;			// ����Y�᷶Χ0-5��ʱ�䣻
	
		// ��ʼ�����Ӳ����� // ��ǰʱ�䣻
	timings[value].month = DateMonth;
	timings[value].day = DateDay;
	timings[value].hour = ClockHour;
	timings[value].min = ClockMin;

	printf("����Chile_����");
	OLED_Clear(0);
	OLED_ShowString(0,0,"Alarm Set: NULL",16);		
	OLED_ShowString(20,2,"TIME",8);		// 24
	OLED_ShowString(73,2,"DATE",8);		// 75
	
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Alarm();
		Move_Point(MoveY, 2);			// ��ʾ��ͷ
		delay_ms(10);		
		
		switch (Key16)
		{
			case KEY_1: Alarm_Set(MoveY, 1); MoveY++; break;			// �޸�ʱ��(MoveY)��ֵΪ1��  // �ƶ���ǩ����һ��Ŀ�ꣻ
			case KEY_2: Alarm_Set(MoveY, 2); MoveY++; break;
			case KEY_3: Alarm_Set(MoveY, 3); MoveY++; break;
			case KEY_4: Alarm_Set(MoveY, 4); MoveY++; break;			// ע�⣺ KEY_4 ����������ֵ��5��������4�� ���޸Ķ��壻
			case KEY_5: Alarm_Set(MoveY, 5); MoveY++; break;
			case KEY_6: Alarm_Set(MoveY, 9); MoveY++; break;
			case KEY_7: Alarm_Set(MoveY, 7); MoveY++; break;
			case KEY_8: Alarm_Set(MoveY, 8); MoveY++; break;
			case KEY_9: Alarm_Set(MoveY, 9); MoveY++; break;
			case KEY_0: Alarm_Set(MoveY, 0); MoveY++; break;			// �޸�ʱ��(MoveY)��ֵΪ0��
			case KEY_B: MoveY++; OLED_Clear8x8(20,5,16,1); break;
			case KEY_C: MoveY--; OLED_Clear8x8(20,5,16,1); break;
			case KEY_D: GO_HOME break;
			case KEY_ENTER: OLED_Clear(0); Show_ChildMenu_Alarm(); break;
		}
		
		if (MoveY > 7)MoveY = 0;			// ��ͷ��곬����Χʱ����λ��
		if (MoveY < 0)MoveY = 5;
		
		delay_ms(10);
	}
	
	OLED_Clear(0);			// ����������
	Show_ChildMenu_Alarm();							// ������һ����
}


*/