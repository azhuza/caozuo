//os_3
#include <iostream>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<syslog.h>
#include<string.h>
#include<stdlib.h>

#define MAX 128
using namespace std;
int modify();




int main()
{

    int fileID;//file的ID
    int num; //字符个数
    int choice;
    char buffer[MAX];  //读取的缓冲队列
    char *path="/bin/ls";
    char *argv[4]={"ls","-l","file1",NULL};
    while(1)
    {
        cout<<"***************************"<<endl;
        cout<<"1.创建新文件"<<endl;
        cout<<"2.写文件"<<endl;
        cout<<"3.读文件"<<endl;
        cout<<"4.修改文件权限"<<endl;
        cout<<"5.查看当前文件的权限"<<endl;
		cout<< "0.退出" << endl;
        cout<<"***************************"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 0:close(fileID);exit(0);
            case 1:
                fileID=open("file1",O_RDWR|O_TRUNC|O_CREAT,0750);//文件名，打开方式
                if(fileID==-1)
                {
                    cout<<"Failed!"<<endl;
                }
                else
                    cout<<"Succeed！fileID = "<<fileID<<endl;//显示file的ID
                break;
            case 2:
                num=read(0,buffer,MAX);//成功返回读取的字节数
                write(fileID,buffer,num);//从读入的信息送到file1里去
                break;
            case 3:
                read(fileID,buffer,MAX);
                write(1,buffer,num);//把file1文件的内容在屏幕上输出
                break;
            case 4:
                modify();
                cout<<"成功改变格式！"<<endl;
                break;
            case 5:
                execv(path,argv);//执行ls -l file1
                break;
            default:
                cout<<"error choice!"<<endl;

        }
    }


    return 0;
}


int modify()
{
    int c;
    mode_t mode=S_IWUSR;
    cout<<"0.所有用户读写执行"<<endl;
    cout<<"1.所有用户只可读"<<endl;
    cout<<"2.所有用户只可写"<<endl;
    cout<<"3.所有用户只可执行"<<endl;
    cout<<"4.用户组读写执行"<<endl;
    cout<<"5.用户组只可读"<<endl;
    cout<<"6.用户组只可写"<<endl;
    cout<<"7.用户组只可执行"<<endl;
    cin>>c;
    switch(c)
    {
        case 0:chmod("file1",S_IRWXU);break;
        case 1:chmod("file1",S_IRUSR);break;
        case 2:chmod("file1",S_IWUSR);break;
        case 3:chmod("file1",S_IXUSR);break;
        case 4:chmod("file1",S_IRWXG);break;
        case 5:chmod("file1",S_IRGRP);break;
        case 6:chmod("file1",S_IWGRP);break;
        case 7:chmod("file1",S_IXGRP);break;
        default:printf("error choice!\n");

    }
    return 0;
}
/*-rw------- (600) -- 只有属主有读写权限。  
-rw-r--r-- (644) -- 只有属主有读写权限；而属组用户和其他用户只有读权限。  
-rwx------ (700) -- 只有属主有读、写、执行权限。  
-rwxr-xr-x (755) -- 属主有读、写、执行权限；而属组用户和其他用户只有读、执行权限。  
-rwx--x--x (711) -- 属主有读、写、执行权限；而属组用户和其他用户只有执行权限。  
-rw-rw-rw- (666) -- 所有用户都有文件读、写权限。这种做法不可取。  
-rwxrwxrwx (777) -- 所有用户都有读、写、执行权限。更不可取的做法。  */
