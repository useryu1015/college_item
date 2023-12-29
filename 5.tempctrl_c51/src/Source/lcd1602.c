#include "lcd1602.h"	

/*******************************************************************
功能描述：LCD1602写命令函数 
入口参数?uuint8 com
返回值：无
********************************************************************/
void lcd_wcom(uint8 com)
{
    lcd1602_rs=0;               //选择指令寄存器
    lcd1602_rw=0;               //选择写操作
    P6=com;                     //把命令送入到LCD1602屏8位数据口
    delay_ms(1);                //延时，LCD1602准备接收数据
	
	  //控制LCD1602使能引脚产生高电平到低电平的跳变，液晶模块执行命令
    lcd1602_en=1;               //使能引脚置高电平
    lcd1602_en=0;               //使能引脚置低电平
} 

/*******************************************************************
功能描述：LCD1602写数据函数 
入口参数：uint8 dat
返回值：无
********************************************************************/
void lcd_wdat(uint8 dat)          
{ 
    lcd1602_rs=1;               //选择数据寄存器 
    lcd1602_rw=0;               //选择写操作
    P6=dat;                     //把命令送入到LCD1602屏8位数据口
    delay_ms(1);                //延时，LCD1602准备接收数据
	
	  //控制LCD1602使能引脚产生高电平到低电平的跳变，液晶模块执行命令
    lcd1602_en=1;               //使能引脚置高电平
    lcd1602_en=0;               //使能引脚置低电平
} 

/*******************************************************************
功能描述：LCD1602初始化函数 
入口参数：无
返回值：无
********************************************************************/
void lcd_init(void)                 
{ 
    lcd_wcom(0x38);       //8位数据，双列，5*7字形       
    lcd_wcom(0x0c);       //开启显示屏，关光标，光标不闪烁 
    lcd_wcom(0x06);       //显示地址递增，即写一个数据后，显示位置右移一位 
    lcd_wcom(0x01);       //清屏 
} 		

/*******************************************************************
功能描述：LCD1602按指定位置显示一个字符
入口参数：uint8 X, uint8 Y, uint8 DData
返回值：无
********************************************************************/
void DisplayOneChar(uint8 X, uint8 Y, uint8 DData)
{
	Y &= 0x1;
	X &= 0xF; //限制X不能大于15，Y不能大于1
	if (Y) X |= 0x40; //当要显示第二行时地址码+0x40;
	X |= 0x80; //算出指令码
	lcd_wcom(X); //发命令字
	lcd_wdat(DData); //发数据
}

/*******************************************************************
功能描述：LCD1602按指定位置显示一串字符
入口参数：uint8 X, uint8 Y, uint8 DData  X代表第X+1列，Y代表第Y+1行
返回值：无
********************************************************************/
void DisplayListChar(uint8 X, uint8 Y, uint8 code *DData)
{
	uint8 ListLength;

  ListLength = 0;
	Y &= 0x1;
	X &= 0xF; //限制X不能大于15，Y不能大于1
	while (DData[ListLength]>0x19) //若到达字串尾则退出
		{
			if (X <= 0xF)        //X坐标应小于0xF
				{
					DisplayOneChar(X, Y, DData[ListLength]); //显示单个字符
					ListLength++;
					X++;
				}
		}
}

/*********************************END FILE********************************************/	


