#include "led.h"
#include "beep.h"
#include "key.h"
#include "MQ-2.h"
#include "fire.h"

/**************************************************************************
��������������������
��ڲ�������
����ֵ����
 *************************************************************************/
void beep_heartbeat(void)
{
	/*
	if (key_state && (MQ2_state || fire_state)){		// ����xx������һ��ֵ������������״̬��
		Sensor_OUT = 0;          //������������
	} else{
		Sensor_OUT = 1;          //����������
	}
	*/

	if (1){
	 	Sensor_OUT = 1;          //����������
		led_on(LED_3);	         //�����û�ָʾ��D3
		delay_ms(1000);          //��ʱ1S������۲�ʵ������
		
		Sensor_OUT = 0;          //������������
		led_off(LED_3);	         //Ϩ���û�ָʾ��D3
		delay_ms(1000);          //��ʱ1S������۲�ʵ������


	}

}

/*********************************END FILE********************************************/	
