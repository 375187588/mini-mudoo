#include <unistd.h>

#include <functional>
#include <iostream>

#include "Acceptor.h"

Acceptor::Acceptor(std::shared_ptr<EventLoop> loop,const InetAddress& addr) :
    m_loop(loop),
    m_socket(std::make_unique<Socket>(addr, Socket::Type::STREAM_SOCK, Socket::Protocol::DEFAULT)),
    m_accept_channel(std::make_shared(loop, m_socket.Fd())){
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

    assert(fd > 0);

    std::cout << "pretty good, new connection:" << addr.GetId() << ":" << addr.GetPort() << std::endl;

    ::close(fd);
}