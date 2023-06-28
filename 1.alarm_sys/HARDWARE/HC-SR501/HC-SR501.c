#include "stm32f10x.h"
#include "HC-SR501.h"
#include "led.h"
#include "usart.h"
#include "cled.h"

int HW_Sign = 0x0000;				// �ж�(��¼)���⴫����״̬ �ı�־


// ������⴫������ʼ��
void HCSR501_Init(void)			// �ж���16��������������ͬ��ţ�
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_4;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		//���ó���������  // ��������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);						//��ʼ��GPIOC6,7  // PC0,4    PC5-9������һ���ⲿ�жϺ���......
	
}







// ����״̬ɨ�躯����
void HW_Scan(void)
{
	if (HW1 == ENABLE)				// ENABLE != 0; �����㣻	// ģ�����ԣ� �Դ��ɵ���Ӧ��ʱ������������ʱ���ұ���Ӳ�����ƣ�
		HW_Sign |= 0x0001;
	else
		HW_Sign &= 0xFFFE;			// 1110
	
	if (HW2 == ENABLE)
		HW_Sign |= 0x0002;
	else
		HW_Sign &= 0xFFFD;			// 1101        // 1011 == B		0111 == 7		1101 == D		1110 == E
	
	
	if (HW_Sign == 0x0000)		// ����.....
	{
		TIM3_DISABLE(1);	
		//printf("TIM3_��ʱ���ѹر�		\r\n");
	}
	else
		TIM_Cmd(TIM3, ENABLE); 	// ʹ�ܶ�ʱ����


}






