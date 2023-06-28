#include "sys-alarm.h"
#include "oled.h"
#include "clock.h"
#include "key.h"
#include "HC-SR501.h"
#include "beep.h"
#include "delay.h"
#include "rc522.h"
#include "cled.h"
#include "key.h"
#include "led.h"
#include "key4x4.h"
#include "string.h"

/*全局变量*/
struct timing TimeVisit[MAXV];			// 
struct timing TimeSteal[MAXS];			// 记录警报时间结构体； 

// 6-8位 用户密码；		
const char LEN = 6;									// 密码长度；
char PassWord[8] = {1,2,3,4,5,6,0,0};					

char PassWord2[8] = {1,1,3,4,5,6,0,0};		// 预防按键串扰；					

int LEDSwitch = 1;									// 照明灯开关；

 
// 初始化记录时间为空；
void Time_Init(void)
{
	int i;
	
	for (i = 0; i < ((MAXV > MAXS)?MAXV:MAXS); i++)
	{
		if (MAXV > i)										// 溢出保护；
		{
			TimeVisit[i].sign = false;
			//printf("asd:  %d \r\n",i);
		}
			
		if (MAXS > i)
			TimeSteal[i].sign = false;
	}
}



/********************* 11/30 Flag后面用的拼音声明函数...  ： 警报 逗留 出门 回家 ***********************/
/**********************	
*	Flag函数用于判断智能警报系统 各种情况所对应的操作；（执行的操作）
* 在cled中断函数中执行；   HW1和HW2对应的警报；
**********************/

// 检测到警报防盗系统；
// 功能： 
// 1. 警报灯闪烁、语音模块；
// 2. 蜂鸣器间断警报；
// 3. 记录警报时间段；
static void Flag_JinBao()
{
	if (HW1 == 1 && HW2 == 1)
		Write_Time(STEAL);						// 记录警报时间；  steal：盗窃
	
}

// 访客逗留；				// 陌生人留言功能？  目前未开发
static void Flag_DouLiu()
{
	;
}

// 手动开关警报系统；
static void Flag_Guanbi(int Key)
{
	if (Key == ENABLE)
		CLOSE_Alarm_System(CLOSETIME);					// 关闭警报系统10分钟；
}

// 回家；
// 目前支持进门后，按键开关报警系统；  (手动关闭)
// 函数暂时无操作，和逗留功能相同
// 拓展：使用带管理员认证的密码锁功能等，当认证后，自动关闭警报系统；
//    		如：指纹锁(密码)、人脸识别、TF卡/扣、或者钥匙解锁后判断！     
// 12/3 通过对IC射频卡的识别，自动关闭警报系统；
static void Flag_HuiJia(int ICcard)
{
	if (ICcard == MI_OK)
		CLOSE_Alarm_System(CLOSETIME);				// 关闭警报系统10分钟；
}

// 检测到出门状态；											(自动关闭)				
// 入口条件： if (HW1 == 0 && HW2 == 1)
static void Flag_ChuMen()
{
	if (HW1 == 0 && HW2 == 1)
		CLOSE_Alarm_System(CLOSETIME);					// 关闭警报系统10分钟；
}



// 警报系统：
// 注意： 		在合适的位置调用该函数！
// 		1. main中调用时，如果主程序跳转执行其他功能，则会导致该函数未被调用，可靠性差？
//		2. 中断调用，内容过多，不可预知，稳定性差；
void Alarm_System(int Key)
{
	int ICcard;
	//HW_Scan();     										// 位操作的 红外扫描函数；
		
	ICcard = RC522_IcCard_Scan();				// IC卡扫描函数；
	
	Flag_JinBao();
	Flag_DouLiu();
	Flag_HuiJia(ICcard);
	Flag_ChuMen();
	Flag_Guanbi(Key);
	
}




// 开启警报系统
void OPEN_Alarm_System(void)
{
	OLED_Clear(0);									// 清屏
	TIM_Cmd(TIM3, ENABLE);  				// 使能TIMx
	CLED_Color(GREEN);							// 绿色					// 这句代码可删掉；和中断重复
	GO_HOME
}


// 关闭警报系统
// 提示： 
//					1. OLED界面显示并倒计时；
//					2. 蜂鸣器滴3声？
// time：关闭时间 单位：秒
// time == 0  闭死（直到手动开启）
void CLOSE_Alarm_System(int time)
{
	int KEY = 0;
	int count = NULL;
	
	OLED_Clear(0);									// 清屏
	OLED_ShowCHinese(0,0,21); 			// 重启倒计时
	OLED_ShowCHinese(16,0,22);			
	OLED_ShowCHinese(32,0,23); 			
	OLED_ShowCHinese(48,0,24);			
	OLED_ShowCHinese(64,0,25); 		
	OLED_ShowString(80,0,":",16);
	
	OLED_ShowCHinese(26,4,16); 			// 警报已关闭
	OLED_ShowCHinese(46,4,17);			
	OLED_ShowCHinese(66,4,26); 			
	OLED_ShowCHinese(86,4,27);			
	OLED_ShowCHinese(106,4,28); 
	
	CLED_Color(OFF);											// 关闭室外彩灯；
	BEEP = 1;	delay_ms(1000);	BEEP = 0;		// 蜂鸣器警报     // 出门状态时，蜂鸣器翻转警报；			// 由于中断函数的翻转，意外响3声XX
	TIM_Cmd(TIM3, DISABLE);  							// 失能TIMx，避免因中断而跳出该函数导致的不确定因素（特别是中断中，乱插入函数）			// 11/30 ************* 该位置应添加初始化等！！ ******************
	CLED_Color(OFF);											// 关闭室外彩灯；
	
	if (time == STOP)											// 手动开关
	{
		OLED_ShowString(92,0,"Null",16);
		while((KEY = KEY_Scan(0)) != KEY0_PRES)//;	// 死循环，直到用户按下 WKUP			// while(KEY_Scan(0) != KEY0_PRES);
			LED_Switch(KEY);									// 警报开关&照明灯开关； 
		
		OPEN_Alarm_System();
		return;
	}
	
	while(time != 0)
	{
//		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)			// 此路不通；
//		time--;
		OLED_ShowNum(86,0,(u32)time,5,16);	// 显示重启倒计时；
		
		if (count != UPDATEsec)			   			// 当时钟的秒数更新时；
		{
			time--;														// 倒计时 减一秒；
			count = UPDATEsec;								// 更新标记；
		}
		Key_Switch();
	}
	
	OPEN_Alarm_System();						// 打开警报系统
	
}


// 记录时间；
// tips: 	该函数应在30分钟内只执行一次，避免重复记录时间
// VISIT：逗留、来访
// STEAL：盗窃
void Write_Time(u8 value)
{
	int i = 0;
	unsigned int time;
	const unsigned int num = BREAKTIME;							// 警报和逗留时间记录最短间隔； 单位：Min
	
	// 记录拜访和逗留！  暂未配置调用
	if (value == VISIT)
	{
		while (TimeVisit[i].sign == true && i < MAXV) 		// 找出“空”的结构体
			i++;
		
		time = Time_Compare(value, i-1); 
		printf("i = %d \r\n",i);
		printf("time = %d \r\n",time);
		if (time < num && i > 0)
		{
			printf("time = %d \r\n",time);
			printf("i = %d \r\n",i);
			return;
		}
		
		if (TimeVisit[i].sign == false)
		{
			printf("数据记录成功 \r\n");
			TimeVisit[i].month = DateMonth;
			TimeVisit[i].day = DateDay;
			TimeVisit[i].hour = ClockHour;
			TimeVisit[i].min = ClockMin;
			TimeVisit[i].sign = true;					
		}

		if (i >= MAXV)
			for (i = 0; i < MAXV; i++)
				TimeVisit[i].sign = false;			// 清空结构体；		
	}
	
	// 记录警报时间
	if (value == STEAL)
	{
		while (TimeSteal[i].sign == true && i < MAXS) 		// 找出“空”的结构体
			i++;
		
		if (Time_Compare(value, i-1) < num)
			return;

		if (TimeSteal[i].sign == false)			// 防止i溢出；
		{
			TimeSteal[i].month = DateMonth;
			TimeSteal[i].day = DateDay;
			TimeSteal[i].hour = ClockHour;
			TimeSteal[i].min = ClockMin;
			TimeSteal[i].sign = true;		
		}			

		
		if (i >= MAXS)
			Time_Init();						// 清空结构体；					// 注意： 该函数会同时清空Visit和Steal的sign状态； 但并不清空记录的时间；
	}
	
}

// 比较现在的时间和 记录的时间 相差值；
// 返回值单位： Min
// 注意！！ 未考虑天数，如果凌晨记录，返回值会出现负数；
// 					即使强制装换，也未避免会重复记录两次；
unsigned int Time_Compare(u8 value, u8 i)
{
	int NowMin,VisitMin,StealMin;
	
	NowMin = ClockHour * 60 + ClockMin;
	VisitMin = TimeVisit[i].hour * 60 + TimeVisit[i].min;
	StealMin = TimeSteal[i].hour * 60 + TimeSteal[i].min;
	
	if (value == VISIT)
		return (u32)(NowMin - VisitMin);
	
	if (value == STEAL)
		return (u32)(NowMin - StealMin);
}



// 12/3 *****************************************   待完成  部分  ***********************************

// 显示报警时间 			// 和显示闹钟 Show_Alarm()相同；  闹钟都没做完....
// 参数： 月份、日期、小时、分钟；
static void Show_Child_AlarmTime(int i)
{
	//int i = 0;
	int row = -5;
	
	// 显示时间部分
	OLED_ShowNum(22+row,4,TimeSteal[i].hour / 10,1,16);			// 显示小时。			
	OLED_ShowNum(32+row,4,TimeSteal[i].hour % 10,1,16);			// 显示小时。	
	OLED_ShowString(40+row,4,":",16);
	OLED_ShowNum(48+row,4,TimeSteal[i].min / 10,1,16);			// 显示分钟。
	OLED_ShowNum(58+row,4,TimeSteal[i].min % 10,1,16);			// 显示分钟。
	
	// 显示日期部分
	OLED_ShowNum(73+row,4,TimeSteal[i].month / 10,1,16);			// 十位显示
	OLED_ShowNum(81+row,4,TimeSteal[i].month % 10,1,16);			// 个位
	OLED_ShowString(89+row,4,"/",16);
	OLED_ShowNum(99+row,4,TimeSteal[i].day / 10,1,16);	
	OLED_ShowNum(107+row,4,TimeSteal[i].day % 10,1,16);		
	
	/******************  显示下一个时间点  ********************/
	// 显示时间部分
	OLED_ShowNum(22+row+7,6,TimeSteal[i-1].hour / 10,1,8);			// 显示小时。			
	OLED_ShowNum(32+row+5,6,TimeSteal[i-1].hour % 10,1,8);			// 显示小时。	
	OLED_ShowString(40+row+4,6,":",8);
	OLED_ShowNum(48+row+3,6,TimeSteal[i-1].min / 10,1,8);			// 显示分钟。
	OLED_ShowNum(58+row+1,6,TimeSteal[i-1].min % 10,1,8);			// 显示分钟。
	
	// 显示日期部分
	OLED_ShowNum(73+row-0,6,TimeSteal[i-1].month / 10,1,8);			// 十位显示
	OLED_ShowNum(81+row-0,6,TimeSteal[i-1].month % 10,1,8);			// 个位
	OLED_ShowString(89+row-1,6,"/",8);
	OLED_ShowNum(99+row-4,6,TimeSteal[i-1].day / 10,1,8);	
	OLED_ShowNum(107+row-4,6,TimeSteal[i-1].day % 10,1,8);			
	
	/******************  显示下下个时间点  ********************/
	// 显示时间部分
	OLED_ShowNum(22+row+10,7,TimeSteal[i-2].hour / 10,1,8);			// 显示小时。			
	OLED_ShowNum(32+row+7,7,TimeSteal[i-2].hour % 10,1,8);			// 显示小时。	
	OLED_ShowString(40+row+5,7,":",8);
	OLED_ShowNum(48+row+3,7,TimeSteal[i-2].min / 10,1,8);			// 显示分钟。
	OLED_ShowNum(58+row+1,7,TimeSteal[i-2].min % 10,1,8);			// 显示分钟。
	
	// 显示日期部分
	OLED_ShowNum(73+row-0,7,TimeSteal[i-2].month / 10,1,8);			// 十位显示
	OLED_ShowNum(81+row-1,7,TimeSteal[i-2].month % 10,1,8);			// 个位
	OLED_ShowString(89+row-2,7,"/",8);
	OLED_ShowNum(99+row-5,7,TimeSteal[i-2].day / 10,1,8);	
	OLED_ShowNum(107+row-6,7,TimeSteal[i-2].day % 10,1,8);				
	
	printf("显示警报时间>>%d  状态>>%d  \r\n",i+1,TimeSteal[i].sign);
	
}

// 警报时间查询函数
// StealNum： 显示记录了多少次；
// 
// struct timing TimeSteal[MAXS];			// 记录警报时间结构体； 
void Show_AlarmTime(void)
{
	int i;
	int StealNum = 0;
	int Key16 = 0;
	
	for (i=0; i < MAXS; i++)
		if (TimeSteal[i].sign == true)		// 记录了几条时间；
			StealNum++;
		
	printf("警报时间查询 \r\n");		
	OLED_Clear(0);	

		
	OLED_ShowCHinese(6,0,16); 			// 警
	OLED_ShowCHinese(24,0,17);			// 报
	OLED_ShowCHinese(42,0,31); 			// 次
	OLED_ShowCHinese(60,0,32);			// 数
	OLED_ShowString(78,0,":",16);
		
	OLED_ShowNum(96,0,StealNum,2,16);
	OLED_ShowString(29,3,"TIME",8);			// 24
	OLED_ShowString(68,3,"DATE",8);			// 75

	i = StealNum;
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Child_AlarmTime(StealNum-1);	// 显示时间；
		
		switch (Key16)
		{
			case KEY_2: 			
				StealNum++;										// 查询(显示)下一个时间点；  警报时间点
				break;
			case KEY_8:
				StealNum--;										// 查询(显示)上一个时间点；
				break;
			case KEY_B: 			
				StealNum++;										// 查询(显示)下一个时间点；  警报时间点
				break;
			case KEY_C:
				StealNum--;										// 查询(显示)上一个时间点；
				break;
			case KEY_D:
				GO_HOME
				break;
			case KEY_ENTER: 						
				Show_Menu();									// 显示上一个界面；返回键；		
				break;
		}
		
		if (StealNum < 0+1)StealNum = 0+1;		// 溢出重置；    
		if (StealNum > i+1)StealNum = i+1;

		delay_ms(10);
	}
	
	Show_Menu();												// 显示上一个界面；返回键；		
	
}


// 设置并显示密码
void ShowAndSet_Password(char *st, int num, int i)
{
	int row = 10;
	
	if (num == 'A')												// 删除键；
	{
		st[i] = NULL;								
		OLED_Clear8x8(20+row*i,3,1,2);	  	// 显示空白..		
		OLED_Clear8x8(20+row*i,3,8,2);			// 删除下划线；
		return;
	}
	
	st[i] = num;
	OLED_ShowNum(20+row*i,3,st[i],1,16);

	
}


/***************************
*
*	管理员密码认证部分、模块
*
***************************/

// 显示密码位置索引: _
// 显示掩码: *
static void Show_Message(int i)
{
	int row = 10;
	int j;
	
	if (msCount < 500)
		OLED_ShowString(20+row*i,3,"_",16);
	else
		OLED_Clear8x8(20+row*i,3,4,2);	
	
	//if (i>=1);
	//for (j=i; j>=2; j--);
	while (i >= 2)								// 在合适位置显示掩码* 而不是逐一替换；
	{
		OLED_ShowString(20+row*(i-2),3,"*",16);
		i--;
	}
	
}

// 按键输入函数；  带显示部分；
// 回车键结束输入；
// *st: 存放位置；
// n:   最大字数；
static void KEY4x4_gets(char *st, int n)
{
	int i = 0;
	int Key16 = 0;
	
//	for (i=0; i<n; i++)
	
	while((Key16 = KEY4x4_Scan()) != KEY_RETURN)
	{
		Show_Message(i);
		if (i >= LEN) i = LEN;
		delay_ms(5);
		switch (Key16)
		{
			case KEY_1: ShowAndSet_Password(st,1,i); i++; break;			
			case KEY_2: ShowAndSet_Password(st,2,i); i++; break;
			case KEY_3: ShowAndSet_Password(st,3,i); i++; break;
			case KEY_4: ShowAndSet_Password(st,4,i); i++; break;			// 注意： KEY_4 按键反馈的值是5，而并非4； 可修改定义；
			case KEY_5: ShowAndSet_Password(st,5,i); i++; break;
			case KEY_6: ShowAndSet_Password(st,6,i); i++; break;
			case KEY_7: ShowAndSet_Password(st,7,i); i++; break;
			case KEY_8: ShowAndSet_Password(st,8,i); i++; break;
			case KEY_9: ShowAndSet_Password(st,9,i); i++; break;
			case KEY_0: ShowAndSet_Password(st,0,i); i++; break;		
			case KEY_A: i--; ShowAndSet_Password(st,'A',i); break;
			case KEY_B: 							break;
			case KEY_C:								break;
			case KEY_D: 		GO_HOME 	break;
			case KEY_ENTER: return;		break;													// 确认后，返回主调函数；
		}
	}
	GO_HOME
}



// 用户（管理员）密码						// unsigned char PassWord;// 8位 用户密码；
// 1. 显示界面
// 2. 输入与判断
// 3. 设置密码
// 如果想返回到某个函数。把该函数的函数指针作为参数？
void User_Password(void)
{
	char value[8];
	
	OLED_Clear(0);						// 清屏；
	OLED_ShowString(0,0,"PassWord:",16);
	OLED_ShowString(60,7,"A:Delete",8);
	
	while (1)
	{
		KEY4x4_gets(value,LEN);
		
		//if (strncmp(value,PassWord,6) == 0)				// 比较用户输入的密码value和预设置密码PassWord； // 初始
		if (strncmp(value,PassWord,6) == 0 || strncmp(value,PassWord2,6) == 0 || RC522_IcCard_Scan() == MI_OK)				// 和谐； 
		{
			printf("Pass OK >>%d \r\n", strncmp(value,PassWord,6));
			return;								// 认证通过，返回主调函数；
		}
		else
		{
			printf("Wrong >>%d \r\n", strncmp(value,PassWord,6));
			OLED_Clear8x8(0,3,16,2);	
			OLED_ShowString(35,3,"Wrong!!!",16);	// 认证失败；继续循环；
			delay_ms(5000);
			OLED_Clear8x8(35,3,8,2);	
		}
			
	}
	
}



// *************** 独立按键模块 ***********************//
// 警报开关&照明灯开关；
void Key_Switch(void)
{
	u8 Key = 0;
	static int sled = 1;
		
	Key = KEY_Scan(0);
	
	switch(Key)
	{
		case KEY0_PRES:
			CLOSE_Alarm_System(STOP);					// 关闭警报系统10分钟；
			break;
		case KEY1_PRES:
			LEDSwitch = !LEDSwitch;
			break;
	}
	
	if (HW2 == 1 && LEDSwitch)
		LED2 = 1;
	else
		LED2 = 0;
	
}

void LED_Switch(int KEY)								// yitahutu
{
	if (KEY == KEY1_PRES)
		LEDSwitch = !LEDSwitch;
	
	if (HW2 == 1 && LEDSwitch)
		LED2 = 1;
	else
		LED2 = 0;
}





// 11/30  待完成
// ***************** 警报系统模块 *************************//
// 测试程序
void Alarm_System_Test(void)
{
	
	// 展示功能效果；....      ******************* 最后处理：
	
	
}

