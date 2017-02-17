#include <cassert>

#include "Epoller.h"

Epoller::Epoller(std::shared_ptr<EventLoop> loop):
    m_loop(loop),
    m_epoll_fd(::epoll_create1(EPOLL_CLOEXEC)),
    m_events(512) {
    std::assert(m_epoll_fd > 0);
}

void Epoller::Poll(std::vector<std::weak_ptr<Channel>>& activeChannels) {
       auto num = ::epoll_wait(m_epoll_fd, &*m_events.begin(), 512, 0);

       FillActiveChannels(num, activeChannels);
}

void Epoller::UpdateChannel(std::shared_ptr<Channel> channel) {
    if (m_channels.find(channel->Fd()) == m_channels.end()) {
        // add channel
        UpdateChannel(EPOLL_CTL_ALL, channel);
    }
    else {
        UpdateChannel(channel->Events() == Channel::NONEEVENT ? EPOLL_CTL_DEL : EPOLL_CTL_MOD, channel);
    }
}

void Epoller::UpdateChannel(int epollType, std::shared_ptr<Channel> channel){
    struct epoll_event ev;

    ev.events = channel->Events();
    ev.data.ptr = channel->get();

    ::epoll_ctl(m_epoll_fd, epollType, &ev);
}

void Epoller::FillActiveChannels(int num, std::vector<std::weak_ptr<Channel>>& activeChannels) {
    for(auto i = 0; i < num; ++i) {
        activeChannels.push_back(std::make_weak<Channel>(m_events[i].data.ptr));
    }
}


