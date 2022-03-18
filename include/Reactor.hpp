#ifndef Reactor_H
#define Reactor_H
#include"Common.hpp"
//#include"Eventmultiplexer.hpp"
//事件发生器
//多路分发器
//
class Handle;
class Eventmultiplexer;

class Reactor
{

private:

    Eventmultiplexer* m_demultiplexer;

public:

    //创建Reactor
    Reactor();
    void handle_event();
    void register_handler(Handle*);
    void remove_handler(Handle*);
    //释放资源
    ~Reactor();

};

#endif