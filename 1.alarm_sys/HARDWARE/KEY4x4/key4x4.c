#include "stm32f10x.h"
#include "key4x4.h"
#include "sys.h" 
#include "delay.h"
#include "usart.h"


/*************************
X��
	PEin	7-10

Y��
	PEout	11-14
*************************/


// ���󰴼���ʼ������
void KEY4x4_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;//KEY0-KEY1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
		GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;				 //LED0-->PB.5 �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOE, &GPIO_InitStructure);							 //�����趨������ʼ��GPIOE
}

// ʹ����������ͣ���ʼ����		// ����ʹ��define���壬ִ���ٶȸ��죡����
static void KEY_ALL_Pull_Down(void)
{
	KEY_Y(11) = 0;
	KEY_Y(12) = 0;
	KEY_Y(13) = 0;
	KEY_Y(14) = 0;
}


// 4x4����ɨ�躯��
// ʹ��һ��Ƕ��ѭ�������ɨ��X��Y��
// ԭ�� ͨ��Y ��������ߵ�ƽ,
//				ɨ��X �Ǹ�IO������ߵ�ƽ��
// X�᣺�����顢ɨ�裻
// Y�᣺�������״̬��
// �ú����ʺ��������о��󰴼���ֻ���޸�ѭ���ж�Ӧ��ţ���
// ע�⣺ 1. �ı�IO��ʱ���ú�������Ҫ�ı�ѭ����IO�ڱ�ţ������Զ����IO�ڱ�ţ������޸ģ�
//				2. �ú���ͬ�������ȼ����⣡ ��ͬʱ����ʱ��ֻ�����ȱ�ɨ�赽�ģ�0-15�����С�ģ�
//				3. ����ͬһ�������IO�ڱ�ű������ڻ����� ���ɵ�����Ѱ���������޷���ѭ���жϣ�
//				4. ��ʱδ��ӹ��ܣ�ģʽ����	�������� �� ������
// 2020-11-13		����ֵ����Ϊ	1-16
// 11/14 ��֧��������
u8 KEY4x4_Scan(void)
{
	int i,j;							// ���ꣻ
	static u8 IO_Sign = 1;				// �ܼ���һ��IO������ʽ��ǩ������  ��Ƕ��ѭ�����У���  // �ܷ���0-15���ʺ��������о��󰴼�
	static u8 key_up = 1;	// �������ɿ���־;  
	
	IO_Sign = 1;
	
	for (i = 11; i <= 14; i++)							// Y���IO�ڱ�ţ�
		for (j = 7; j <= 10; j++,IO_Sign++)		// X���IO�ڱ�ţ�  // ����IO_Sign��������Ӧֵ��0-15����
		{
			KEY_Y(i) = 1;			// ʹPEout(i)����ߵ�ƽ��
			
			if (KEY_Y(i))			// ɨ��Y����ߵ�ƽ�� ����ȡ�����жϣ� ��Ϊ��������ߵ�ƽʱ�����������жϣ���
			{
				if (KEY_X(j) && key_up)		// �������鵽�ߵ�ƽʱ��
				{
					key_up = 0;
					printf("����ɨ�裺 %d  \r\n",IO_Sign);
					return IO_Sign;
				}
				else if (!KEY_X(7)&&!KEY_X(8)&&!KEY_X(9)&&!KEY_X(10))			// �����������⵽�͵�ƽʱ��ʹ�ܰ�����
				{
					key_up = 1;
					KEY_ALL_Pull_Down();										// ��ʼ�����а���������ͣ�	// ������ڴ�λ�ã�����XXXX������ȷ�ж�������
				}
					
			}
			else
				printf("PEout:IO��%d����쳣��  \r\n ", i);
		}
		
	delay_ms(10);					// ����������
	return 0;
}

// ��׼����ɨ�躯����
// ֧��������
// 11/23 �����ô˺������������ţ�����
u8 KEY16_Scan(void)
{
	int i,j;
	u8 IO_Sign = 1;				// �ܼ���һ��IO������ʽ��ǩ������  ��Ƕ��ѭ�����У���  // �ܷ���0-15���ʺ��������о��󰴼�
	
	ALL_DOWN_KEY_Y													// ��ʼ�����а���������ͣ�
	
	for (i = 11; i <= 14; i++)							// Y���IO�ڱ�ţ�
		for (j = 7; j <= 10; j++,IO_Sign++)		// X���IO�ڱ�ţ�  // ����IO_Sign��������Ӧֵ��0-15����
		{
			KEY_Y(i) = 1;			// ʹPEout(i)����ߵ�ƽ��

			if (KEY_X(j))			// �������鵽�ߵ�ƽʱ��
				return IO_Sign;
		}
		
	delay_ms(20);					// ����������  // ������������ʱ��
}
