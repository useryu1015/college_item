#include "clock.h"
#include "oled.h"
#include "delay.h"

#include "usart.h"
#include "stdbool.h"

bool sign = true;			// 闹钟标志： 默认： 开
int AlramValue = 0;


/******************* ************************************************************   11 / 15 -------------------------------
* 显示部分
*******************/


/*
// 显示主界面汉字，箭头等；
void Show_Chinese(void)
{
		OLED_ShowCHinese(6,0,4); 			// 日
		OLED_ShowCHinese(26,0,5);			// 期
		OLED_ShowString(42,0,":",16); // :
//		OLED_ShowCHinese(6,2,6); 			// 时
//		OLED_ShowCHinese(6,4,7);			// 间
	
		OLED_ShowString(93,7,"menu",8);
		
	
		Move_Menu_Point(80,7,8,500);				// 在坐标(80,7)显示箭头；
}

// 显示日期；
void Show_Date(u8 value)
{
		if (value == 1)			// 日期主界面；
		{
			OLED_ShowNum(8+46,1,DateYear,4,12);		
			OLED_ShowString(33+46,1,"/",12);
			OLED_ShowNum(40+46,1,DateMonth / 10,1,12);		// 十位显示
			OLED_ShowNum(47+46,1,DateMonth % 10,1,12);		// 个位
			OLED_ShowString(54+46,1,"/",12);
			OLED_ShowNum(61+46,1,DateDay / 10,1,12);	
			OLED_ShowNum(68+46,1,DateDay % 10,1,12);			
		}
		if (value == 2)			// 日期设置界面；
		{
			OLED_ShowNum(5+16,3,DateYear,4,16);		
			OLED_ShowString(38+16,3,"/",16);
			OLED_ShowNum(47+16,3,DateMonth / 10,1,16);		// 十位显示
			OLED_ShowNum(55+16,3,DateMonth % 10,1,16);		// 个位
			OLED_ShowString(64+16,3,"/",16);
			OLED_ShowNum(73+16,3,DateDay / 10,1,16);	
			OLED_ShowNum(81+16,3,DateDay % 10,1,16);				
		}
}

// 显示时间；
void Show_Time(void)
{
		int row = -2;
		
//		Date_Update();			// 更新日期；

		OLED_ShowNum(22+row,3,ClockHour / 10,1,16);			// 显示小时。			
		OLED_ShowNum(32+row,3,ClockHour % 10,1,16);			// 显示小时。	
		OLED_ShowString(40+row,3,":",16);
	
		OLED_ShowNum(48+row,3,ClockMin / 10,1,16);			// 显示分钟。
		OLED_ShowNum(58+row,3,ClockMin % 10,1,16);			// 显示分钟。
		OLED_ShowString(66+row,3,":",16);	
	
		OLED_ShowNum(74+row,3,ClockSec / 10,1,16);			// 显示秒数。 十位	// 拆分数值每位显示，能正确显示0X；
		OLED_ShowNum(84+row,3,ClockSec % 10,1,16);			// 显示秒数。	个位
		OLED_ShowString(92+row,4,".",8);
	
		OLED_ShowNum(97+row,4,msCount/100,1,8);		// 显示毫秒。
		OLED_ShowNum(104+row,4,(msCount/10) % 10,1,15);		// 显示毫秒。

		
//		//判断当小于10时； 显示补零；    BUG： 显示时若隐若现；不坚定；  DEBUG： 每次重复执行时；都会自动刷新？  // 每次只执行一次；
//		if (ClockHour < 10)
//			OLED_ShowNum(20,4,0,1,16);
//		if (ClockMin < 10)
//			OLED_ShowNum(48,4,0,1,16);
//		if (ClockSec < 10)
//			OLED_ShowNum(76,4,0,1,16);
//		if (msCount < 10)
//			OLED_ShowNum(97,5,0,1,15);
		
}




// 显示闹钟
// 参数： 月份、日期、小时、分钟；
void Show_Alarm(void)
{
	int row = 0;
	
	OLED_ShowNum(22+row,3,ClockHour / 10,1,16);			// 显示小时。			
	OLED_ShowNum(32+row,3,ClockHour % 10,1,16);			// 显示小时。	
	OLED_ShowString(40+row,3,":",16);

	OLED_ShowNum(48+row,3,ClockMin / 10,1,16);			// 显示分钟。
	OLED_ShowNum(58+row,3,ClockMin % 10,1,16);			// 显示分钟。
	
	
	OLED_ShowNum(73+row,3,DateMonth / 10,1,16);		// 十位显示
	OLED_ShowNum(81+row,3,DateMonth % 10,1,16);		// 个位
	OLED_ShowString(89+row,3,"/",16);
	OLED_ShowNum(99+row,3,DateDay / 10,1,16);	
	OLED_ShowNum(107+row,3,DateDay % 10,1,16);		
	
	//73+row,81+row,99+row,107+row
}






// 闹钟开关；
void Set_Alarm_Switch(void)
{
	int Key = 0;
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"ChildMenu-Alarm",16);
	OLED_ShowString(32,2,"Alarm: ",16);
	
	while (1)
	{
		Key = KEY4x4_Scan();
		delay_ms(20);
		
		OLED_Clear8x8(96,2,4,2);					// 会闪屏，换个位置即可；					OLED_Clear8x8(96,2,4,2);	
		if (sign == true)
			OLED_ShowString(96,2,"ON",16);
		if (sign == false)
			OLED_ShowString(96,2,"OFF",16);
		
		switch (Key)
		{
			case KEY_B: 
				sign = !sign;
				break;
			case KEY_C:
				sign = !sign;
				break;
			case KEY_D:
				GO_HOME
				break;
			case KEY_ENTER: 						// 这个位置可以自定义菜单选项；其他功能；
				Show_ChildMenu_Alarm();
				//return sign;
			case KEY_RETURN:
				Show_ChildMenu_Alarm();
				//return sign;							// BUG： 用return不能更新；
		}
	}
	
	
}

// 选择第几个闹钟，即结构体；
void Set_Alarm_Choose(int * value)
{
	int Key = 0;
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"ChildMenu-Alarm",16);
	OLED_ShowString(32,4,"Alarm: ",16);
	
	
	while (1)
	{
		Key = KEY4x4_Scan();
		delay_ms(10);
		
		OLED_ShowNum(96,4,(u32)*value,2,16);
		
		switch (Key)
		{
			case KEY_B: 
				(*value)++;								// 一定不能用到 value++等！！！！  导致修改地址！！！
				break;
			case KEY_C:
				(*value)--;
				break;
			case KEY_D:
				GO_HOME
				break;
			case KEY_ENTER: 						// 这个位置可以自定义菜单选项；其他功能；
				Show_ChildMenu_Alarm();
				//return sign;
			case KEY_RETURN:
				Show_ChildMenu_Alarm();
				//return sign;							// BUG： 用return不能更新；
		}
		
		if (*value < 0)
			*value = 20;
		if (*value > 20)
			*value = 0;
	}
	
}

void Show_ChildMenu_Alarm(void)		//bool sign, int value
{
	int Key = 0;
	int MoveP = 2;						// 箭头坐标；
	static int value = 0;			// 指向的闹钟；
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"ChildMenu-Alarm",16);
	
	OLED_ShowString(32,2,"Alarm: ",16);
		if (sign == true)
			OLED_ShowString(96,2,"ON",16);
		if (sign == false)
			OLED_ShowString(96,2,"OFF",16);
		
	OLED_ShowString(32,4,"Alarm: ",16);
		OLED_ShowNum(96,4,value,2,16);
		
	OLED_ShowString(32,6,"Alarm Set",16);
	
	while (1)
	{
		Key = KEY4x4_Scan();
		Move_Menu_Point(12,MoveP,161608,600);					// 显示箭头；
		
		switch (Key)
		{
			case KEY_2: 
				Move_Menu_Point(12,MoveP,161608,0);				// 隐含箭头；
				MoveP -= 2;
				break;
			case KEY_8:
				Move_Menu_Point(12,MoveP,161608,0);				// 隐含箭头；
				MoveP += 2;
				break;
			case KEY_D:
				GO_HOME
				break;
			case KEY_ENTER: 							// 这个位置可以自定义菜单选项；其他功能；
				if (MoveP == 2)						
					Set_Alarm_Switch();				// 闹钟开关；
				if (MoveP == 4)						
					Set_Alarm_Choose(&value);	// 闹钟选择；
				if (MoveP == 6)						
					Menu_Alarm_Set(value);		// 闹钟设置；
				break;
			case KEY_RETURN:
				OLED_Clear(0);									// 清屏；
				Show_ChildMenu(0);							// 显示上一个界面；返回键；		
				break;
		}
		
		if (MoveP > 6)MoveP = 2;			// 箭头向标超出范围时，复位；	MoveP: 3/6
		if (MoveP < 2)MoveP = 6;
			
		delay_ms(10);
	}

}





// 显示childmenu子菜单
void Show_ChildMenu(char value)
{
	int Key16 = 0;
	int MoveP = 2;			// 箭头坐标； 
	int Y = 8,Y2 = 16;
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"ChildMenu:",16);
	
	if (value == 0)			// 万年历；
	{
		// 设置时间；
		OLED_ShowCHinese(32,2,9); 			// 
		OLED_ShowCHinese(48,2,10);			// 
		OLED_ShowCHinese(64,2,6); 			// 
		OLED_ShowCHinese(80,2,7);				// 

		// 设置日期；
		OLED_ShowCHinese(32+Y,4,9); 			// 
		OLED_ShowCHinese(48+Y,4,10);			// 
		OLED_ShowCHinese(64+Y,4,4); 			// 
		OLED_ShowCHinese(80+Y,4,5);				// 
		
		// 设置闹钟；
		OLED_ShowCHinese(32+Y2,6,9); 			// 
		OLED_ShowCHinese(48+Y2,6,10);			// 
		OLED_ShowCHinese(64+Y2,6,19); 			// 
		OLED_ShowCHinese(80+Y2,6,20);			// 		
		
		while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
		{
			Move_Menu_Point(12,MoveP,161608,600);					// 显示箭头；
			
			switch (Key16)
			{
				case KEY_2: 
					Move_Menu_Point(12,MoveP,161608,0);				// 隐含箭头；
					MoveP -= 2;
					break;
				case KEY_8:
					Move_Menu_Point(12,MoveP,161608,0);				// 隐含箭头；
					MoveP += 2;
					break;
				case KEY_D:
					GO_HOME
					break;
				case KEY_ENTER: 						// 这个位置可以自定义菜单选项；其他功能；
					if (MoveP == 2)						
						Menu_Time_Set();				// 设置时间；
					if (MoveP == 4)						
						Menu_Date_Set();				// 设置日期；
					if (MoveP == 6)						
						Show_ChildMenu_Alarm();						// 设置闹钟；
					break;
			}
			
			if (MoveP > 6)MoveP = 2;			// 箭头向标超出范围时，复位；	MoveP: 3/6
			if (MoveP < 2)MoveP = 6;
			
			delay_ms(10);
		}
		
		Show_Menu();										// 显示上一个界面；返回键；		
	}
	
}

// 显示menu菜单
void Show_Menu(void)
{
	int Key16 = 0;
	int MoveP = 3;		// 箭头坐标； 0-5；
	
	OLED_Clear(0);
	OLED_ShowString(0,0,"Menu:",16);

	// 查询报警点
	OLED_ShowCHinese(32,3,14); 			// 
	OLED_ShowCHinese(48,3,15);			// 
	OLED_ShowCHinese(64,3,16); 			// 
	OLED_ShowCHinese(80,3,17);			// 
	OLED_ShowCHinese(96,3,18); 			// 
		
	// 设置万年历
	OLED_ShowCHinese(32,6,9); 			// 
	OLED_ShowCHinese(48,6,10);			// 
	OLED_ShowCHinese(64,6,11); 			// 
	OLED_ShowCHinese(80,6,12);			// 
	OLED_ShowCHinese(96,6,13); 			// 
	
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Move_Menu_Point(12,MoveP,161608,600);					// 显示箭头；
		
		switch (Key16)
		{
			case KEY_2: 
				Move_Menu_Point(12,MoveP,161608,0);				// 隐含箭头；
				MoveP += 3;
				break;
			case KEY_8:
				Move_Menu_Point(12,MoveP,161608,0);				// 隐含箭头；
				MoveP -= 3;
				break;
			case KEY_D: 
				GO_HOME
				break;
			case KEY_ENTER: 						// 这个位置可以自定义菜单选项；其他功能；
				if (MoveP == 3)						// 进入子菜单 ———— 警报时间；			
					;
				if (MoveP == 6)						// 子菜单 ———— 万年历设置；
					Show_ChildMenu(0);
				break;
		}
		
		if (MoveP > 6)MoveP = 3;			// 箭头向标超出范围时，复位；	MoveP: 3/6
		if (MoveP < 3)MoveP = 6;
		
		delay_ms(10);
	}
	
	Show_Home();										// 显示上一个界面；返回键；		
}

// 显示home主界面；
void Show_Home(void)  		
{
	int key = 0;
	OLED_Clear(0);						// 清屏；
	
	while(1)
	{
		Show_Time();						// 显示时间；
		Show_Date(1);						// 显示日期；
		Show_Chinese();					// 显示中文界面；	
		
		if ((key = KEY4x4_Scan()) == KEY_ENTER)				// 进入MENU界面
			Show_Menu();
		
		
		if (key == KEY_A)				// 日期测试；
		{
			while (1)
			{
				DateDay++;		
				Date_Update();
				
				delay_ms(300);
				Show_Date(1);						// 显示日期；
				
				if (DateDay > 5 && DateDay < 20)
					DateDay = 20;
			}
		}

	}

}
*/