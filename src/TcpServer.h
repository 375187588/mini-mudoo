#pragma once

#include <memory>

#include "Acceptor.h"
#include "EventLoop.h"
#include "InetAddress.h"

class TcpServer : public std::enable_shared_from_this<TcpServer> {
public:
    TcpServer(std::shared_ptr<EventLoop> loop, const InetAddress addr);
   
private:
    std::unique_ptr<Acceptor> m_acceptor;
    std::shared_ptr<EventLoop> m_loop;
};