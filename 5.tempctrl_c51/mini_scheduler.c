#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SYS_HEARTBEAT 100000      // ϵͳ������С����
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
        if (!(run_time%1)) task1();			// ÿ100*1������Ӧһ��
        if (!(run_time%5)) task2();			// ÿ100*5������Ӧһ��

        printf("%d \n ",run_time);
        usleep(SYS_HEARTBEAT);     // 100ms ϵͳ������С��λ
        run_time &= 0x7;       // �������
    }

    
}