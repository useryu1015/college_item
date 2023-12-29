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


uint8 code table1[]="LCD1602 check ok";				//要显示的内容1放入数组table1
uint8 code table2[]="test = ";                //要显示的内容2放入数组table2
uint8 code table3[]={0,1,2,3,4,5,6,7,8,9};    //常量数组0-9

void show_DHT11(void);
/*************************************************************************
功能描述：主函数
入口参数：无
返回值：无
*************************************************************************/
int main(void)
{
	//uint8 i;		
	// 串口初始化：		 可以注释掉
	DATA_PIN=1;                                   //总线拉高 
	Uart1_Init();                                 //串口1初始化
	EA = 1;                                       //使能总中断
 	delay_ms(10);                                 //初始化后延时
	
	// DHT11 初始化
	P3M1 &= 0xFE;	P3M0 &= 0xFE;	                  //设置P3.0为准双向口
	P3M1 &= 0xFD;	P3M0 |= 0x02;	                  //设置P3.1为推挽输出
	

	// 初始化
	P2M1 &= 0xFE;	P2M0 |= 0x01;		// 蜂鸣器初始化：	设置P2.0为推挽输出	
	Sensor_OUT = 0;          //蜂鸣器不鸣响
	
	// 触摸按键初始化
	P5M1 &= 0xEF;	P5M0 &= 0xEF;	  //设置P5.4为准双向口 			// 触摸按键；

	DisplayListChar(0, 0, table1);       //从第一行第1列开始显示table1
	DisplayListChar(2, 1, table2);       //从第二行第3列开始显示table2
	

	
	// LCD Init
	lcd_init();                          //液晶屏初始化 
	delay_ms(10);
	DisplayListChar(1, 0, "sys init...");			//从第一行第2列开始显示	
	
	while(1)
	{
		Sensor_OUT = 0;          //蜂鸣器不鸣响
		/******************	温控&显示部分 ***************************/
		Read_DHT11();			// 获取DHT11温湿度值
		//Read_DS18B20();			// xxx
		show_DHT11();			// lcd显示温度值
		

		/******************	警报部分 ***************************/
		fire_heartbeat();		// 火焰传感器
		MQ2_heartbeat();		// 传感器检测函数				// 高低电平信号      
		KEY_Scan();					// 蜂鸣器终止按钮			      
		//beep_heartbeat();		// 蜂鸣器 状态更新
		
		
		//SendDataByUart1(fire_state);	SendDataByUart1(MQ2_state);	SendDataByUart1(key_state);
		
		SendStringByUart1("test \r\n");
	
		delay_ms(1000);	  		//延时
	}
}



void show_DHT11(void){
	//将温湿度值转换为字符串
	uint8 tempH = DHT11Value.tempH + 0x30;
	uint8 tempL = DHT11Value.tempL + 0x30;
	uint8 humidityH = DHT11Value.humyH + 0x30;
	uint8 humidityL = DHT11Value.humyL + 0x30;

	lcd_wcom(0x01); //清屏

	DisplayListChar(1, 0, "TEMP");			//从第一行第2列开始显示	
	DisplayOneChar(1, 1, tempH);			// 显示温度高位
	DisplayOneChar(2, 1, tempL);			// 显示温度低位

	DisplayListChar(8, 0, "HUMI");			// 从第一行第89列开始显示
	//DisplayOneChar(8, 1, humidityH);		// 显示 高位
	//DisplayOneChar(9, 1, humidityL);		// 显示 低位	
	
	
	DisplayOneChar(7, 1, fire_state + 0x30 );			// 显示温度高位
	DisplayOneChar(9, 1, MQ2_state + 0x30 );			// 显示温度高位
	DisplayOneChar(10, 1, key_state + 0x30 );			// 显示温度高位
	

}