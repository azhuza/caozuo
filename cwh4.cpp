//os_4
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
void SignHandler1(int iSignNo);
void SignHandler2(int iSignNo);
int child1,child2;
int filedis[2];

int main()
{

    char buffer[40];
    char info[40];
    int counter=1;
    printf("Process Parent pid %d\n",getpid());
    //创建无名管道
    if(pipe(filedis)<0)
    {
        printf("Create pip failed\n");
        return -1;
    }
    //设置软中断信号
    signal(SIGINT,SignHandler1); //要进行处理的信号,处理的方式
    //创建子进程１，２
    child1=fork();
    if(child1==0)
    {
        printf("child1 pid %d\n",getpid());
        signal(SIGINT,SIG_IGN);/*SIGINT     终止进程     中断进程*/
        signal(SIGUSR1,SignHandler2);/*SIGUSR1   终止进程     用户定义信号1
SIGUSR2   终止进程     用户定义信号2*/
        while(1)
        {
            close(filedis[0]);
            sprintf(info,"child1 sends message %d \n",counter);
            write(filedis[1],info,30);
            counter++;
            sleep(1);
        }
    }
    else if(child1>0)//返回主进程
    {
        child2=fork();//创建子进程2
        if(child2==0)
        {
            printf("child2 pid %d\n",getpid());
            signal(SIGINT,SIG_IGN);
            signal(SIGUSR1,SignHandler2);
            while(1)
            {
                close(filedis[1]);
                read(filedis[0],buffer,40);
                printf("%s",buffer);
            }
        }
        //等待进程1,2退出
        waitpid(child1,NULL,0);
        printf("Child process 1 is over\n");
        waitpid(child2,NULL,0);
        printf("Child process 2 is over\n");
        //关闭管道
        close(filedis[0]);
        close(filedis[1]);
        printf("Parent process is killed\n");
    }
    return 0;
}

void SignHandler1(int iSignNo)
{
    printf("\nParent gets Ctrl+C\n");
    if(iSignNo==SIGINT)   //传递SIGUSR信号给子进程
    {
        kill(child1,SIGUSR1);
        kill(child2,SIGUSR2);
    }
}
void SignHandler2(int iSignNo)
{
    close(filedis[0]);
    close(filedis[1]);
    if(child1==0&&iSignNo==SIGUSR1)
    {
        printf("Child process 1 is killed by Parent!\n");
        exit(0);
    }
    if(child2==0&&iSignNo==SIGUSR1)
    {
        printf("Child process 2 is killed by Parent!\n");
        exit(0);
    }
}
