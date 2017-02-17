#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <cstdint>
#include <memory>
#include <string>

class InetAddress {
public:
	enum class Domain{
		INET_AF = AF_INET,
		//TODO: more
	};

	typedef std::uint16_t Port;

public:
	InetAddress(std::string ip, InetAddress::Port port, Domain domain);

	inline std::string GetIp() const { return m_ip; }

	inline Port GetPort() const { return m_port; }

	inline Domain GetDomain() const { return m_domain; }

	inline std::shared_ptr<sockaddr_in> Get() const { return m_addr; }

	inline void SetIp(std::string ip) { m_ip = ip; }

	inline void SetPort(Port port) { m_port = port; }

	inline void SetDomain(Domain domain) { m_domain = domain; }

	inline void SetRawAddr(sockaddr_in addr) { m_addr = std::make_shared<sockaddr_in>(addr); };

private:
	std::string m_ip;
	Port m_port;
	Domain m_domain;
	std::shared_ptr<sockaddr_in> m_addr;
};