#include "cled.h"
#include "usart.h"
#include "led.h"
#include "HC-SR501.h"
#include "beep.h"
#include "speaker.h"
#include "sys-alarm.h"

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void CLED_Init(void)
{
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 	//ʹ��PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	//IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					 				//�����趨������ʼ��GPIOB.5
	
 GPIO_SetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5);	//PB.5 �����
}





// ���ö�ʱ���жϣ��ﵽ��˸Ч����	
// �ŵ㣺��delay��Ȳ�Ӱ��������ִ�С���ռ��������	����ʵʱ�ԣ�
// ������IO�ڣ�	 PC0 PC4
// ���е�ʹ��һ����ʱ������Ӱ�죺	
// 1. ͬʱ��˸��ͬʱ��ת�� 
// 2. ע�⣺�ж����ݹ��ࣻ
void TIM3_Int_Init(u16 arr,u16 psc)			// ��ʱ��3���жϷ������
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //	ʹ��TIMx					 
}


// ��ʱ��3�жϷ������
// ���ƾ�������˸
// ���ж�ֻ���ƾ�������˸������ ��Ҫ�������㣡��
void TIM3_IRQHandler(void)    // TIM3�ж�
{
	static int ColorSign = 0;				// �жϱ���������������
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );   //���TIMx�����жϱ�־ 
			//printf("TIM3_�жϷ�����ִ��   \r\n");
			
			if (HW1 == 1)
			{
				CLED_Color((ColorSign==0)?RED:BLUE);			// ��ʾ����˫ɫ ��ת��
				ColorSign = !ColorSign;
				
				SPEAK = 1;																// ��������ʹ��
			}
			else
			{
				CLED_Color(OFF);					// �ر�
				CLED_Color(GREEN);				// ��ɫ
				
				SPEAK = 0;								// �ر�����
			}
				
			if (HW2 == 1 && HW1 == 1)
				BEEP = !BEEP;							// ��������ת������
			else
				BEEP = 0;   							// �رշ�������
			
			//Key_Switch();								// ��������&�����ƿ��أ� 
			//HW_LED_StateFlag();					// ���⴫����״ָ̬ʾ�ƣ�   // HWʹ�ܣ�IO����ߵ�ƽ��
			//�ú����ƶ���clock�жϺ����У�  ԭ�򣺸��жϻ����ݾ���ϵͳ�Զ��رգ�
		}
}



// ���Ƶ���CLED״̬(��ɫ)
// Tips: ��Զ����ֻ��һ��Ϊ�͵�ƽ�� �����ledӰ�죻
void CLED_Color(int color)
{
	switch (color)
	{
		case RED: 	CLED_RED = 0;CLED_GREEN = 1;CLED_BLUE = 1; break;
		case GREEN:	CLED_RED = 1;CLED_GREEN = 0;CLED_BLUE = 1; break;
		case BLUE:	CLED_RED = 1;CLED_GREEN = 1;CLED_BLUE = 0; break;
		case OFF: 	CLED_RED = 1;CLED_GREEN = 1;CLED_BLUE = 1; break;
	}
}


//			if (HW_Sign&0x0001)			// �ж� 0001λ״̬��
//				LED0 =! LED0;
//			else
//				LED0 = 1;
//			
//			if (HW_Sign&0x0002)			// �ж� 0010λ״̬��
//				LED1 =! LED1;
//			else
//				LED1 = 1;


// ���ùܣ�
void TIM3_DISABLE(u8 number)
{
	TIM_Cmd(TIM3, DISABLE);  // ʧ��TIMx
	LED0 = 1;
	LED1 = 1;
}



