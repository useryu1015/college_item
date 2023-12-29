#include	"lcd1602.h"
#include  "delay.h"
#include  "uart.h"
#include  "dht11.h"
#include  "beep.h"
#include  "fire.h"
#include  "MQ-2.h"
#include  "key.h"

#define DEF1 10		// 
#define DEF2 20


uint8 code table1[]="LCD1602 check ok";				//Ҫ��ʾ������1��������table1
uint8 code table2[]="test = ";                //Ҫ��ʾ������2��������table2
uint8 code table3[]={0,1,2,3,4,5,6,7,8,9};    //��������0-9

void show_DHT11(void);
/*************************************************************************
����������������
��ڲ�������
����ֵ����
*************************************************************************/
int main(void)
{
	//uint8 i;		
	// ���ڳ�ʼ����		 ����ע�͵�
	DATA_PIN=1;                                   //�������� 
	Uart1_Init();                                 //����1��ʼ��
	EA = 1;                                       //ʹ�����ж�
 	delay_ms(10);                                 //��ʼ������ʱ
	
	// DHT11 ��ʼ��
	P3M1 &= 0xFE;	P3M0 &= 0xFE;	                  //����P3.0Ϊ׼˫���
	P3M1 &= 0xFD;	P3M0 |= 0x02;	                  //����P3.1Ϊ�������
	

	// ��ʼ��
	P2M1 &= 0xFE;	P2M0 |= 0x01;		// ��������ʼ����	����P2.0Ϊ�������	
	Sensor_OUT = 0;          //������������
	
	// ����������ʼ��
	P5M1 &= 0xEF;	P5M0 &= 0xEF;	  //����P5.4Ϊ׼˫��� 			// ����������

	DisplayListChar(0, 0, table1);       //�ӵ�һ�е�1�п�ʼ��ʾtable1
	DisplayListChar(2, 1, table2);       //�ӵڶ��е�3�п�ʼ��ʾtable2
	

	
	// LCD Init
	lcd_init();                          //Һ������ʼ�� 
	delay_ms(10);
	DisplayListChar(1, 0, "sys init...");			//�ӵ�һ�е�2�п�ʼ��ʾ	
	
	while(1)
	{
		Sensor_OUT = 0;          //������������
		/******************	�¿�&��ʾ���� ***************************/
		Read_DHT11();			// ��ȡDHT11��ʪ��ֵ
		//Read_DS18B20();			// xxx
		show_DHT11();			// lcd��ʾ�¶�ֵ
		

		/******************	�������� ***************************/
		fire_heartbeat();		// ���洫����
		MQ2_heartbeat();		// ��������⺯��				// �ߵ͵�ƽ�ź�      
		KEY_Scan();					// ��������ֹ��ť			      
		//beep_heartbeat();		// ������ ״̬����
		
		
		//SendDataByUart1(fire_state);	SendDataByUart1(MQ2_state);	SendDataByUart1(key_state);
		
		SendStringByUart1("test \r\n");
	
		delay_ms(1000);	  		//��ʱ
	}
}



void show_DHT11(void){
	//����ʪ��ֵת��Ϊ�ַ���
	uint8 tempH = DHT11Value.tempH + 0x30;
	uint8 tempL = DHT11Value.tempL + 0x30;
	uint8 humidityH = DHT11Value.humyH + 0x30;
	uint8 humidityL = DHT11Value.humyL + 0x30;

	lcd_wcom(0x01); //����

	DisplayListChar(1, 0, "TEMP");			//�ӵ�һ�е�2�п�ʼ��ʾ	
	DisplayOneChar(1, 1, tempH);			// ��ʾ�¶ȸ�λ
	DisplayOneChar(2, 1, tempL);			// ��ʾ�¶ȵ�λ

	DisplayListChar(8, 0, "HUMI");			// �ӵ�һ�е�89�п�ʼ��ʾ
	//DisplayOneChar(8, 1, humidityH);		// ��ʾ ��λ
	//DisplayOneChar(9, 1, humidityL);		// ��ʾ ��λ	
	
	
	DisplayOneChar(7, 1, fire_state + 0x30 );			// ��ʾ�¶ȸ�λ
	DisplayOneChar(9, 1, MQ2_state + 0x30 );			// ��ʾ�¶ȸ�λ
	DisplayOneChar(10, 1, key_state + 0x30 );			// ��ʾ�¶ȸ�λ
	

}