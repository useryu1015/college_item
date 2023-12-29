#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SYS_HEARTBEAT 100000      // 系统运行最小周期
void task1(void);
void task2(void);
void mini_scheduler(void);


int main(void){
    printf("basic_scheduler Demo\n");    

    mini_scheduler();

    return 0
}


void task1(void){
	printf("start task1 \n");

}
void task2(void){
	printf("start task2 \n");

}
void mini_scheduler(void){
    int run_time = 1;

    while (1)
    {
        run_time += 1;
        if (!(run_time%1)) task1();			// 每100*1毫秒响应一次
        if (!(run_time%5)) task2();			// 每100*5毫秒响应一次

        printf("%d \n ",run_time);
        usleep(SYS_HEARTBEAT);     // 100ms 系统周期最小单位
        run_time &= 0x7;       // 溢出保护
    }

    
}