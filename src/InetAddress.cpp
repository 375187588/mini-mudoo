#include "InetAddress.h"

InetAddress::InetAddress(std::string ip, Port port, Domain domain):
	m_ip(ip),
	m_port(port),
	m_domain(domain),
	m_addr(std::make_shared<sockaddr_in>()) {
		m_addr->sin_family = static_cast<int>(domain);
		m_addr->sin_port = ::htons(m_port);
		m_addr->sin_addr.s_addr = ::inet_addr(m_ip.c_str());
}