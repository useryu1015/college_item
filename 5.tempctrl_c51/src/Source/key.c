#include "led.h"
#include "key.h"	

uint8 key_state = 1;

/**************************************************************************
���������������������
��ڲ�������
����ֵ����
 *************************************************************************/
void KEY_Scan(void)
{
	 if(TOUCH_KEY == 1)           //��ⴥ������������P5.4�Ƿ��Ǹߵ�ƽ (����ָ����������Ӧ��������Ϊ�ߵ�ƽ)
	 {
		 key_state = ~key_state;		// ques: ���������¹���
	    delay_ms(10);             //������ʱ10ms����������
	    if(TOUCH_KEY== 1)	        //��ⴥ������������P5.4�Ƿ���Ȼ�Ǹߵ�ƽ
	    {
				led_on(LED_3);	        //�����û�ָʾ��D3
		    while(TOUCH_KEY == 1)   //�ȴ����������ͷţ������P5.4һֱΪ�ߵ�ƽ����һֱִ�п�����
				{
					;                     //����TOUCH_KEY == 1��������ִ�����������
				}
        led_off(LED_3);	        //���������ͷţ�Ϩ���û�ָʾ��D3
	    }
	 }
}

/*********************************END FILE********************************************/	
