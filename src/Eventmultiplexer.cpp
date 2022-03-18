#pragma once
#include"Eventmultiplexer.hpp"
#include"Handle.hpp"

Eventmultiplexer::Eventmultiplexer()
{
    epollfd=epoll_create(EPOLLFD_MAXSIZE);
    assert(epollfd>=0);
}

Eventmultiplexer::~Eventmultiplexer()
{
    close(epollfd);
}

void Eventmultiplexer::register_event(Handle* m_handle)
{
    struct epoll_event event;
    event.data.ptr=m_handle;
    event.events=m_handle->get_events();
    int op;
    if(m_handle->is_inpool()) 
        op=EPOLL_CTL_MOD;
    else 
        op=EPOLL_CTL_ADD;
    assert(epoll_ctl(epollfd,op,m_handle->get_fd(),&event)!=-1);

    setnonblocking(m_handle->get_fd());

    m_handle->set_inpool(true);
}

void Eventmultiplexer::remove_event(Handle* m_handle)
{
    epoll_ctl(epollfd,EPOLL_CTL_DEL,m_handle->get_fd(),nullptr);
}

void Eventmultiplexer::demutiplexer()
{
    int nready;

    while(1){

        nready=epoll_wait(epollfd,events,MAX_FDSIZE,-1);
        
        if(nready<0){
            printf("epoll faiulre\n");
            return ;
        }

        for(int i=0;i<nready;i++)
        {
            Handle* cur= static_cast<Handle*>(events[i].data.ptr);
            cur->set_revents(events[i].events);
            cur->handle_event();

        }
    }

}
