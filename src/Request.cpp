#include"Request.hpp"
void Request::request_init(int fdval,const sockaddr_in* addrval)
{
    fd=fdval;
    addr=*addrval;
}

void Request::process()
{
    printf("process finised/n");
}
