#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
	int fd;
	struct stat statbuf;
	int len1,len2,ret;
	char buf[60];
	fd = open("test.c",O_CREAT | O_RDWR , 10705);
	if(fd == -1)
	{
		perror ("open fail\n");
		return -1;
	}
	else 
	{
		printf("open success\n");
		len1 = write(fd,"write to the file!",strlen("write to the file!"));
		if(len1 == -1)
		{
			perror("write fail!\n");
			return -1;
		}
		else
		{
			printf("write success!\n");
			close(fd);
		}
	}

	fd = open("test.c",O_RDONLY);
	len2 = read(fd,buf,10);
	if(len2 == -1)
	{
		perror("read fail\n");
	}
	buf[10]='\0';
	ret = stat("test.c",&statbuf);
	printf("test.c 的大小 %ld\tthe 10 of file content:%s\n",statbuf.st_size,buf);
	close(fd);

	return 0;
}
