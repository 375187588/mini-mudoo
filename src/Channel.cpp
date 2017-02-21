#include <poll.h>

#include "Channel.h"

constexpr int Channel::NONEEVENT = 0;
constexpr int Channel::READEVENT = POLLIN | POLLPRI;
constexpr int Channel::WRITEEVENT = POLLOUT;

Channel::Channel(std::shared_ptr<EventLoop> loop, int fd):
	m_loop(loop),
	m_fd(fd),
	m_events(NONEEVENT) {

}

void Channel::EnableReading() {
	m_events |= READEVENT;
	m_loop->UpdateChannel(shared_from_this());
}

void Channel::HandleEvent() {
	if (m_events & (POLLIN | POLLPRI | POLLRDHUP)) {
		if (m_read_callback) m_read_callback();
	}
}