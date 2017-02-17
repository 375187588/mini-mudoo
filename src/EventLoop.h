#pragma once

#include <memory>
#include <thread>

#include "Channel.h"
#include "Epoller.h"

class EventLoop : public std::enable_shared_from_this<EventLoop>{
public:
    EventLoop();
    void Loop();
    void Quit();

private:
    const bool IsInLoopThread() const { return m_thread_id == std::this_thread::get_id();}
    void UpdateChannel(std::shared_ptr<Channel> channel) const;

private:
    bool m_quit;
    size_t m_wake_up_fd;
    std::thread::id m_thread_id;
    std::shared_ptr<Epoller> m_poller;
};