#include  "dht11.h" 
#include  "uart.h"	

uint8 u8T_data_H_temp,u8T_data_L_temp,u8RH_data_H_temp,uRH_data_L_temp,u8checkdata_temp;
DHT11VALUE DHT11Value;

/**************************************************************************************
 * ��  �� : ��ʱ����
 * ��  �� : 10us��������
 * ����ֵ : ��
 **************************************************************************************/
void delay_10us(uint8 x)
{
  uint8 i;

  for (i = 0; i < x; i++) 
	{
		 Delay10us();
  }
}

 /**************************************************************************************
 * ��  �� : ��DHT11��ȡһ���ֽڣ�MSB����
 * ��  �� : ��
 * ����ֵ : uint8
 **************************************************************************************/
static uint8 Read_Byte(void)
{
	uint8 i, temp=0;

	for(i=0;i<8;i++)    
	{	   
		while(!DATA_PIN);  //ÿbit��50us�͵�ƽ���ÿ�ʼ����ѯֱ���ӻ����� ��50us �͵�ƽ ����

		/*DHT11 ��23~27us�ĸߵ�ƽ��ʾ��0������68~74us�ĸߵ�ƽ��ʾ��1��  */
		delay_10us(4); //��ʱԼ40us,�����ʱ��Ҫ��������0������ʱ�伴��	   	  

		if(DATA_PIN)   //Լ40us����Ϊ�ߵ�ƽ��ʾ���ݡ�1��
		{
			while(DATA_PIN);  //�ȴ�����1�ĸߵ�ƽ����
			temp|=(uint8)(0x01<<(7-i));  //�ѵ�7-iλ��1��MSB���� 
		}
		else	 //40us��Ϊ�͵�ƽ��ʾ���ݡ�0��
		{			   
			temp&=(uint8)~(0x01<<(7-i)); //�ѵ�7-iλ��0��MSB����
		}
	}
	return temp;	
}

 /**************************************************************************************
 * ��  �� : һ�����������ݴ���Ϊ40bit����λ�ȳ�
 * ��  �� : 8bit ʪ������ + 8bit ʪ��С�� + 8bit �¶����� + 8bit �¶�С�� + 8bit У��� 
 * ����ֵ : ��
 **************************************************************************************/
void Read_DHT11(void)   //��ʪ��������
{
	  uint8 u8T_data_H,u8T_data_L,u8RH_data_H,u8RH_data_L,u8checkdata,uchartemp;
	
	  DATA_PIN=0;         //��������
    delay_ms(20);       //��ʱ20ms�������18ms
    DATA_PIN=1;         //�������� ������ʱ30us
    delay_10us(3);      //��ʱԼ30us
	
    if(!DATA_PIN)       //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������   
    {
			  while(!DATA_PIN);   //��ѯֱ���ӻ�������83us �͵�ƽ ��Ӧ�źŽ���
			  while(DATA_PIN);    //��ѯֱ���ӻ�������87us �ߵ�ƽ �����źŽ���
			
			  /*��ʼ��������*/ 
        u8RH_data_H_temp= Read_Byte();
        uRH_data_L_temp= Read_Byte();
        u8T_data_H_temp= Read_Byte();
        u8T_data_L_temp= Read_Byte();
        u8checkdata_temp= Read_Byte();
			
        DATA_PIN=1;                   //��ȡ��������������
			
			  /*����ȡ�������Ƿ���ȷ*/
        uchartemp=(u8T_data_H_temp+u8T_data_L_temp+u8RH_data_H_temp+uRH_data_L_temp);
        if(uchartemp==u8checkdata_temp)   //У��
        {
            u8RH_data_H=u8RH_data_H_temp;
            u8RH_data_L=uRH_data_L_temp;
            u8T_data_H=u8T_data_H_temp;
            u8T_data_L=u8T_data_L_temp;
            u8checkdata=u8checkdata_temp;
        }				
        DHT11Value.tempH = u8T_data_H/10; 
        DHT11Value.tempL = u8T_data_H%10;
        
        DHT11Value.humyH = u8RH_data_H/10; 
        DHT11Value.humyL = u8RH_data_H%10; 					
    } 
    else      //û�ܳɹ���ȡ������0
    {
        DHT11Value.tempH = 0; 
        DHT11Value.tempL = 0;        
        DHT11Value.humyH = 0; 
        DHT11Value.humyL = 0;  	
    }  
}

/**************************************************************************************
 * ��  �� : ����ʵʱ��ʾ��ʪ��
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void DHT11_TEST(void)
{
	  static uint8 temp[3]; 
    static uint8 humidity[3];   

	  memset(temp, 0, 3);                             //��temp�����ʼ�������㣩
    memset(humidity, 0, 3);                         //��humidity�����ʼ�������㣩
		
	  Read_DHT11();                                   //��ȡ��ʪ��ֵ
		
	  //����ʪ��ֵת��Ϊ�ַ���
	  temp[0] = DHT11Value.tempH + 0x30;
    temp[1] = DHT11Value.tempL + 0x30;
    humidity[0] = DHT11Value.humyH + 0x30;
    humidity[1] = DHT11Value.humyL + 0x30;
		
		//���ڴ�ӡ��ʪ��ֵ
    SendStringByUart1("Temperature:");
    SendStringByUart1(temp);    // ����ָ��       temp[2] = 0;   so while end
    SendStringByUart1("   ");
    SendStringByUart1("Humidity:");
    SendStringByUart1(humidity);
    SendStringByUart1("\r\n");	
}


/*********************************END FILE*************************************/