#pragma once

#include <memory>

#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Channel.h"

class Acceptor {
public:
    Acceptor(std::shared_ptr<EventLoop> loop, const InetAddress& addr);
    void Listen();
    void HandleRead();
    
private:
    std::shared_ptr<EventLoop> m_loop;
    std::unique_ptr<Socket> m_socket;
    std::shared_ptr<Channel> m_accept_channel;
};