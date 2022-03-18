#ifndef HANDLE_H
#define HANDLE_H

class EventHandler;

class Handle
{

public:

    Handle(int fd_);
    ~Handle();
    void set_event(int event);
    void set_handler(EventHandler*  m_handler);
    void set_inpool(bool );
    void set_revents(int );
    int get_events();
    int get_revents();
    int get_fd() ;
    bool is_inpool();
    //事件就绪，委托事件处理器处理；
    void handle_event();

private:

    bool inpool;
    int fd;
    int events;
    int revents;
    EventHandler* handler; 

};

#endif