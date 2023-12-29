#include "sys.h"
#include "beep.h"



void BEEP_Init(void){
	
	//IO???
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//?IO?????
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //????,???????IC??????????????(5K)
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	BEEP = 1;
	
	//DHT11_Rst();//??????
	
	//eturn DHT11_Check();//??DHT11???

}






