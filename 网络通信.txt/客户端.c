#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#define FORK 8080

int main()
{
    int sock;
    int clientchoice;
    struct sockaddr_in ser_addr;
    char result_msg[100]={0};
    int b=0;

    if ((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("fail socket");
        return -1;
    }
    
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(FORK);

    if (inet_pton(AF_INET,"127.0.0.1",&ser_addr.sin_addr)<=0)
    {
        perror("fail id");
        return -1;
    }

    if (connect(sock,(struct sockaddr*)&ser_addr,sizeof(ser_addr))<0)
    {
        perror("fail connect");
        return -1;
    }
    printf("游戏即将开始\n");
    printf("请输入结果\n");
    scanf("%d",&clientchoice);
    send(sock,&clientchoice,sizeof(int),0);
    read(sock,&b,sizeof(int));
    read(sock,&result_msg,b);
    printf("结果为%s\n",result_msg);
    printf("游戏结束\n");
    close(sock);
    return 0;

    
}