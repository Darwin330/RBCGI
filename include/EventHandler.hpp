#pragma once
#include"Common.hpp"
//#include"Handle.hpp"

class Handle;

class EventHandler{

public:

    virtual void handle_event()=0;

};

class ConcreteHandler: public EventHandler
{

public:
    ConcreteHandler(Handle* h);
    ~ConcreteHandler();
    void handle_event();

    Handle* getHandle();

    void set_handle(Handle* handle);

    void set_readcb(Eventcallback f);

    void set_writecb(Eventcallback f);

    void set_errorcb(Eventcallback f);

private:

    Handle* m_handle;
    Eventcallback readcallback;
    Eventcallback writecallback;
    Eventcallback errorcallback;
};