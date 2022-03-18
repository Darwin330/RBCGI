#pragma once
#include"Common.hpp"
int setnonblocking(int fd){
    int old_options =  fcntl( fd , F_GETFL );
    int new_options = old_options|O_NONBLOCK;
    assert(fcntl(fd,F_SETFL,new_options)!=-1);
    return old_options;
}