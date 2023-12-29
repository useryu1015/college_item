#include "clock.h"
#include "oled.h"
#include "delay.h"

#include "usart.h"
#include "stdbool.h"

bool sign = true;			// ���ӱ�־�� Ĭ�ϣ� ��
int AlramValue = 0;


/******************* ************************************************************   11 / 15 -------------------------------
* ��ʾ����
*******************/


/*
// ��ʾ�����溺�֣���ͷ�ȣ�
void Show_Chinese(void)
{
		OLED_ShowCHinese(6,0,4); 			// ��
		OLED_ShowCHinese(26,0,5);			// ��
		OLED_ShowString(42,0,":",16); // :
//		OLED_ShowCHinese(6,2,6); 			// ʱ
//		OLED_ShowCHinese(6,4,7);			// ��
	
		OLED_ShowString(93,7,"menu",8);
		
	
		Move_Menu_Point(80,7,8,500);				// ������(80,7)��ʾ��ͷ��
}

// ��ʾ���ڣ�
void Show_Date(u8 value)
{
		if (value == 1)			// ���������棻
		{
			OLED_ShowNum(8+46,1,DateYear,4,12);		
			OLED_ShowString(33+46,1,"/",12);
			OLED_ShowNum(40+46,1,DateMonth / 10,1,12);		// ʮλ��ʾ
			OLED_ShowNum(47+46,1,DateMonth % 10,1,12);		// ��λ
			OLED_ShowString(54+46,1,"/",12);
			OLED_ShowNum(61+46,1,DateDay / 10,1,12);	
			OLED_ShowNum(68+46,1,DateDay % 10,1,12);			
		}
		if (value == 2)			// �������ý��棻
		{
			OLED_ShowNum(5+16,3,DateYear,4,16);		
			OLED_ShowString(38+16,3,"/",16);
			OLED_ShowNum(47+16,3,DateMonth / 10,1,16);		// ʮλ��ʾ
			OLED_ShowNum(55+16,3,DateMonth % 10,1,16);		// ��λ
			OLED_ShowString(64+16,3,"/",16);
			OLED_ShowNum(73+16,3,DateDay / 10,1,16);	
			OLED_ShowNum(81+16,3,DateDay % 10,1,16);				
		}
}

// ��ʾʱ�䣻
void Show_Time(void)
{
		int row = -2;
		
//		Date_Update();			// �������ڣ�

		OLED_ShowNum(22+row,3,ClockHour / 10,1,16);			// ��ʾСʱ��			
		OLED_ShowNum(32+row,3,ClockHour % 10,1,16);			// ��ʾСʱ��	
		OLED_ShowString(40+row,3,":",16);
	
		OLED_ShowNum(48+row,3,ClockMin / 10,1,16);			// ��ʾ���ӡ�
		OLED_ShowNum(58+row,3,ClockMin % 10,1,16);			// ��ʾ���ӡ�
		OLED_ShowString(66+row,3,":",16);	
	
		OLED_ShowNum(74+row,3,ClockSec / 10,1,16);			// ��ʾ������ ʮλ	// �����ֵÿλ��ʾ������ȷ��ʾ0X��
		OLED_ShowNum(84+row,3,ClockSec % 10,1,16);			// ��ʾ������	��λ
		OLED_ShowString(92+row,4,".",8);
	
		OLED_ShowNum(97+row,4,msCount/100,1,8);		// ��ʾ���롣
		OLED_ShowNum(104+row,4,(msCount/10) % 10,1,15);		// ��ʾ���롣

		
//		//�жϵ�С��10ʱ�� ��ʾ���㣻    BUG�� ��ʾʱ�������֣����ᶨ��  DEBUG�� ÿ���ظ�ִ��ʱ�������Զ�ˢ�£�  // ÿ��ִֻ��һ�Σ�
//		if (ClockHour < 10)
//			OLED_ShowNum(20,4,0,1,16);
//		if (ClockMin < 10)
//			OLED_ShowNum(48,4,0,1,16);
//		if (ClockSec < 10)
//			OLED_ShowNum(76,4,0,1,16);
//		if (msCount < 10)
//			OLED_ShowNum(97,5,0,1,15);
		
}




// ��ʾ����
// ������ �·ݡ����ڡ�Сʱ�����ӣ�
void Show_Alarm(void)
{
	int row = 0;
	
	OLED_ShowNum(22+row,3,ClockHour / 10,1,16);			// ��ʾСʱ��			
	OLED_ShowNum(32+row,3,ClockHour % 10,1,16);			// ��ʾСʱ��	
	OLED_ShowString(40+row,3,":",16);

	OLED_ShowNum(48+row,3,ClockMin / 10,1,16);			// ��ʾ���ӡ�
	OLED_ShowNum(58+row,3,ClockMin % 10,1,16);			// ��ʾ���ӡ�
	
	
	OLED_ShowNum(73+row,3,DateMonth / 10,1,16);		// ʮλ��ʾ
	OLED_ShowNum(81+row,3,DateMonth % 10,1,16);		// ��λ
	OLED_ShowString(89+row,3,"/",16);
	OLED_ShowNum(99+row,3,DateDay / 10,1,16);	
	OLED_ShowNum(107+row,3,DateDay % 10,1,16);		
	
	//73+row,81+row,99+row,107+row
}






// ���ӿ��أ�
void Set_Alarm_Switch(void)
{
	int Key = 0;
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"ChildMenu-Alarm",16);
	OLED_ShowString(32,2,"Alarm: ",16);
	
	while (1)
	{
		Key = KEY4x4_Scan();
		delay_ms(20);
		
		OLED_Clear8x8(96,2,4,2);					// ������������λ�ü��ɣ�					OLED_Clear8x8(96,2,4,2);	
		if (sign == true)
			OLED_ShowString(96,2,"ON",16);
		if (sign == false)
			OLED_ShowString(96,2,"OFF",16);
		
		switch (Key)
		{
			case KEY_B: 
				sign = !sign;
				break;
			case KEY_C:
				sign = !sign;
				break;
			case KEY_D:
				GO_HOME
				break;
			case KEY_ENTER: 						// ���λ�ÿ����Զ���˵�ѡ��������ܣ�
				Show_ChildMenu_Alarm();
				//return sign;
			case KEY_RETURN:
				Show_ChildMenu_Alarm();
				//return sign;							// BUG�� ��return���ܸ��£�
		}
	}
	
	
}

// ѡ��ڼ������ӣ����ṹ�壻
void Set_Alarm_Choose(int * value)
{
	int Key = 0;
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"ChildMenu-Alarm",16);
	OLED_ShowString(32,4,"Alarm: ",16);
	
	
	while (1)
	{
		Key = KEY4x4_Scan();
		delay_ms(10);
		
		OLED_ShowNum(96,4,(u32)*value,2,16);
		
		switch (Key)
		{
			case KEY_B: 
				(*value)++;								// һ�������õ� value++�ȣ�������  �����޸ĵ�ַ������
				break;
			case KEY_C:
				(*value)--;
				break;
			case KEY_D:
				GO_HOME
				break;
			case KEY_ENTER: 						// ���λ�ÿ����Զ���˵�ѡ��������ܣ�
				Show_ChildMenu_Alarm();
				//return sign;
			case KEY_RETURN:
				Show_ChildMenu_Alarm();
				//return sign;							// BUG�� ��return���ܸ��£�
		}
		
		if (*value < 0)
			*value = 20;
		if (*value > 20)
			*value = 0;
	}
	
}

void Show_ChildMenu_Alarm(void)		//bool sign, int value
{
	int Key = 0;
	int MoveP = 2;						// ��ͷ���ꣻ
	static int value = 0;			// ָ������ӣ�
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"ChildMenu-Alarm",16);
	
	OLED_ShowString(32,2,"Alarm: ",16);
		if (sign == true)
			OLED_ShowString(96,2,"ON",16);
		if (sign == false)
			OLED_ShowString(96,2,"OFF",16);
		
	OLED_ShowString(32,4,"Alarm: ",16);
		OLED_ShowNum(96,4,value,2,16);
		
	OLED_ShowString(32,6,"Alarm Set",16);
	
	while (1)
	{
		Key = KEY4x4_Scan();
		Move_Menu_Point(12,MoveP,161608,600);					// ��ʾ��ͷ��
		
		switch (Key)
		{
			case KEY_2: 
				Move_Menu_Point(12,MoveP,161608,0);				// ������ͷ��
				MoveP -= 2;
				break;
			case KEY_8:
				Move_Menu_Point(12,MoveP,161608,0);				// ������ͷ��
				MoveP += 2;
				break;
			case KEY_D:
				GO_HOME
				break;
			case KEY_ENTER: 							// ���λ�ÿ����Զ���˵�ѡ��������ܣ�
				if (MoveP == 2)						
					Set_Alarm_Switch();				// ���ӿ��أ�
				if (MoveP == 4)						
					Set_Alarm_Choose(&value);	// ����ѡ��
				if (MoveP == 6)						
					Menu_Alarm_Set(value);		// �������ã�
				break;
			case KEY_RETURN:
				OLED_Clear(0);									// ������
				Show_ChildMenu(0);							// ��ʾ��һ�����棻���ؼ���		
				break;
		}
		
		if (MoveP > 6)MoveP = 2;			// ��ͷ��곬����Χʱ����λ��	MoveP: 3/6
		if (MoveP < 2)MoveP = 6;
			
		delay_ms(10);
	}

}





// ��ʾchildmenu�Ӳ˵�
void Show_ChildMenu(char value)
{
	int Key16 = 0;
	int MoveP = 2;			// ��ͷ���ꣻ 
	int Y = 8,Y2 = 16;
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"ChildMenu:",16);
	
	if (value == 0)			// ��������
	{
		// ����ʱ�䣻
		OLED_ShowCHinese(32,2,9); 			// 
		OLED_ShowCHinese(48,2,10);			// 
		OLED_ShowCHinese(64,2,6); 			// 
		OLED_ShowCHinese(80,2,7);				// 

		// �������ڣ�
		OLED_ShowCHinese(32+Y,4,9); 			// 
		OLED_ShowCHinese(48+Y,4,10);			// 
		OLED_ShowCHinese(64+Y,4,4); 			// 
		OLED_ShowCHinese(80+Y,4,5);				// 
		
		// �������ӣ�
		OLED_ShowCHinese(32+Y2,6,9); 			// 
		OLED_ShowCHinese(48+Y2,6,10);			// 
		OLED_ShowCHinese(64+Y2,6,19); 			// 
		OLED_ShowCHinese(80+Y2,6,20);			// 		
		
		while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
		{
			Move_Menu_Point(12,MoveP,161608,600);					// ��ʾ��ͷ��
			
			switch (Key16)
			{
				case KEY_2: 
					Move_Menu_Point(12,MoveP,161608,0);				// ������ͷ��
					MoveP -= 2;
					break;
				case KEY_8:
					Move_Menu_Point(12,MoveP,161608,0);				// ������ͷ��
					MoveP += 2;
					break;
				case KEY_D:
					GO_HOME
					break;
				case KEY_ENTER: 						// ���λ�ÿ����Զ���˵�ѡ��������ܣ�
					if (MoveP == 2)						
						Menu_Time_Set();				// ����ʱ�䣻
					if (MoveP == 4)						
						Menu_Date_Set();				// �������ڣ�
					if (MoveP == 6)						
						Show_ChildMenu_Alarm();						// �������ӣ�
					break;
			}
			
			if (MoveP > 6)MoveP = 2;			// ��ͷ��곬����Χʱ����λ��	MoveP: 3/6
			if (MoveP < 2)MoveP = 6;
			
			delay_ms(10);
		}
		
		Show_Menu();										// ��ʾ��һ�����棻���ؼ���		
	}
	
}

// ��ʾmenu�˵�
void Show_Menu(void)
{
	int Key16 = 0;
	int MoveP = 3;		// ��ͷ���ꣻ 0-5��
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"Menu:",16);

	// ��ѯ������
	OLED_ShowCHinese(32,3,14); 			// 
	OLED_ShowCHinese(48,3,15);			// 
	OLED_ShowCHinese(64,3,16); 			// 
	OLED_ShowCHinese(80,3,17);			// 
	OLED_ShowCHinese(96,3,18); 			// 
		
	// ����������
	OLED_ShowCHinese(32,6,9); 			// 
	OLED_ShowCHinese(48,6,10);			// 
	OLED_ShowCHinese(64,6,11); 			// 
	OLED_ShowCHinese(80,6,12);			// 
	OLED_ShowCHinese(96,6,13); 			// 
	
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Move_Menu_Point(12,MoveP,161608,600);					// ��ʾ��ͷ��
		
		switch (Key16)
		{
			case KEY_2: 
				Move_Menu_Point(12,MoveP,161608,0);				// ������ͷ��
				MoveP += 3;
				break;
			case KEY_8:
				Move_Menu_Point(12,MoveP,161608,0);				// ������ͷ��
				MoveP -= 3;
				break;
			case KEY_D: 
				GO_HOME
				break;
			case KEY_ENTER: 						// ���λ�ÿ����Զ���˵�ѡ��������ܣ�
				if (MoveP == 3)						// �����Ӳ˵� �������� ����ʱ�䣻			
					;
				if (MoveP == 6)						// �Ӳ˵� �������� ���������ã�
					Show_ChildMenu(0);
				break;
		}
		
		if (MoveP > 6)MoveP = 3;			// ��ͷ��곬����Χʱ����λ��	MoveP: 3/6
		if (MoveP < 3)MoveP = 6;
		
		delay_ms(10);
	}
	
	Show_Home();										// ��ʾ��һ�����棻���ؼ���		
}

// ��ʾhome�����棻
void Show_Home(void)  		
{
	int key = 0;
	OLED_Clear(0);						// ������
	
	while(1)
	{
		Show_Time();						// ��ʾʱ�䣻
		Show_Date(1);						// ��ʾ���ڣ�
		Show_Chinese();					// ��ʾ���Ľ��棻	
		
		if ((key = KEY4x4_Scan()) == KEY_ENTER)				// ����MENU����
			Show_Menu();
		
		
		if (key == KEY_A)				// ���ڲ��ԣ�
		{
			while (1)
			{
				DateDay++;		
				Date_Update();
				
				delay_ms(300);
				Show_Date(1);						// ��ʾ���ڣ�
				
				if (DateDay > 5 && DateDay < 20)
					DateDay = 20;
			}
		}

	}

}
*/