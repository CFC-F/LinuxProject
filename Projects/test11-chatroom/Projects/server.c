#include "FIFO.h"

int main()
{

    Client_Number = 0;    

    //创建信号，用于退出
    if(signal(SIGINT, &signal_quit) == -1)
	{
        printf("Couldn't register signal\n");
        exit(1);
    }

    //创建共有管道，用于通信
    Create_FIFO(Public_FIFO);

    while(1)
	{

        if((PublicFd = open(Public_FIFO, O_RDONLY)) < 0)
		{
            printf("fail open Public_FIFO\n");
            exit(1);
        }

        //通过公共管道进行读客户端数据
        if(read(PublicFd, &Client_Send_Msg, sizeof(struct FIFO_Message)) > 0)
		{

            printf("客户端的进程号是 : %d\n", Client_Send_Msg.client_pid);
			//printf("%c\n",Client_Send_Msg.type);	
            printf("客户端的信息 : %s", Client_Send_Msg.message);
            Client_FIFO_Name = Creat_Client_Name(Client_Send_Msg.client_pid);

			//使用switch，通过标志位来区分登录与聊天
			//通过识别Signal_QUIT，判断某客户端退出，关闭私有管道
	
			switch(Client_Send_Msg.type)
			{
				case 'L':
					printf("这是新建的客户端!\n");
					New_Client_Flag = 1;
					Create_FIFO(Client_FIFO_Name);
					Store_Client_Name();
					Server_Sendto_New();
					close(PublicFd);
					break;
				case 'C':
					Server_Sendto();
					if(strcmp(Client_Send_Msg.message, Signal_QUIT) == 0)
					{
						unlink(Client_FIFO_Name);
						Delete_Client_Data();
						Client_Number --;
						printf("关闭 Client_%d 私有管道\n", Client_Send_Msg.client_pid);
						printf("客户端的数量 : %d\n", Client_Number);
					}
					close(PublicFd);
					break;
				default:
					printf("Error Message\n");

			}
				
        }
        else
		{
            printf("Read Publicfd error!\n");
            exit(1);
        }
		
    }
    
    return 0;

}

char* Creat_Client_Name(int Client_pid)
{

    char TempBuffer[6];
    strcpy(Client_Name, Private_FIFO);
    sprintf(TempBuffer, "%d", Client_pid);
    strcat(Client_Name, TempBuffer);
    return Client_Name;

}

void Create_FIFO(char *FIFO_Name)
{
    int Fd;
    if((Fd = open(FIFO_Name, O_RDONLY)) == -1)
	{
        umask(0);
        mknod(FIFO_Name, S_IFIFO|0666, 0);
        printf("%s-管道被创建\n", FIFO_Name);
    }
    else
	{
        close(Fd);
    }

}

void signal_quit(int signum)
{
	printf("\n服务端已退出\n");
    unlink(Public_FIFO);
    exit(0);

}

void Store_Client_Name(void)
{

    Client_PID_Box[Client_Number] = Client_Send_Msg.client_pid;
    Client_Number ++;
    printf("客户端数量为 : %d\n", Client_Number);

}

void Server_Sendto(void)
{

    int count;

	sprintf(Client_Get_Msg.message, "[%s] :  ", Client_Send_Msg.client_name);
	strcat(Client_Get_Msg.message, Client_Send_Msg.message);

	//服务端通过循环打开私有管道发送给每一个客户端
	for(count = 0; count < Client_Number; count ++)
	{
		if((PrivateFd = open(Creat_Client_Name(Client_PID_Box[count]), O_WRONLY)) > 0)
		{
			Client_Get_Msg.client_pid = Client_Send_Msg.client_pid;
			if(write(PrivateFd, &Client_Get_Msg, sizeof(struct FIFO_Message)) > 0)
			{
				printf("Client_%d 信息写入成功!\n", Client_PID_Box[count]);
				close(PrivateFd);
			}
		}
		usleep(100000);
	}
    
    printf("\n");

}

void Server_Sendto_New(void)
{
	int count;
	
	sprintf(Client_Get_Msg.message, "新用户[%s] 登录 成功\n", Client_Send_Msg.client_name);
	for(count = 0; count < Client_Number; count ++)
	{
		if((PrivateFd = open(Creat_Client_Name(Client_PID_Box[count]), O_WRONLY)) > 0)
		{
			Client_Get_Msg.client_pid = Client_Send_Msg.client_pid;
			if(write(PrivateFd, &Client_Get_Msg, sizeof(struct FIFO_Message)) > 0)
			{
				printf("Client_%d 信息写入成功!\n", Client_PID_Box[count]);
				close(PrivateFd);
			}
		}
		usleep(100000);
	}
    
    printf("\n");
}

void Delete_Client_Data(void)
{

    int local;
    int count;

    for(local = 0; local < Client_Number; local++){
        if(Client_Send_Msg.client_pid == Client_PID_Box[local]){
            break;
        }
    }
    for(count = local; count < Client_Number; count ++){
        Client_PID_Box[count] = Client_PID_Box[count + 1];
        //strcpy(Client_Name_Box[count], Client_Name_Box[count + 1]);
    }

}
