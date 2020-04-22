#ifndef __MYFIFO__
#define __MYFIFO__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define Public_FIFO  "Server_FIFO"
#define Private_FIFO "Client_FIFO_"
#define Signal_QUIT  "quit\n"
#define Client_Number_LEN 10
#define Client_Name_LEN 30

enum
{
	L,  //登录
	C, //聊天
};
struct FIFO_Message
{
	char type;
    int client_pid;
	char client_name[Client_Name_LEN];
    char message[100];
};

void Delete_Client_Data(void);
void Server_Sendto_New(void);
void signal_quit(int signum);
void Create_FIFO(char *FIFO_Name);
char* Creat_Client_Name(int Client_pid);
void Store_Client_Name(void);
void Server_Sendto(void);
void Client_Write(int flag, int Child_pid);
void Client_Read(void);
void Show_Time(void);

int New_Client_Flag;
int Client_Number;
int Client_PID_Box[Client_Number_LEN];
int PublicFd, PrivateFd;
char Client_Name[Client_Name_LEN];
char* Client_FIFO_Name;
struct FIFO_Message Client_Send_Msg, Client_Get_Msg;

#endif 
