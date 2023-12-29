#include  "dht11.h" 
#include  "uart.h"	

uint8 u8T_data_H_temp,u8T_data_L_temp,u8RH_data_H_temp,uRH_data_L_temp,u8checkdata_temp;
DHT11VALUE DHT11Value;

/**************************************************************************************
 * 描  述 : 延时函数
 * 入  参 : 10us的整数倍
 * 返回值 : 无
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
 * 描  述 : 从DHT11读取一个字节，MSB先行
 * 入  参 : 无
 * 返回值 : uint8
 **************************************************************************************/
static uint8 Read_Byte(void)
{
	uint8 i, temp=0;

	for(i=0;i<8;i++)    
	{	   
		while(!DATA_PIN);  //每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束

		/*DHT11 以23~27us的高电平表示“0”，以68~74us的高电平表示“1”  */
		delay_10us(4); //延时约40us,这个延时需要大于数据0持续的时间即可	   	  

		if(DATA_PIN)   //约40us后仍为高电平表示数据“1”
		{
			while(DATA_PIN);  //等待数据1的高电平结束
			temp|=(uint8)(0x01<<(7-i));  //把第7-i位置1，MSB先行 
		}
		else	 //40us后为低电平表示数据“0”
		{			   
			temp&=(uint8)~(0x01<<(7-i)); //把第7-i位置0，MSB先行
		}
	}
	return temp;	
}

 /**************************************************************************************
 * 描  述 : 一次完整的数据传输为40bit，高位先出
 * 入  参 : 8bit 湿度整数 + 8bit 湿度小数 + 8bit 温度整数 + 8bit 温度小数 + 8bit 校验和 
 * 返回值 : 无
 **************************************************************************************/
void Read_DHT11(void)   //温湿传感启动
{
	  uint8 u8T_data_H,u8T_data_L,u8RH_data_H,u8RH_data_L,u8checkdata,uchartemp;
	
	  DATA_PIN=0;         //主机拉低
    delay_ms(20);       //延时20ms，需大于18ms
    DATA_PIN=1;         //总线拉高 主机延时30us
    delay_10us(3);      //延时约30us
	
    if(!DATA_PIN)       //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行   
    {
			  while(!DATA_PIN);   //轮询直到从机发出的83us 低电平 响应信号结束
			  while(DATA_PIN);    //轮询直到从机发出的87us 高电平 标置信号结束
			
			  /*开始接收数据*/ 
        u8RH_data_H_temp= Read_Byte();
        uRH_data_L_temp= Read_Byte();
        u8T_data_H_temp= Read_Byte();
        u8T_data_L_temp= Read_Byte();
        u8checkdata_temp= Read_Byte();
			
        DATA_PIN=1;                   //读取结束，主机拉高
			
			  /*检查读取的数据是否正确*/
        uchartemp=(u8T_data_H_temp+u8T_data_L_temp+u8RH_data_H_temp+uRH_data_L_temp);
        if(uchartemp==u8checkdata_temp)   //校验
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
    else      //没能成功读取，返回0
    {
        DHT11Value.tempH = 0; 
        DHT11Value.tempL = 0;        
        DHT11Value.humyH = 0; 
        DHT11Value.humyL = 0;  	
    }  
}

/**************************************************************************************
 * 描  述 : 串口实时显示温湿度
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************************/
void DHT11_TEST(void)
{
	  static uint8 temp[3]; 
    static uint8 humidity[3];   

	  memset(temp, 0, 3);                             //将temp数组初始化（清零）
    memset(humidity, 0, 3);                         //将humidity数组初始化（清零）
		
	  Read_DHT11();                                   //获取温湿度值
		
	  //将温湿度值转换为字符串
	  temp[0] = DHT11Value.tempH + 0x30;
    temp[1] = DHT11Value.tempL + 0x30;
    humidity[0] = DHT11Value.humyH + 0x30;
    humidity[1] = DHT11Value.humyL + 0x30;
		
		//串口打印温湿度值
    SendStringByUart1("Temperature:");
    SendStringByUart1(temp);    // 数组指针       temp[2] = 0;   so while end
    SendStringByUart1("   ");
    SendStringByUart1("Humidity:");
    SendStringByUart1(humidity);
    SendStringByUart1("\r\n");	
}


/*********************************END FILE*************************************/