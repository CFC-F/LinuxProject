#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
/**********目录打开、读取和关闭函数的使用方法********/
/***** readdir  读取目录文件内容    *****/

int main(int argc ,char *argv[])
{
	char path[1000];
	DIR *dp;
	struct dirent* pdirent;
	if(argc != 2)
	{
		printf("Usage ex3-9 <pathname>\n");
		return 1;
	}
	if((dp = opendir(argv[1])) == NULL)
	{
		printf("Opendir %s failed\n",argv[1]);
		return 2;
	}
	if((pdirent = readdir(dp)) ==0)
	{
		printf("readdir %s failed \n",argv[1]);;
		return 3;
	}
	while((pdirent = readdir(dp)) != NULL)
	//printf("%s\n",pdirent->d_name);
        printf("%s:%ld\n",pdirent->d_name,pdirent->d_ino);
	
	closedir(dp);
	return 0;
}
