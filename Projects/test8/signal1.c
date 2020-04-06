#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void intfunc(int signum);
void exitfunc(int signum);

int main()
{
	int i=1,j=1;
	if(signal(SIGINT,&intfunc) == -1)    //SIGINT信号  控制终端的中断键被按下
	{
		printf("Cound`t register signal hanlder for SIGINT!\n");
		exit(1);
	}
	/*
	if(signal(SIGTSTP,&intfunc)==-1)   //SIGTSTP信号，把停止信号发送给联机会话进程，通常由CTRL+Z 来产生信号
	{
		printf("Cound`t register signal hanlder for SIGTSTP!\n");
		exit(1);
	}
	*/
	if(signal(SIGTERM,&exitfunc) == -1)    //SIGTERM信号 终止进程，kill系统调用就发送这个信号
	{
		printf("Cound`t register signal hanlder for SIGTERM!\n");
		exit(1);
	}
	
	printf("Pid of This Process:%d\n",getpid());
	
	for(;;)
	{
		printf("show already %d\t",i++);
		printf("How are you\n");
		sleep(j);	
	}
	exit(0);
}

void intfunc(int signum)
{
	int i=1,j=1;
	for(;;)
	{
		printf("second show already %d\t",i++);
		printf("Bye bye\n");
		sleep(j);
	}
}

void exitfunc(int signum)
{
	printf("signal SIGTERM\n");
	exit(0);
}

