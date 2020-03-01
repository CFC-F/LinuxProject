#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define M 5     //人数 
#define K 3    //学科科数 
#define N 66   //名字的数量大小 

struct student
{
	char name[N];
	long long int number;
	struct
	{
		int score;    //单科成绩 
	}subject[K];      //科目 
	int num;          //每个人总成绩  
	double average[K];//每一科平均成绩 
};
struct student stu[M];
struct student stu1[1];



void creat(int a[][M]);                      //自动生成成绩函数
void creatname(struct student stu[M]);       //自动产生姓名首字母     
void nums(struct student stu[M]);           //求某个人的总成绩 
void averages(struct student stu[M]);       //所有人某科成绩平均数 
void disp(struct student stu[M]);
void numbers(struct student stu[M]);
void sorts(struct student stu[M],struct student stu1[1]);



int main(int argc,char *argv[])
{
	FILE* fpstudent;
	if(argc < 2)
	{
		printf("usage:%s sourcefile destfile\n",argv[0]);
		return 1;
	}

	/*if((fpstudent = fopen(argv[1],"r")) == NULL)
	{
		printf("Open sourcefile %s failed!",argv[1]);
		return 2;
	}*/

	if((fpstudent = fopen(argv[1],"w")) == NULL)
	{
		printf("Create destfile %s failed!",argv[1]);
		return 2;
	}
	
	struct student stu[M];
	struct student stu1[1];
	int sub_num[K];
	int a[K][M];
	for(int b=0;b<K;b++)       //六科成绩自动生成 
	{
		creat(a);
		for(int j=0;j<M;j++)
		{
			stu[j].subject[b].score=a[b][j];	
		}
	}
	
	printf("** name     number     num    math  Chinese  Endlish **\n");
	creatname(stu);
	nums(stu); 
	averages(stu);
	numbers(stu);
	disp(stu);
	printf("********score ranking*******\n");
	sorts(stu,stu1);
	
	

	for(int i=0;i<M;i++)
	{
		//fwrite(&stu[i],sizeof(stu),M,fpstudent);
		fprintf(fpstudent,"%s\t", stu[i].name);
		fprintf(fpstudent,"%lld\n", stu[i].number);
		for(int j=0;j < K;j++) fprintf(fpstudent,"%d\t", stu[i].subject[j].score);
		fprintf(fpstudent,"%d\n", stu[i].num);
	}
	return 0;
	
}

void creatname(struct student stu[M])
{
	int i;
	char c;
	srand((unsigned)time(NULL));
	for(i=0;i<M;i++)
	{
		for(int j=0;j<3;j++)
		{
			c='A'+rand()%26;
			stu[i].name[j]=c;
		}
		stu[i].name[3]='\0';
	}
}

void creat(int a[K][M])
{
	int i60=0,i90=0,data=0;
	srand(time(NULL));
	for(int w=0;w<K;w++)
	{
		for (int i=0;i<M;i++)
		{
			data=rand()%101;
			if(data<=60)
			{
				i60++;
				if(i60>(M*0.1))
					i--;
				else
					a[w][i]=data;
			}
			else if(data>=90)		
			{
				i90++;
				if(i90>(M*0.1))				
					i--;
			    else
		    	a[w][i]=data;
			}
			else
				a[w][i]=data;
		}

	}
}

void nums(struct student stu[M])
{
	int num2=0,num5=0;      // num2 求某科所有人成绩的变量  ；num5某个人所有成绩 的变量 
	for(int j=0;j<M;j++)       
	{
		for(int b=0;b<K;b++)   
		{
			num5+=stu[j].subject[b].score;  //某个人所有成绩求和 num5 
		}
		stu[j].num=num5;                    //某个人的总成绩传到结构体中  
		num5=0;
	}
}
	
	
void averages(struct student stu[M])
{
	double num1[K];
	int num2=0,b,j; //num[] 某科所有人成绩数组 ;num2 求某科所有人成绩的变量 
	for(b=0;b<K;b++)       
	{
		for(j=0;j<M;j++)
		{
			num2+=stu[j].subject[b].score;  //某科所有人成绩求和 num2 
		}
		num1[b]=num2;                   //某科所有人成绩总和 
		num2=0;
	}	
	for(j=0;j<M;j++)
	{
		for(b=0;b<K;b++)
		{
			stu[j].average[b]=(num1[b]/M);   //某科所有人成绩平均分数 
		}	
	}		
}

void sorts(struct student stu[M],struct student stu1[1])
{
	int k=1;
	//struct student *p=stu;
	//struct student *q=stu1;
	//struct student stu1;
	for(int j=0;j<M-1;j++)  //for(int h=0;h<M-1;h++)
	{
		for(int i=0;i<M-1-j;i++)
		{
			if(stu[i].num>stu[i+1].num)
			{
				//temp=stu[i].num;
				//stu[i].num=stu[i++].num;
				//stu[i++].num=temp;
				stu1[0]=stu[i];
	            stu[i]=stu[i+1];
            	stu[i+1]=stu1[0];
            //	*q=*(p+i);
            //	*(p+i)=*(p+i+1);
            //	*(p+i+1)=*q;	
			}	
		}
	}
	for(int j=0;j<M;j++)
	{
		if(j<=(M*0.5))
		{
			if(j<9)
				printf("%s  %lld total score:%d\n",stu[j].name,stu[j].number,stu[j].num);
			else
				printf("%s  %lld total score:%d\n",stu[j].name,stu[j].number,stu[j].num);	
		}
		else
		{
			if(k<9)
				printf("%s  %lld total score:%d\n",stu[j].name,stu[j].number,stu[j].num);
			else
				printf("%s  %lld total score:%d\n",stu[j].name,stu[j].number,stu[j].num);	    //(p+j)->number,(p+j)->num
			k++;
		}		
	}
}
void disp(struct student stu[M])
{
	int k=1;
	for(int j=0;j<M;j++)
	{
		printf("   %s  ",stu[j].name);
		if(j<=(M*0.5))
		{
			if(j<9)
				printf("%lld  ",stu[j].number);
			else
				printf("%lld  ",stu[j].number);	
		}
		else
		{
			if(k<9)
				printf("%lld  ",stu[j].number);
			else
				printf("%lld  ",stu[j].number);	
			k++;
		}
		printf(" %d  ",stu[j].num);
		for(int b=0;b<K;b++)
		{
			//creat(a);
			//int a[K][M];
			{
				printf("   %d   ", stu[j].subject[b].score); 
			} 
		}
		printf("\n");
	}
	for(int j=0;j<M;j++)
	{
		
	}
	for(int b=0;b<K;b++)
	{
		printf("subject %d average score :%lf\n",b+1,stu[b].average[b]);
	}
}

void numbers(struct student stu[M])
{
	int k=1;
	for(int j=0;j<M;j++)
	{
		if(j<=(M*0.5))
		{
			if(j<9)
			//	printf("20172301010%d的总成绩为:%d\n",j+1,stu[j].num);
				stu[j].number=201723010100+j+1;
			else
			//	printf("2017230101%d的总成绩为:%d\n",j+1,stu[j].num);
				stu[j].number=201723010100+j+1;	
		}
		else
		{
			if(k<9)
			//	printf("20172301020%d的总成绩为:%d\n",k,stu[j].num);
				stu[j].number=201723010200+k;
			else
			//	printf("2017230102%d的总成绩为:%d\n",k,stu[j].num);	
				stu[j].number=201723010200+K;
			k++;
		}		
	}
}
