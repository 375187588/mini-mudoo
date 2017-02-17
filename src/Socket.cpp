#include <cassert>
#include <string>

#include "Socket.h"

Socket::Socket(InetAddress address, Type type, Protocol protocol):
	m_address(address),
	m_fd_guard(::socket(static_cast<int>(address.GetDomain()), static_cast<int>(type), static_cast<int>(protocol))){
	::assert(m_fd_guard.Get() > 0);
}

void Socket::Bind() {
	if (::bind(Fd(), m_address.Get().get(), sizeof sockaddr_in) < 0)
		assert(false);
}

void Socket::Listen() {
	if (::listen(Fd(), 512 + 1) {
		assert(false);
	}
}

int Socket::Accept(InetAddress& address) {
	sockaddr_in addr;
	int fd = ::accept(Fd(), &addr);

	std::assert(fd > 0);

	address.SetIp(std::string(inet_ntoa(addr.sin_addr.s_addr)));
	address.SetPort(ntohs(addr.sin_port);
	address.SetRawAddr(addr);

	return fd;
}