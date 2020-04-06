#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define M 5

void swit(char* b,char buf1[M])
{
	int i=0;
	while(*(b+i) != '#')
	{
		if((*(b+i) - 32) < 65)
			buf1[i]=*(b+i);
		else
		buf1[i]=(char)(*(b+i)-32);

		i++;
	}
	buf1[M-1]='\0';
}


int main(int argc,char *argv[])
{
	int fd;
	char buf[M+1];
	char buf1[M];
	int len;
	fd=open("./sixthtest.c",O_RDWR, 10755);
	
	printf("***请输入字符：***\n");
	for(int i=0;i<M;i++)
	{
		scanf("%c",&buf[i]);
	}
	buf[M]='\0';
	char *p = buf;
	swit(p,buf1);
	
	printf("buf ：%s\n",buf);
	printf("buf1：%s\n",buf1);
	
	len = write(fd,buf1,M-1);
	if(len == -1)
	{
		printf("error\n");
		return 1;
	}
	else
	{
		printf("write success\n");
		close(fd);
	}
	
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("调用execl系列函数输出：\n");
		execl("/bin/cat","/bin/cat","./sixthtest.c",NULL);
		return 2;
	}
	return 0;
}
