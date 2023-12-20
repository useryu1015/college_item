#include "stm32f10x.h"
#include "HC-SR501.h"
#include "led.h"
#include "usart.h"
#include "cled.h"

int HW_Sign = 0x0000;				// 判断(记录)红外传感器状态 的标志


// 人体红外传感器初始化
void HCSR501_Init(void)			// 中断线16条，尽量别用相同编号？
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_4;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		//设置成上拉输入  // 下拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);						//初始化GPIOC6,7  // PC0,4    PC5-9好像共用一个外部中断函数......
	
}







// 红外状态扫描函数；
void HW_Scan(void)
{
	if (HW1 == ENABLE)				// ENABLE != 0; 即非零；	// 模块特性： 自带可调响应延时，程序不用再延时，且便于硬件控制；
		HW_Sign |= 0x0001;
	else
		HW_Sign &= 0xFFFE;			// 1110
	
	if (HW2 == ENABLE)
		HW_Sign |= 0x0002;
	else
		HW_Sign &= 0xFFFD;			// 1101        // 1011 == B		0111 == 7		1101 == D		1110 == E
	
	
	if (HW_Sign == 0x0000)		// 节能.....
	{
		TIM3_DISABLE(1);	
		//printf("TIM3_定时器已关闭		\r\n");
	}
	else
		TIM_Cmd(TIM3, ENABLE); 	// 使能定时器；


}






