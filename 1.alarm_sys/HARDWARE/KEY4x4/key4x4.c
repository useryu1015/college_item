#include "stm32f10x.h"
#include "key4x4.h"
#include "sys.h" 
#include "delay.h"
#include "usart.h"


/*************************
X：
	PEin	7-10

Y：
	PEout	11-14
*************************/


// 矩阵按键初始化函数
void KEY4x4_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;//KEY0-KEY1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成下拉输入
		GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;				 //LED0-->PB.5 端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		GPIO_Init(GPIOE, &GPIO_InitStructure);							 //根据设定参数初始化GPIOE
}

// 使所有输出拉低；初始化；		// 可以使用define定义，执行速度更快！！！
static void KEY_ALL_Pull_Down(void)
{
	KEY_Y(11) = 0;
	KEY_Y(12) = 0;
	KEY_Y(13) = 0;
	KEY_Y(14) = 0;
}


// 4x4按键扫描函数
// 使用一个嵌套循环，完成扫描X和Y；
// 原理： 通过Y 依次输出高电平,
//				扫描X 那个IO口输入高电平；
// X轴：输入检查、扫描；
// Y轴：设置输出状态；
// 该函数适合任意排列矩阵按键，只需修改循环中对应编号！！
// 注意： 1. 改变IO口时，该函数还需要改变循环中IO口编号；（可以定义好IO口编号，便于修改）
//				2. 该函数同样有优先级问题！ 即同时按下时，只反馈先被扫描到的（0-15标号最小的）
//				3. 函数同一坐标轴的IO口编号必须相邻或能有 规律递增可寻；（否则无法用循环判断）
//				4. 暂时未添加功能（模式）：	按键复用 和 长按；
// 2020-11-13		返回值调整为	1-16
// 11/14 不支持连按；
u8 KEY4x4_Scan(void)
{
	int i,j;							// 坐标；
	static u8 IO_Sign = 1;				// 很简便的一个IO反馈方式标签！！！  且嵌套循环特有！！  // 能返回0-15，适合任意排列矩阵按键
	static u8 key_up = 1;	// 按键按松开标志;  
	
	IO_Sign = 1;
	
	for (i = 11; i <= 14; i++)							// Y输出IO口编号；
		for (j = 7; j <= 10; j++,IO_Sign++)		// X输出IO口编号；  // 递增IO_Sign，反馈对应值（0-15）；
		{
			KEY_Y(i) = 1;			// 使PEout(i)输出高电平；
			
			if (KEY_Y(i))			// 扫描Y输出高电平， 可以取消此判断； 因为必须输出高电平时，才能正常判断！！
			{
				if (KEY_X(j) && key_up)		// 当输入检查到高电平时；
				{
					key_up = 0;
					printf("按键扫描： %d  \r\n",IO_Sign);
					return IO_Sign;
				}
				else if (!KEY_X(7)&&!KEY_X(8)&&!KEY_X(9)&&!KEY_X(10))			// 当所有输入检测到低电平时，使能按键；
				{
					key_up = 1;
					KEY_ALL_Pull_Down();										// 初始化所有按键输出拉低；	// 必须放在此位置，否则XXXX不能正确判断条件；
				}
					
			}
			else
				printf("PEout:IO口%d输出异常！  \r\n ", i);
		}
		
	delay_ms(10);					// 按键防抖；
	return 0;
}

// 标准按键扫描函数；
// 支持连按；
// 11/23 不禁用此函数，按键串扰？？？
u8 KEY16_Scan(void)
{
	int i,j;
	u8 IO_Sign = 1;				// 很简便的一个IO反馈方式标签！！！  且嵌套循环特有！！  // 能返回0-15，适合任意排列矩阵按键
	
	ALL_DOWN_KEY_Y													// 初始化所有按键输出拉低；
	
	for (i = 11; i <= 14; i++)							// Y输出IO口编号；
		for (j = 7; j <= 10; j++,IO_Sign++)		// X输出IO口编号；  // 递增IO_Sign，反馈对应值（0-15）；
		{
			KEY_Y(i) = 1;			// 使PEout(i)输出高电平；

			if (KEY_X(j))			// 当输入检查到高电平时；
				return IO_Sign;
		}
		
	delay_ms(20);					// 按键防抖；  // 并控制连按延时；
}
