
#include "led.h"	

 /**************************************************************************
��������������һ��ָ����ָʾ��(D1��D2��D3��D4)
��ڲ�����uint8 led_idx  (��ȡֵLED_1��LED_2��LED_3��LED_4)
����ֵ����
 *************************************************************************/
void led_on(uint8 led_idx)
{
  switch(led_idx)
	{
		case LED_1:
      LED_D1=0;	       //����P2.6�˿�����͵�ƽ�������û�ָʾ��D1
		  break;		
		case LED_2:
      LED_D2=0;        //����P2.7�˿�����͵�ƽ�������û�ָʾ��D2
		  break;
		case LED_3:
      LED_D3=0;	       //����P7.2�˿�����͵�ƽ�������û�ָʾ��D3
		  break;		
		case LED_4:
      LED_D4=0;        //����P7.1�˿�����͵�ƽ�������û�ָʾ��D4
		  break;
		default:
		  break;
  }
}

/**************************************************************************
����������Ϩ��һ��ָ����ָʾ��(D1��D2��D3��D4)
��ڲ�����uint8 led_idx  (��ȡֵLED_1��LED_2��LED_3��LED_4)
����ֵ����
 *************************************************************************/
void led_off(uint8 led_idx)
{
  switch(led_idx)
	{
		case LED_1:
      LED_D1=1;	       //����P2.6�˿�����ߵ�ƽ��Ϩ���û�ָʾ��D1
		  break;		
		case LED_2:
      LED_D2=1;        //����P2.7�˿�����ߵ�ƽ��Ϩ���û�ָʾ��D2
		  break;
		case LED_3:
      LED_D3=1;	       //����P7.2�˿�����ߵ�ƽ��Ϩ���û�ָʾ��D3
		  break;		
		case LED_4:
      LED_D4=1;        //����P7.1�˿�����ߵ�ƽ��Ϩ���û�ָʾ��D4
		  break;
		default:
		  break;
  }
}

/**************************************************************************
������������תһ��ָ����ָʾ��(D1��D2��D3��D4)
��ڲ�����uint8 led_idx  (��ȡֵLED_1��LED_2��LED_3��LED_4)
����ֵ����
*************************************************************************/
void led_toggle(uint8 led_idx)
{
  switch(led_idx)
	{
		case LED_1:
      LED_D1=~LED_D1;	   //����P2.6�˿������ͬ����һ�εĵ�ƽ����ת�û�ָʾ��D1
		  break;		
		case LED_2:
      LED_D2=~LED_D2;    //����P2.7�˿������ͬ����һ�εĵ�ƽ����ת�û�ָʾ��D2
		  break;
		case LED_3:
      LED_D3=~LED_D3;	   //����P7.2�˿������ͬ����һ�εĵ�ƽ����ת�û�ָʾ��D3
		  break;		
		case LED_4:
      LED_D4=~LED_D4;    //����P7.1�˿������ͬ����һ�εĵ�ƽ����ת�û�ָʾ��D4
		  break;
		default:
		  break;
  }
}

/**************************************************************************
���������������������ϵ�4��ָʾ��(D1��D2��D3��D4)
��ڲ�������
����ֵ����
 *************************************************************************/
void leds_on(void)
{
		LED_D1=0;	       //����P2.6�˿�����͵�ƽ�������û�ָʾ��D1
		LED_D2=0;        //����P2.7�˿�����͵�ƽ�������û�ָʾ��D2
	  LED_D3=0;        //����P7.2�˿�����͵�ƽ�������û�ָʾ��D3
	  LED_D4=0;        //����P7.1�˿�����͵�ƽ�������û�ָʾ��D4
}

/**************************************************************************
����������Ϩ�𿪷����ϵ�4��ָʾ��(D1��D2��D3��D4)
��ڲ�������
����ֵ����
 *************************************************************************/
void leds_off(void)
{
		LED_D1=1;	       //����P2.6�˿�����ߵ�ƽ��Ϩ���û�ָʾ��D1
		LED_D2=1;        //����P2.7�˿�����ߵ�ƽ��Ϩ���û�ָʾ��D2
	  LED_D3=1;        //����P7.2�˿�����ߵ�ƽ��Ϩ���û�ָʾ��D3
	  LED_D4=1;        //����P7.1�˿�����ߵ�ƽ��Ϩ���û�ָʾ��D4
}

/**************************************************************************
������������ˮ��
��ڲ�������
����ֵ����
 *************************************************************************/
void LED_Blink(void)
{
		leds_off();	          //Ϩ�������û�ָʾ��
		led_on(LED_1);        //�����û�ָʾ��D1
		delay_ms(300);
		leds_off();	          //Ϩ�������û�ָʾ��
		led_on(LED_2);        //�����û�ָʾ��D2
		delay_ms(300);
		leds_off();	          //Ϩ�������û�ָʾ��
		led_on(LED_3);        //�����û�ָʾ��D3
		delay_ms(300);
		leds_off();	          //Ϩ�������û�ָʾ��
		led_on(LED_4);        //�����û�ָʾ��D4
		delay_ms(300);
		leds_off();	          //Ϩ�������û�ָʾ��
		delay_ms(300);
}

/*********************************END FILE********************************************/	
