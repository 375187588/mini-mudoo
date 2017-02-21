#include <memory>

#include "TcpServer.h"

TcpServer::TcpServer(std::shared_ptr<EventLoop> loop, const InetAddress addr):
    m_loop(loop),
    m_acceptor(new Acceptor(loop, addr)) {
}
