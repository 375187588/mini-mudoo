#pragma once

#include <sys/types.h>
#include <sys/socket.h>

#include "InetAddress.h"
#include "FdGuard.h"

class Socket {
public:
	enum class Type {
		STREAM_SOCK = SOCK_STREAM,
		//TODO: more
	};

	enum class Protocol {
		DEFAULT = 0,
		TCP_IPPROTO = IPPROTO_TCP,
		//TODO: more
	};

public:
	Socket(InetAddress, Type, Protocol);

	const inline int Fd() const { return m_fd_guard.Get(); }
	inline void Bind();
	inline void Listen();
	int Accept(InetAddress&);

private:
	InetAddress m_address;
	FdGuard m_fd_guard;

	Type m_type;
	Protocol m_protocol;
};