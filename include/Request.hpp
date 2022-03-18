#pragma once;
#include"Common.hpp"
class Request
{
    public:
    void request_init(int ,const sockaddr_in *);
    void process();
    private:
    int fd;
    sockaddr_in addr;
};