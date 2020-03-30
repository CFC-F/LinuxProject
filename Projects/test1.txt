#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#define len 1024


/**************使用函数实现cat命令的功能****************/

int main(int argc,char *argv[])
{
        int fd;
        int ret;
        char buf[len+1];

        if(argc <= 1)
        {
                printf("file name empty\n");
                return 1;
        }

        fd = open(argv[1],O_RDWR|O_CREAT|O_APPEND,10600);
        if(fd == -1)
        {
                printf("open fail\n");
                return 2;
        }
        buf[len] = '\0';
        memset(buf,'\0',len);
        while(ret = (read(fd,buf,len) >0 ))
        {
                printf("%s",buf);
                memset(buf,'\0',len);
        }

        printf("\n");

        close(fd);
        return 0;
}
