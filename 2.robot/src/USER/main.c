#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "sg90.h"
#include "robot.h"

int main(void)
{
	u16 led0pwmval=0;
	u8 dir=1;
	u8 i;

	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
 	LED_Init();
	
 	TIM3_PWM_Init(20000-1,72-1);
	TIM3_Int_Init(20000-1,72-1);
	
	Set_RobotPT(0);
	delay_ms(5000);
	
   	while(1)
	{
		Module_Pallet1();
	}

}

