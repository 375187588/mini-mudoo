#include <unistd.h>

#include <functional>
#include <iostream>
#include <cassert>

#include "Acceptor.h"

Acceptor::Acceptor(std::shared_ptr<EventLoop> loop,const InetAddress& addr) :
    m_loop(loop),
    m_socket(new Socket(addr, Socket::Type::STREAM_SOCK, Socket::Protocol::DEFAULT)),
    m_accept_channel(std::make_shared<Channel>(loop, m_socket->Fd())){
    m_socket->Bind();
    m_accept_channel->SetReadCallback(std::bind(&Acceptor::HandleRead, this));
}

void Acceptor::Listen() {
    m_socket->Listen();
    m_accept_channel->EnableReading();
}

void Acceptor::HandleRead() {
    InetAddress addr;
    auto fd = m_socket->Accept(addr);

    std::assert(fd > 0);

    std::cout << "pretty good, new connection:" << addr.GetId() << ":" << addr.GetPort() << std::endl;

    ::close(fd);
}
