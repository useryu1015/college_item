#include "clock.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
//#include "key.h"
//#include "key4x4.h"

u16 msCount = 0;//ms����			// ��������Ȧ������

// ������-ʱ��
u8 ClockHour = 20,						// volatile ���η�Ϊʲô����...
		ClockMin = 59,
		ClockSec = 58;

// ������-����
u16 DateYear	= YEAR,
		DateMonth = MONTH,
		DateDay		= DAY;

struct month{
	char mname[15];
	char name3[4];
	int days;
	int month;
};

static struct month months[12] = 
{
		"January" ,   "jan" , 31 , 1 ,
		"February" ,  "feb" , 28 , 2 ,
		"March" ,     "mar" , 31 , 3 ,
		"April" ,     "apr" , 30 , 4 ,
		"May" ,	      "may" , 31 , 5 ,
		"June" ,      "jun" , 30 , 6 ,
		"July" ,      "jul" , 31 , 7 ,
		"August" , 	  "aug" , 31 , 8 ,
		"September" , "sep" , 30 , 9 , 
		"October" ,   "oct" , 31 , 10 ,
		"November" ,  "nov" , 30 , 11 ,
		"December" ,  "dec" , 31 , 12 ,
};


void Hcsr04Init()					// ��ʼ����ʱ������������������			����������������������ȣ�
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //�������ڶ�ʱ�����õĽṹ��
	 
		//��ʱ����ʼ�� ʹ�û�����ʱ��TIM6
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);   //ʹ�ܶ�ӦRCCʱ��
		//���ö�ʱ�������ṹ��
		TIM_DeInit(TIM2);
		TIM_TimeBaseStructure.TIM_Period = (1000-1); //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ         ������1000Ϊ1ms
		TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  1M�ļ���Ƶ�� 1US����
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ		 
		
		TIM_ClearFlag(TIM6, TIM_FLAG_Update);  			 //��������жϣ����һ���ж����������ж�
		TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);   	 //�򿪶�ʱ�������ж�
		clock_NVIC();
    //TIM_Cmd(TIM6,DISABLE);     	//�ر�ʹ��TIMx����
		TIM_Cmd(TIM6, ENABLE); 			//ʹ��TIMx����
}
 

//NVIC����
void clock_NVIC()
{
			NVIC_InitTypeDef NVIC_InitStructure;
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
			NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;         		//ѡ�񴮿�1�ж�
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  	//��ռʽ�ж����ȼ�����Ϊ1
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         	//��Ӧʽ�ж����ȼ�����Ϊ1
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        			//ʹ���ж�
			NVIC_Init(&NVIC_InitStructure);
}
 
//��ʱ��6�жϷ������
void TIM6_IRQHandler(void)   //TIM6�ж�							// DEBUG������ ��������Ǻ�ʱ���У���˭���õģ�����     ����Ȧ���ı�־��
{
		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
						TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
						msCount++;
			
						if (msCount > 998)			// ���ٲ���Ҫ�Ľ���/������ת��
						{
							Time_Update(24);			// ��ֹ��תʱ��������δִ�и��£�   	// ������CPU������
							
							if (ClockHour >= 23 && ClockMin >= 58)
								Date_Update();
						}
		}
}

/*********************************************************************************************************************************************************
*
*																					  �Զ��庯������
*
*********************************************************************************************************************************************************/


/******************************************
* ʱ�Ӹ���ģ�飻
* ����ת����
* 11/23: �ò����ѷ����ڶ�ʱ���жϣ�
******************************************/

// ����ʱ�䣻
// style: ʱ����ʾ12 / 24 Сʱ ����ѡ��
void Time_Update(u8 style)
{
	//static int sign = 0;
	
	if (msCount >= 1000)		// ��������1000����ʱ������������ 
	{
		msCount = 0;
		ClockSec++;
	}
	
	if (ClockSec >= 60)			// ���ӵ�����
	{
		ClockSec = 0;
		ClockMin++;
	}
	
	if (ClockMin >= 60)			// Сʱ������
	{
		ClockMin = 0;
		ClockHour++;
	}
	
	if (ClockHour >= style && style == 24)	// Ϊ����������׼����
	{
		ClockHour = 0;				// ����ʱ�����ѱ����㣻�����ٳ�ʼ���� 
		DateDay++;
	}
	
}

// �������ڣ�
void Date_Update(void)
{

// ����һ�� 
//	static int Leap_Year = 1;				// �����ǩ��	
//	if (DateYear % 4 == 0)
//	{
//		Leap_Year = 0;							// �ر���һ���жϣ�
//		
//		if (DateDay > months[DateMonth-1].days + 1)
//			//update...
//	}
		
	//if (DateYear % 4 == 0)
	if((DateYear%4==0&&DateYear%100!=0)||(DateYear%400==0&&DateYear%3200!=0)||DateYear%172800==0)				// �ٶȵ������жϷ�ʽ��
	{
		months[1].days = 29;						// ����ʱ�����ṹ�壩2�������޸�Ϊ 29��
	}
	else
		months[1].days = 28;
	
	
	if (DateDay > months[DateMonth-1].days)					// �����ڴ��ڵ�ǰ�µ��������ʱ�������£�
	{
		DateDay = 1;
		DateMonth++;
	}
	
	if (DateMonth > 12)
	{
		DateMonth = 1;
		DateYear++;
	}
	
}

























/*

// ������� �ƶ���		����˸��
// sign: Y����ı�ţ�
// value: �޸ĵĹ��ܣ� �磺
//			 	0. �޸�ʱ�䣻
//				1. �޸����ڣ�
void Move_Point(char sign, char value)
{
	static int num = 0;
	const int row = 2;							// ��ͷ����΢����
	
	// ���������Ա���ݣ���Ϣ����ʱ����ʾ��ʮλ��Y�����ꣻ
	const int MoveY[3][8] = {{22,32,48,58,74,84},			
													 {37+row,45+row,63+row,71+row,89+row,97+row},
													 {22+row,32+row,48+row,58+row,73+row,81+row,99+row,107+row}};
	
	num++;
	
//	if (msCount > 500)
//		OLED_ShowString(MoveY[value][sign] -2,5,"^",8);
//	else
//		OLED_Clear8x8(20,5,16,1);						// 11/13 BUG: ��������clear ********************************* 11/13 ***********\
	
	if (num % 16 < 10)
		OLED_ShowString(MoveY[value][sign] -2,5,"-",8);
	else
		OLED_Clear8x8(20,5,16,1);	
}

// ����ѡ���ָʾ��ͷ��
// x: 0-127
// y: 0-7
// value�� ��ͷ�ߴ磻 						// 0X����ͷ��ʽ��
// ms: ��ͷ��˸Ƶ�ʣ���λms��			// αƵ�ʣ� Nowֻ�ı�����ʾ�������ı�����������˸Ƶ�ʣ�
// Move_Menu_Point(x,y,1616,0)		// ����ʵ�� ָ��λ�ü�ͷ���㣡���� ʵ�ּ�ͷ�ƶ��ı�������		// Ҳ������OLED_Clear8*8 ָ��λ�����㣻
void Move_Menu_Point(u8 x, u8 y, int value, int ms)
{
	
	// �ߴ磺 8*8
	if (value == 8)
	{
		if (msCount < ms)
			OLED_ShowCHinese8x8(x,y,2);	// ��ʾ��ż�ͷ��8*8
		else
			OLED_ShowCHinese8x8(x,y,0);	// ��ʾ�հ�..		
	}
	
	
	// �ߴ�16*16
	if (value == 161608 || value >= 161600)
	{
		if (msCount < ms)
			OLED_ShowCHinese(x,y,value%100);	// ��ʾ��ż�ͷ��8*8
		else
			OLED_Clear8x8(x,y,2,2);	  	// ��ʾ�հ�..		
	}
}


*/


/****************
*
*			END
*
****************/



// 11/15  �����д�����ڽ���....   ûƷ��
// 		���ǿɶ���̫��߼���ϵ����Ȼ��̫�ң�.....














































/**************
*
* ������ʾ���
* ����ʱ�ӣ�	�ƶ����ꣻ
*	ָ��ʱ�ӣ�	����BMPͼ��һ֡һ֡��ʾ��
*
***************/

	
// ��ʾʱ�䣻
void Show_Time2(void)
{
	int row = 30;
	int SecSign,i;

	OLED_ShowNum(22+row,3,ClockHour / 10,1,16);			// ��ʾСʱ��
	OLED_ShowNum(32+row,3,ClockHour % 10,1,16);			// ��ʾСʱ��	
	OLED_ShowString(40+row,3,":",16);

	OLED_ShowNum(48+row,3,ClockMin / 10,1,16);			// ��ʾ���ӡ�
	OLED_ShowNum(58+row,3,ClockMin % 10,1,16);			// ��ʾ���ӡ�
	OLED_ShowString(66+row,3,":",16);	

	OLED_ShowNum(10+row,6,ClockSec / 10,1,16);			// ��ʾ������ ʮλ	// �����ֵÿλ��ʾ������ȷ��ʾ0X��
	OLED_ShowNum(20+row,6,ClockSec % 10,1,16);			// ��ʾ������	��λ
	
	SecSign = ClockSec;
	
	for (i = 30+row; i < 120; i += 16)
	{
		SecSign++;
		OLED_ShowNum(i,7,SecSign / 10,1,8);		// ��ʾ���롣
		OLED_ShowNum(i+7,7,SecSign % 10,1,8);		// ��ʾ���롣			// ���߼���� 7
	

	}
	
	
}



