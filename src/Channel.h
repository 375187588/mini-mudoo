#pragma once

#include <memory>
#include <functional>

class EventLoop;

class Channel: public std::enable_shared_from_this<Channel>{
public:
	static const int READEVENT;
	static const int WRITEEVENT;
	static const int NONEEVENT;

	typedef std::function<void()> ReadCallback;

public:
	Channel(std::shared_ptr<EventLoop> loop, int fd);
	void EnabelReading();
	inline int Events() const { return m_events; }
	inline int Fd() const { return m_fd; }
	void HandleEvent();
	inline void SetReadCallback(ReadCallback callback) { m_read_callback = callback; }

private:
	std::shared_ptr<EventLoop> m_loop;
	int m_fd;
	int m_events;
	ReadCallback m_read_callback;
};