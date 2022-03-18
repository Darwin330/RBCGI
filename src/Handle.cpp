#pragma once
#include"Handle.hpp"
#include"EventHandler.hpp"
Handle::Handle(int fd_){
    fd=fd_;
    events=0;
    revents=0;
    inpool=false;
    handler=nullptr;
}

Handle::~Handle()
{
    close(fd);
}

void Handle::set_inpool(bool f){
    inpool=f;
}

void Handle::set_event(int event){
    events=event;
}

void Handle::set_handler(EventHandler* m_handler){
    handler=m_handler;
}

void Handle::set_revents(int r){
    revents=r;
}

int Handle::get_fd(){
    return fd;
}

int Handle::get_events(){
    return events;
}

int Handle::get_revents(){
    return revents;
}

void Handle::handle_event(){
    handler->handle_event();
}

bool Handle::is_inpool()
{
    return inpool;
}