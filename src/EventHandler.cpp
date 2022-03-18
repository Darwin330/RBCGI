#pragma once
#include"EventHandler.hpp"
#include"Handle.hpp"

ConcreteHandler::ConcreteHandler(Handle* handle){
    set_handle(handle);
}

Handle* ConcreteHandler::getHandle()
{
    return m_handle;
}

void ConcreteHandler::handle_event(){
       
    int revents= m_handle->get_revents();       
    int fd=m_handle->get_fd();
    if(revents & EPOLLIN)
    {
       readcallback(fd);
    }
    if(revents & EPOLLOUT)
    {
       writecallback(fd);
    }
    if(revents & EPOLLERR)
    {
       errorcallback(fd);
    }
}

void ConcreteHandler::set_handle(Handle* handle)
{
    m_handle=handle;
    m_handle->set_handler(this);
}

void ConcreteHandler::set_readcb(Eventcallback f)
{
    readcallback=f;
}

void ConcreteHandler::set_writecb(Eventcallback f)
{
   writecallback=f;
}

void ConcreteHandler::set_errorcb(Eventcallback f)
{
    errorcallback=f;
}