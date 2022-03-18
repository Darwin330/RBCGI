#pragma once
#include"Common.hpp"

class Handle;
#define EPOLLFD_MAXSIZE 12
class Eventmultiplexer
{

public:

    Eventmultiplexer();
    ~Eventmultiplexer();
    void register_event(Handle*);
    void remove_event(Handle*);
    void demutiplexer();

private:

    int epollfd;
    epoll_event events[MAX_FDSIZE];
    std::unordered_set<Handle*> pool;
    
};