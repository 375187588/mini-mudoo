#pragma once

#include <unistd.h>

class FdGuard {
public:
	FdGuard():
		m_fd(-1){

	}

	FdGuard(int fd):
		m_fd(fd) {

	}

	FdGuard(FdGuard&) = delete;
	FdGuard& operator=(FdGuard&) = delete;

	FdGuard(FdGuard&& rhs):
		m_fd(rhs.m_fd) {
		rhs.m_fd = -1;
	}

	FdGuard& operator=(FdGuard&& rhs) {
		m_fd = rhs.m_fd;
		rhs.m_fd = -1;
		return *this;
	}

	const int Get() const { return m_fd; }

	~FdGuard() {
		if (m_fd > 0) {
			::close(m_fd);
		}
	}
private:
	int m_fd;
};