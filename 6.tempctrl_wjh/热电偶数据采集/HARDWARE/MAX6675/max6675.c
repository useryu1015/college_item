#include "max6675.h"
#include "stm32f10x.h"
#include "usart.h"

#define 	MAX6675_CS	 		GPIO_Pin_4
#define 	MAX6675_CSL()		GPIOA->BRR = MAX6675_CS;
#define 	MAX6675_CSH()		GPIOA->BSRR = MAX6675_CS;

int sensor_state = 0;

void SPI_MAX6675_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;	
	
	/* Ê¹ÄÜ SPI1 Ê±ÖÓ */                         
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

	/* ---------Í¨ÐÅI/O³õÊ¼»¯----------------
	 * PA5-SPI1-SCK :MAX6675_SCK
	 * PA6-SPI1-MISO:MAX6675_SO
	 * PA7-SPI1-MOSI:MAX6675_SI	 
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// ¸´ÓÃÊä³ö
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ---------¿ØÖÆI/O³õÊ¼»¯----------------*/
	/* PA4-SPI1-NSS:MAX6675_CS */							// Æ¬Ñ¡
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// ÍÆÃâÊä³ö
	GPIO_Init(GPIOA, &GPIO_InitStructure);						  
	GPIO_SetBits(GPIOA, GPIO_Pin_4);						// ÏÈ°ÑÆ¬Ñ¡À­¸ß£¬ÕæÕýÓÃµÄÊ±ºòÔÙÀ­µÍ
 

	/* SPI1 ÅäÖÃ */ 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	
	
	/* Ê¹ÄÜ SPI1  */
	SPI_Cmd(SPI1, ENABLE); 
}

/*
 *
 *
 *
 */
unsigned char MAX6675_ReadByte(void)
{
	
	/* Loop while DR register in not emplty */
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
	
	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI1, 0xff);
	
	/* Wait to receive a byte */
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI1);
}


float read_max6675 (void)
{
	unsigned int t,i;
	unsigned char c;
	unsigned char flag;
	float temprature;
//	/* 配置系统时钟 72M */
//	SystemInit();
//  
//	/* MAX6675 SPI init */
//	SPI_MAX6675_Init();
//	uart_init(115200);		// 初始化串口
	
    if (1)
	{
		MAX6675_CSL();
		c = MAX6675_ReadByte();
		i = c;
		i = i<<8;
		c = MAX6675_ReadByte();
		MAX6675_CSH();
		
		i = i|((unsigned int)c);			// i 读出的是原始数据
		flag = i&0x04;						// flag保存热电偶的连接状态
		t = i<<1;
		t = t>>4;
		temprature = t*0.25;                
		
		if(i!=0)							// max6675有数据返回
		{
			if(flag==0)						// 热电偶已连接
			{
				sensor_state = 0;
				printf("old data: %04X,  now temp: %4.2f\r\n",i,temprature);
        return temprature;
			}	
			else							// 热电偶掉线
			{
				sensor_state = 1;
				printf("no max66\r\n");
			}
		
		}
		else								//max6675 没有数据返回
		{
			sensor_state = 2;
			printf("max6675 wrong\r\n");
		}
		// for(i=0;i<0x2fffff;i++);			// 热电偶转换时间是0.2秒，间隔
	}

    return temprature;
}

