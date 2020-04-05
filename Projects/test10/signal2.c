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
	//ע���źŴ�����
	if(signal(SIGQUIT,&sig_quit) == -1)
	{
		printf("Could not register signal hanlder for SIGQUIT!\n");
		exit(1);
	}

	//�����źż��Ķ��弰�źż��Ĳ���
    sigset_t newmask,oldmask,pendmask;
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);
	
	//�������Σ�����ԭ���ź�����
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
	{
		printf("SIG_BLOCK error\n");
		exit(2);
	}
	
	//ʹ��alarm�������ж�ʱ5��
	if(signal(SIGALRM,sig_alarm) == -1)
	{
		printf("Could not register signal ALARM!\n");
		exit(4);
	}	
	alarm(5);
	sleep(3);

	//�ռ������ε��źŲ�֤��SIGQUIT�Ƿ����źż���
	if(sigpending(&pendmask) < 0)
	{
		printf("sigpending error \n");
		exit(3);
	}
	if(sigismember(&pendmask,SIGQUIT))
	{
		printf("\nSIGQUIT pending \n");
	}
	//���»ָ�ԭ������
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
	{
		printf("SIG_SETMASK error \n");
		exit(4);
	}
	
	//��ʾ�Ѿ���sigprocmask�����з���
	printf("SIGQUIT unblocked \n");
	sleep(6);
	exit(0);
}

static void sig_quit(int signum)
{
	//��ʾ�Ѿ����źŴ�������
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
