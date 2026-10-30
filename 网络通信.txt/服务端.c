/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

const char* get_name(int choice) {
    switch(choice) {
        case 0: return "石头";
        case 1: return "剪刀";
        case 2: return "布";
        default: return "未知";
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int client_choice, server_choice;
    char result_msg[100];

    // 创建Socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 绑定
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // 监听
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("游戏服务端已启动，正在监听端口 %d...\n", PORT);
    srand(time(NULL));

    while(1) {
        // 接受连接
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        // 接收客户端出拳
        read(new_socket, &client_choice, sizeof(int));
        printf("收到客户端出拳: %s\n", get_name(client_choice));

        // 生成服务端出拳
        server_choice = rand() % 3;
        printf("服务端出拳: %s\n", get_name(server_choice));

        // 判断胜负
        if (client_choice == server_choice) {
            strcpy(result_msg, "平局！");
        } else if ((client_choice == 0 && server_choice == 1) || 
                   (client_choice == 1 && server_choice == 2) || 
                   (client_choice == 2 && server_choice == 0)) {
            strcpy(result_msg, "你赢了！");
        } else {
            strcpy(result_msg, "电脑赢了！");
        }

        // 发送结果
        send(new_socket, result_msg, strlen(result_msg), 0);
        printf("本局结束，等待下一个玩家...\n\n");
        close(new_socket);
    }
    return 0;
}*/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>

#define PORT 8080

char *get_name(int a){
    switch(a){
        case 0:return "石头";
        case 1:return "剪刀";
        case 2:return "布";
        default:return "未知";
    }
}

int main(){
    int server_fd,newsock;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    int opt=1;
    int serverchoice,clientchoice;
    char result_msg[100];
    if ((server_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("fail sock\n");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);

    if (bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0)
    {
        perror("fail bind\n");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd,3)<0)
    {
        perror("fail listen\n");
        exit(EXIT_FAILURE);
    }
    printf("正在监听端口\n");
    while (1)
    {
    if ((newsock=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0)
    {
        perror("fail accept\n");
        continue;
    }

    printf("游戏准备开始\n");
    read(newsock,&clientchoice,sizeof(clientchoice));
    printf("客户出拳为%s\n",get_name(clientchoice));
    serverchoice=rand()%3;
    printf("服务端出拳为%s\n",get_name(serverchoice));
    int result=clientchoice-serverchoice;
    if (result<0||result>1)
    {
        strcpy(result_msg,"你赢了");
    }else if (result==0)
    {
        strcpy(result_msg,"平局");
    }else 
    if (result==1)
    {
        strcpy(result_msg,"你输了");
    }
    int a=strlen(result_msg);
    send(newsock,&a,sizeof(int),0);
    send(newsock,result_msg,strlen(result_msg)+1,0);
    close(newsock);
    printf("游戏结束,等待下一个玩家\n");
    }
    
    
    
    
    
    

}



