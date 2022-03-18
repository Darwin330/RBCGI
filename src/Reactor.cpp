#pragma once
#include"Reactor.hpp"
#include"Eventmultiplexer.hpp"

Reactor::Reactor()
{
    m_demultiplexer =new Eventmultiplexer();
}

Reactor::~Reactor()
{
    //delete m_demultiplexer;
}

void Reactor::register_handler(Handle* m_handle)
{
    m_demultiplexer->register_event(m_handle);
}

void Reactor::remove_handler(Handle* m_handle)
{
    m_demultiplexer->remove_event(m_handle);
}

void Reactor::handle_event()
{
    m_demultiplexer->demutiplexer();
}