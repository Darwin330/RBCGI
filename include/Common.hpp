#ifndef COMMON_H
#define COMMON_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <sys/ioctl.h>
#include <fcntl.h>
// 与多进程操作相关的头文件
//#include <sys/wait.h>
//#include <sys/ipc.h>
//#include <sys/shm.h>
//#include <signal.h>

// 与多线程相关的头文件
// 注意，应在编译时链接线程库，增加编译选项 -lthread
//#include <pthread.h>
//聊天室服务器程序
//#include <sys/poll.h>
#include <sys/epoll.h>
//#include<unordered_map>
#include<functional>
#include<vector>
#include<unordered_set>
/*
struct sock_info{
    int fd;
    struct sockaddr_in;

};*/

typedef  std::function<void(int )> Eventcallback;
int setnonblocking(int fd);
#define MAX_FDSIZE 1000
#define BUFFER_SIZE 65536

#endif