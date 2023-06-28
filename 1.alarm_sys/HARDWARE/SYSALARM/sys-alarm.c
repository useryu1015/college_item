#include "sys-alarm.h"
#include "oled.h"
#include "clock.h"
#include "key.h"
#include "HC-SR501.h"
#include "beep.h"
#include "delay.h"
#include "rc522.h"
#include "cled.h"
#include "key.h"
#include "led.h"
#include "key4x4.h"
#include "string.h"

/*ȫ�ֱ���*/
struct timing TimeVisit[MAXV];			// 
struct timing TimeSteal[MAXS];			// ��¼����ʱ��ṹ�壻 

// 6-8λ �û����룻		
const char LEN = 6;									// ���볤�ȣ�
char PassWord[8] = {1,2,3,4,5,6,0,0};					

char PassWord2[8] = {1,1,3,4,5,6,0,0};		// Ԥ���������ţ�					

int LEDSwitch = 1;									// �����ƿ��أ�

 
// ��ʼ����¼ʱ��Ϊ�գ�
void Time_Init(void)
{
	int i;
	
	for (i = 0; i < ((MAXV > MAXS)?MAXV:MAXS); i++)
	{
		if (MAXV > i)										// ���������
		{
			TimeVisit[i].sign = false;
			//printf("asd:  %d \r\n",i);
		}
			
		if (MAXS > i)
			TimeSteal[i].sign = false;
	}
}



/********************* 11/30 Flag�����õ�ƴ����������...  �� ���� ���� ���� �ؼ� ***********************/
/**********************	
*	Flag���������ж����ܾ���ϵͳ �����������Ӧ�Ĳ�������ִ�еĲ�����
* ��cled�жϺ�����ִ�У�   HW1��HW2��Ӧ�ľ�����
**********************/

// ��⵽��������ϵͳ��
// ���ܣ� 
// 1. ��������˸������ģ�飻
// 2. ��������Ͼ�����
// 3. ��¼����ʱ��Σ�
static void Flag_JinBao()
{
	if (HW1 == 1 && HW2 == 1)
		Write_Time(STEAL);						// ��¼����ʱ�䣻  steal������
	
}

// �ÿͶ�����				// İ�������Թ��ܣ�  Ŀǰδ����
static void Flag_DouLiu()
{
	;
}

// �ֶ����ؾ���ϵͳ��
static void Flag_Guanbi(int Key)
{
	if (Key == ENABLE)
		CLOSE_Alarm_System(CLOSETIME);					// �رվ���ϵͳ10���ӣ�
}

// �ؼң�
// Ŀǰ֧�ֽ��ź󣬰������ر���ϵͳ��  (�ֶ��ر�)
// ������ʱ�޲������Ͷ���������ͬ
// ��չ��ʹ�ô�����Ա��֤�����������ܵȣ�����֤���Զ��رվ���ϵͳ��
//    		�磺ָ����(����)������ʶ��TF��/�ۡ�����Կ�׽������жϣ�     
// 12/3 ͨ����IC��Ƶ����ʶ���Զ��رվ���ϵͳ��
static void Flag_HuiJia(int ICcard)
{
	if (ICcard == MI_OK)
		CLOSE_Alarm_System(CLOSETIME);				// �رվ���ϵͳ10���ӣ�
}

// ��⵽����״̬��											(�Զ��ر�)				
// ��������� if (HW1 == 0 && HW2 == 1)
static void Flag_ChuMen()
{
	if (HW1 == 0 && HW2 == 1)
		CLOSE_Alarm_System(CLOSETIME);					// �رվ���ϵͳ10���ӣ�
}



// ����ϵͳ��
// ע�⣺ 		�ں��ʵ�λ�õ��øú�����
// 		1. main�е���ʱ�������������תִ���������ܣ���ᵼ�¸ú���δ�����ã��ɿ��Բ
//		2. �жϵ��ã����ݹ��࣬����Ԥ֪���ȶ��Բ
void Alarm_System(int Key)
{
	int ICcard;
	//HW_Scan();     										// λ������ ����ɨ�躯����
		
	ICcard = RC522_IcCard_Scan();				// IC��ɨ�躯����
	
	Flag_JinBao();
	Flag_DouLiu();
	Flag_HuiJia(ICcard);
	Flag_ChuMen();
	Flag_Guanbi(Key);
	
}




// ��������ϵͳ
void OPEN_Alarm_System(void)
{
	OLED_Clear(0);									// ����
	TIM_Cmd(TIM3, ENABLE);  				// ʹ��TIMx
	CLED_Color(GREEN);							// ��ɫ					// �������ɾ�������ж��ظ�
	GO_HOME
}


// �رվ���ϵͳ
// ��ʾ�� 
//					1. OLED������ʾ������ʱ��
//					2. ��������3����
// time���ر�ʱ�� ��λ����
// time == 0  ������ֱ���ֶ�������
void CLOSE_Alarm_System(int time)
{
	int KEY = 0;
	int count = NULL;
	
	OLED_Clear(0);									// ����
	OLED_ShowCHinese(0,0,21); 			// ��������ʱ
	OLED_ShowCHinese(16,0,22);			
	OLED_ShowCHinese(32,0,23); 			
	OLED_ShowCHinese(48,0,24);			
	OLED_ShowCHinese(64,0,25); 		
	OLED_ShowString(80,0,":",16);
	
	OLED_ShowCHinese(26,4,16); 			// �����ѹر�
	OLED_ShowCHinese(46,4,17);			
	OLED_ShowCHinese(66,4,26); 			
	OLED_ShowCHinese(86,4,27);			
	OLED_ShowCHinese(106,4,28); 
	
	CLED_Color(OFF);											// �ر�����ʵƣ�
	BEEP = 1;	delay_ms(1000);	BEEP = 0;		// ����������     // ����״̬ʱ����������ת������			// �����жϺ����ķ�ת��������3��XX
	TIM_Cmd(TIM3, DISABLE);  							// ʧ��TIMx���������ж϶������ú������µĲ�ȷ�����أ��ر����ж��У��Ҳ��뺯����			// 11/30 ************* ��λ��Ӧ��ӳ�ʼ���ȣ��� ******************
	CLED_Color(OFF);											// �ر�����ʵƣ�
	
	if (time == STOP)											// �ֶ�����
	{
		OLED_ShowString(92,0,"Null",16);
		while((KEY = KEY_Scan(0)) != KEY0_PRES)//;	// ��ѭ����ֱ���û����� WKUP			// while(KEY_Scan(0) != KEY0_PRES);
			LED_Switch(KEY);									// ��������&�����ƿ��أ� 
		
		OPEN_Alarm_System();
		return;
	}
	
	while(time != 0)
	{
//		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)			// ��·��ͨ��
//		time--;
		OLED_ShowNum(86,0,(u32)time,5,16);	// ��ʾ��������ʱ��
		
		if (count != UPDATEsec)			   			// ��ʱ�ӵ���������ʱ��
		{
			time--;														// ����ʱ ��һ�룻
			count = UPDATEsec;								// ���±�ǣ�
		}
		Key_Switch();
	}
	
	OPEN_Alarm_System();						// �򿪾���ϵͳ
	
}


// ��¼ʱ�䣻
// tips: 	�ú���Ӧ��30������ִֻ��һ�Σ������ظ���¼ʱ��
// VISIT������������
// STEAL������
void Write_Time(u8 value)
{
	int i = 0;
	unsigned int time;
	const unsigned int num = BREAKTIME;							// �����Ͷ���ʱ���¼��̼���� ��λ��Min
	
	// ��¼�ݷúͶ�����  ��δ���õ���
	if (value == VISIT)
	{
		while (TimeVisit[i].sign == true && i < MAXV) 		// �ҳ����ա��Ľṹ��
			i++;
		
		time = Time_Compare(value, i-1); 
		printf("i = %d \r\n",i);
		printf("time = %d \r\n",time);
		if (time < num && i > 0)
		{
			printf("time = %d \r\n",time);
			printf("i = %d \r\n",i);
			return;
		}
		
		if (TimeVisit[i].sign == false)
		{
			printf("���ݼ�¼�ɹ� \r\n");
			TimeVisit[i].month = DateMonth;
			TimeVisit[i].day = DateDay;
			TimeVisit[i].hour = ClockHour;
			TimeVisit[i].min = ClockMin;
			TimeVisit[i].sign = true;					
		}

		if (i >= MAXV)
			for (i = 0; i < MAXV; i++)
				TimeVisit[i].sign = false;			// ��սṹ�壻		
	}
	
	// ��¼����ʱ��
	if (value == STEAL)
	{
		while (TimeSteal[i].sign == true && i < MAXS) 		// �ҳ����ա��Ľṹ��
			i++;
		
		if (Time_Compare(value, i-1) < num)
			return;

		if (TimeSteal[i].sign == false)			// ��ֹi�����
		{
			TimeSteal[i].month = DateMonth;
			TimeSteal[i].day = DateDay;
			TimeSteal[i].hour = ClockHour;
			TimeSteal[i].min = ClockMin;
			TimeSteal[i].sign = true;		
		}			

		
		if (i >= MAXS)
			Time_Init();						// ��սṹ�壻					// ע�⣺ �ú�����ͬʱ���Visit��Steal��sign״̬�� ��������ռ�¼��ʱ�䣻
	}
	
}

// �Ƚ����ڵ�ʱ��� ��¼��ʱ�� ���ֵ��
// ����ֵ��λ�� Min
// ע�⣡�� δ��������������賿��¼������ֵ����ָ�����
// 					��ʹǿ��װ����Ҳδ������ظ���¼���Σ�
unsigned int Time_Compare(u8 value, u8 i)
{
	int NowMin,VisitMin,StealMin;
	
	NowMin = ClockHour * 60 + ClockMin;
	VisitMin = TimeVisit[i].hour * 60 + TimeVisit[i].min;
	StealMin = TimeSteal[i].hour * 60 + TimeSteal[i].min;
	
	if (value == VISIT)
		return (u32)(NowMin - VisitMin);
	
	if (value == STEAL)
		return (u32)(NowMin - StealMin);
}



// 12/3 *****************************************   �����  ����  ***********************************

// ��ʾ����ʱ�� 			// ����ʾ���� Show_Alarm()��ͬ��  ���Ӷ�û����....
// ������ �·ݡ����ڡ�Сʱ�����ӣ�
static void Show_Child_AlarmTime(int i)
{
	//int i = 0;
	int row = -5;
	
	// ��ʾʱ�䲿��
	OLED_ShowNum(22+row,4,TimeSteal[i].hour / 10,1,16);			// ��ʾСʱ��			
	OLED_ShowNum(32+row,4,TimeSteal[i].hour % 10,1,16);			// ��ʾСʱ��	
	OLED_ShowString(40+row,4,":",16);
	OLED_ShowNum(48+row,4,TimeSteal[i].min / 10,1,16);			// ��ʾ���ӡ�
	OLED_ShowNum(58+row,4,TimeSteal[i].min % 10,1,16);			// ��ʾ���ӡ�
	
	// ��ʾ���ڲ���
	OLED_ShowNum(73+row,4,TimeSteal[i].month / 10,1,16);			// ʮλ��ʾ
	OLED_ShowNum(81+row,4,TimeSteal[i].month % 10,1,16);			// ��λ
	OLED_ShowString(89+row,4,"/",16);
	OLED_ShowNum(99+row,4,TimeSteal[i].day / 10,1,16);	
	OLED_ShowNum(107+row,4,TimeSteal[i].day % 10,1,16);		
	
	/******************  ��ʾ��һ��ʱ���  ********************/
	// ��ʾʱ�䲿��
	OLED_ShowNum(22+row+7,6,TimeSteal[i-1].hour / 10,1,8);			// ��ʾСʱ��			
	OLED_ShowNum(32+row+5,6,TimeSteal[i-1].hour % 10,1,8);			// ��ʾСʱ��	
	OLED_ShowString(40+row+4,6,":",8);
	OLED_ShowNum(48+row+3,6,TimeSteal[i-1].min / 10,1,8);			// ��ʾ���ӡ�
	OLED_ShowNum(58+row+1,6,TimeSteal[i-1].min % 10,1,8);			// ��ʾ���ӡ�
	
	// ��ʾ���ڲ���
	OLED_ShowNum(73+row-0,6,TimeSteal[i-1].month / 10,1,8);			// ʮλ��ʾ
	OLED_ShowNum(81+row-0,6,TimeSteal[i-1].month % 10,1,8);			// ��λ
	OLED_ShowString(89+row-1,6,"/",8);
	OLED_ShowNum(99+row-4,6,TimeSteal[i-1].day / 10,1,8);	
	OLED_ShowNum(107+row-4,6,TimeSteal[i-1].day % 10,1,8);			
	
	/******************  ��ʾ���¸�ʱ���  ********************/
	// ��ʾʱ�䲿��
	OLED_ShowNum(22+row+10,7,TimeSteal[i-2].hour / 10,1,8);			// ��ʾСʱ��			
	OLED_ShowNum(32+row+7,7,TimeSteal[i-2].hour % 10,1,8);			// ��ʾСʱ��	
	OLED_ShowString(40+row+5,7,":",8);
	OLED_ShowNum(48+row+3,7,TimeSteal[i-2].min / 10,1,8);			// ��ʾ���ӡ�
	OLED_ShowNum(58+row+1,7,TimeSteal[i-2].min % 10,1,8);			// ��ʾ���ӡ�
	
	// ��ʾ���ڲ���
	OLED_ShowNum(73+row-0,7,TimeSteal[i-2].month / 10,1,8);			// ʮλ��ʾ
	OLED_ShowNum(81+row-1,7,TimeSteal[i-2].month % 10,1,8);			// ��λ
	OLED_ShowString(89+row-2,7,"/",8);
	OLED_ShowNum(99+row-5,7,TimeSteal[i-2].day / 10,1,8);	
	OLED_ShowNum(107+row-6,7,TimeSteal[i-2].day % 10,1,8);				
	
	printf("��ʾ����ʱ��>>%d  ״̬>>%d  \r\n",i+1,TimeSteal[i].sign);
	
}

// ����ʱ���ѯ����
// StealNum�� ��ʾ��¼�˶��ٴΣ�
// 
// struct timing TimeSteal[MAXS];			// ��¼����ʱ��ṹ�壻 
void Show_AlarmTime(void)
{
	int i;
	int StealNum = 0;
	int Key16 = 0;
	
	for (i=0; i < MAXS; i++)
		if (TimeSteal[i].sign == true)		// ��¼�˼���ʱ�䣻
			StealNum++;
		
	printf("����ʱ���ѯ \r\n");		
	OLED_Clear(0);	

		
	OLED_ShowCHinese(6,0,16); 			// ��
	OLED_ShowCHinese(24,0,17);			// ��
	OLED_ShowCHinese(42,0,31); 			// ��
	OLED_ShowCHinese(60,0,32);			// ��
	OLED_ShowString(78,0,":",16);
		
	OLED_ShowNum(96,0,StealNum,2,16);
	OLED_ShowString(29,3,"TIME",8);			// 24
	OLED_ShowString(68,3,"DATE",8);			// 75

	i = StealNum;
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Child_AlarmTime(StealNum-1);	// ��ʾʱ�䣻
		
		switch (Key16)
		{
			case KEY_2: 			
				StealNum++;										// ��ѯ(��ʾ)��һ��ʱ��㣻  ����ʱ���
				break;
			case KEY_8:
				StealNum--;										// ��ѯ(��ʾ)��һ��ʱ��㣻
				break;
			case KEY_B: 			
				StealNum++;										// ��ѯ(��ʾ)��һ��ʱ��㣻  ����ʱ���
				break;
			case KEY_C:
				StealNum--;										// ��ѯ(��ʾ)��һ��ʱ��㣻
				break;
			case KEY_D:
				GO_HOME
				break;
			case KEY_ENTER: 						
				Show_Menu();									// ��ʾ��һ�����棻���ؼ���		
				break;
		}
		
		if (StealNum < 0+1)StealNum = 0+1;		// ������ã�    
		if (StealNum > i+1)StealNum = i+1;

		delay_ms(10);
	}
	
	Show_Menu();												// ��ʾ��һ�����棻���ؼ���		
	
}


// ���ò���ʾ����
void ShowAndSet_Password(char *st, int num, int i)
{
	int row = 10;
	
	if (num == 'A')												// ɾ������
	{
		st[i] = NULL;								
		OLED_Clear8x8(20+row*i,3,1,2);	  	// ��ʾ�հ�..		
		OLED_Clear8x8(20+row*i,3,8,2);			// ɾ���»��ߣ�
		return;
	}
	
	st[i] = num;
	OLED_ShowNum(20+row*i,3,st[i],1,16);

	
}


/***************************
*
*	����Ա������֤���֡�ģ��
*
***************************/

// ��ʾ����λ������: _
// ��ʾ����: *
static void Show_Message(int i)
{
	int row = 10;
	int j;
	
	if (msCount < 500)
		OLED_ShowString(20+row*i,3,"_",16);
	else
		OLED_Clear8x8(20+row*i,3,4,2);	
	
	//if (i>=1);
	//for (j=i; j>=2; j--);
	while (i >= 2)								// �ں���λ����ʾ����* ��������һ�滻��
	{
		OLED_ShowString(20+row*(i-2),3,"*",16);
		i--;
	}
	
}

// �������뺯����  ����ʾ���֣�
// �س����������룻
// *st: ���λ�ã�
// n:   ���������
static void KEY4x4_gets(char *st, int n)
{
	int i = 0;
	int Key16 = 0;
	
//	for (i=0; i<n; i++)
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Message(i);
		if (i >= LEN) i = LEN;
		delay_ms(5);
		switch (Key16)
		{
			case KEY_1: ShowAndSet_Password(st,1,i); i++; break;			
			case KEY_2: ShowAndSet_Password(st,2,i); i++; break;
			case KEY_3: ShowAndSet_Password(st,3,i); i++; break;
			case KEY_4: ShowAndSet_Password(st,4,i); i++; break;			// ע�⣺ KEY_4 ����������ֵ��5��������4�� ���޸Ķ��壻
			case KEY_5: ShowAndSet_Password(st,5,i); i++; break;
			case KEY_6: ShowAndSet_Password(st,6,i); i++; break;
			case KEY_7: ShowAndSet_Password(st,7,i); i++; break;
			case KEY_8: ShowAndSet_Password(st,8,i); i++; break;
			case KEY_9: ShowAndSet_Password(st,9,i); i++; break;
			case KEY_0: ShowAndSet_Password(st,0,i); i++; break;		
			case KEY_A: i--; ShowAndSet_Password(st,'A',i); break;
			case KEY_B: 							break;
			case KEY_C:								break;
			case KEY_D: 		GO_HOME 	break;
			case KEY_ENTER: return;		break;													// ȷ�Ϻ󣬷�������������
		}
	}
	GO_HOME
}



// �û�������Ա������						// unsigned char PassWord;// 8λ �û����룻
// 1. ��ʾ����
// 2. �������ж�
// 3. ��������
// ����뷵�ص�ĳ���������Ѹú����ĺ���ָ����Ϊ������
void User_Password(void)
{
	char value[8];
	
	OLED_Clear(0);						// ������
	OLED_ShowString(0,0,"PassWord:",16);
	OLED_ShowString(60,7,"A:Delete",8);
	
	while (1)
	{
		KEY4x4_gets(value,LEN);
		
		//if (strncmp(value,PassWord,6) == 0)				// �Ƚ��û����������value��Ԥ��������PassWord�� // ��ʼ
		if (strncmp(value,PassWord,6) == 0 || strncmp(value,PassWord2,6) == 0 || RC522_IcCard_Scan() == MI_OK)				// ��г�� 
		{
			printf("Pass OK >>%d \r\n", strncmp(value,PassWord,6));
			return;								// ��֤ͨ������������������
		}
		else
		{
			printf("Wrong >>%d \r\n", strncmp(value,PassWord,6));
			OLED_Clear8x8(0,3,16,2);	
			OLED_ShowString(35,3,"Wrong!!!",16);	// ��֤ʧ�ܣ�����ѭ����
			delay_ms(5000);
			OLED_Clear8x8(35,3,8,2);	
		}
			
	}
	
}



// *************** ��������ģ�� ***********************//
// ��������&�����ƿ��أ�
void Key_Switch(void)
{
	u8 Key = 0;
	static int sled = 1;
		
	Key = KEY_Scan(0);
	
	switch(Key)
	{
		case KEY0_PRES:
			CLOSE_Alarm_System(STOP);					// �رվ���ϵͳ10���ӣ�
			break;
		case KEY1_PRES:
			LEDSwitch = !LEDSwitch;
			break;
	}
	
	if (HW2 == 1 && LEDSwitch)
		LED2 = 1;
	else
		LED2 = 0;
	
}

void LED_Switch(int KEY)								// yitahutu
{
	if (KEY == KEY1_PRES)
		LEDSwitch = !LEDSwitch;
	
	if (HW2 == 1 && LEDSwitch)
		LED2 = 1;
	else
		LED2 = 0;
}





// 11/30  �����
// ***************** ����ϵͳģ�� *************************//
// ���Գ���
void Alarm_System_Test(void)
{
	
	// չʾ����Ч����....      ******************* �����
	
	
}

