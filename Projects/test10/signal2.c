#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define N 6


static void sig_quit(int);
void sig_alarm();


int main(int argc, char *argv[]) 
{
	//注册信号处理函数
	if(signal(SIGQUIT,&sig_quit) == -1)
	{
		printf("Could not register signal hanlder for SIGQUIT!\n");
		exit(1);
	}

	//进行信号集的定义及信号集的操作
    sigset_t newmask,oldmask,pendmask;
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);
	
	//设置屏蔽，保存原有信号设置
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
	{
		printf("SIG_BLOCK error\n");
		exit(2);
	}
	
	//使用alarm函数进行定时5秒
	if(signal(SIGALRM,sig_alarm) == -1)
	{
		printf("Could not register signal ALARM!\n");
		exit(4);
	}	
	alarm(5);
	sleep(3);

	//收集被屏蔽的信号并证明SIGQUIT是否在信号集中
	if(sigpending(&pendmask) < 0)
	{
		printf("sigpending error \n");
		exit(3);
	}
	if(sigismember(&pendmask,SIGQUIT))
	{
		printf("\nSIGQUIT pending \n");
	}
	//重新恢复原有设置
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
	{
		printf("SIG_SETMASK error \n");
		exit(4);
	}
	
	//表示已经从sigprocmask函数中返回
	printf("SIGQUIT unblocked \n");
	sleep(6);
	exit(0);
}

static void sig_quit(int signum)
{
	//表示已经在信号处理函数中
	printf("catch SIGQUIT\n");
	int j = 1;
	for(int i=0;i<N;i++)
	{
		//printf("show already %d\t",i++);
		printf("How are you\n");
		sleep(j);	
	}
	if(signal(SIGQUIT,SIG_DFL)==-1)
	{
		printf("Cound not reset SIGQUIT!\n");
	}
	return;
}

void sig_alarm()
{
	printf("alarm already timing 5 seconds\n");
	return ;
}
