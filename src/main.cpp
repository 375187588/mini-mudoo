#include "EventLoop.h"
#include "TcpServer.h"
#include "InetAddress.h"

int main() {
    auto loop_ptr = std::make_shared<EventLoop>();
    InetAddress addr("127.0.0.1", 6789, InetAddress::Domain::INET_AF);

    std::make_shared<TcpServer>(loop_ptr, addr);

    loop_ptr->Loop();
}