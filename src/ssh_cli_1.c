#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<assert.h>
//#include <sys/ioctl.h>
#include <fcntl.h>
// 与多进程操作相关的头文件
//#include <sys/wait.h>
//#include <sys/ipc.h>
//#include <sys/shm.h>
#include <signal.h>

// 与多线程相关的头文件
// 注意，应在编译时链接线程库，增加编译选项 -lthread
//#include <pthread.h>
//聊天室客户端程序
#include <sys/poll.h>
#define MAX_FD 2
#define BUFFER_SIZE 1000
int main(int argv,char**argc){
    if(argv<=2){
        printf("usage: %s ip port_number",argc[0]);
        return -1;
    }

    int port=atoi(argc[2]);
    const char* ip=argc[1];
    
    struct sockaddr_in servaddr;

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&servaddr.sin_addr);

    int sockfd,ret;
    
    sockfd=socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd>=0);
    
    ret=connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    assert(ret!=-1);
    
    struct pollfd fds[MAX_FD];
    //bzero(&fds,sizeof(fds));
    fds[0].fd=fileno(stdin);
    fds[0].events=POLLIN;

    fds[1].fd=sockfd;
    fds[1].events=POLLIN|POLLHUP;

    int nready,n,stdineof;
    //memset(buf,0,BUFFER_SIZE);
    stdineof=0;
    for(;;){
        nready=poll(fds,MAX_FD,0);
        char buf[BUFFER_SIZE];
        
        if(fds[1].revents&POLLIN){
            n=recv(sockfd,buf,BUFFER_SIZE,0);
            if(n==0){
                if(stdineof==1){

                    return 0;
                }
                printf("server closed\n");
                close(sockfd);
                return 0;
            }else{

                printf("got %d msg: %s",n,buf);
            }
            if(--nready==0)continue;
        }
        
        if(fds[0].revents&POLLIN){
            //memset(buf,0,BUFFER_SIZE);
            if((n=read(fds[0].fd,buf,BUFFER_SIZE))==0){
                printf("stdin close\n");
                shutdown(sockfd,SHUT_WR);
                stdineof=1;
            }else{
                send(sockfd,buf,n,0);
            }
        }
    }
    //servaddr

    return 0;
}