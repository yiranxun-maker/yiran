#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>

const char* get_name(int a){
    switch(a){
        case 0:return "石头";
        case 1:return "剪刀";
        case 2:return "布";
        default:return "未知";
    }
}


int main(){
    int child_to_parent[2];
    int parent_to_child[2];
    if (pipe(child_to_parent)==-1||pipe(parent_to_child)==-1)
    {
        perror("管道申请失败");
        return 1;
    }
    pid_t pid=fork();
    if (pid<0)
    {
        perror("fork faild");
        return 1;
    }else if (pid==0)
    {
        close(child_to_parent[0]);
        close(parent_to_child[1]);
        int childchoice;
        int parentchoie;
        srand(time(NULL)^getpid());
        childchoice=rand()%3;
        write(child_to_parent[1],&childchoice,sizeof(int));
        read(parent_to_child[0],&parentchoie,sizeof(int));
        exit(0);
    }else{
        close(child_to_parent[1]);
        close(parent_to_child[0]);
        int childchoice;
        int parentchoice;
        printf("请输入出拳\n");
        scanf("%d",&parentchoice);
        while (parentchoice<0||parentchoice>2)
        {
            printf("请重新输入\n");
            scanf("%d",&parentchoice);
        }
        
        write(parent_to_child[1],&parentchoice,sizeof(int));
        read(child_to_parent[0],&childchoice,sizeof(int));
        printf("你的出拳为%s\n",get_name(parentchoice));
        printf("对方的出拳为%s\n",get_name(childchoice));
        int a=childchoice-parentchoice;
        if (a>1||a<0)
        {
            printf("你输了\n");
        }else if (a==0)
        {
            printf("平局\n");
        }else if (a==1)
        {
            printf("你输了\n");
        }
        wait(NULL);
        return 0;

        
        
        
        
        
    }
    
    
    
}