#include "sys.h"
#include "key.h"



void KEY_Init(void){
	
	//IO???
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//?IO?????
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	// 默认上拉输入，高电平
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	
	//DHT11_Rst();//??????
	//eturn DHT11_Check();//??DHT11???

}


u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;//????????????
	if(mode)key_up=1;  //???????		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==0))
	{
		delay_ms(10);//????? 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(WK_UP==0)return WKUP_PRES; 
	}else if(KEY0==1&&KEY1==1&&WK_UP==1)key_up=1; 	     
	return 0;// ?????????
}


