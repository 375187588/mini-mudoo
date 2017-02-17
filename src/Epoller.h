#pragma once

#include <sys/epoll.h>

#include <memory>
#include <unordered_map>
#include <vector>

#include "EventLoop.h"
#include "Channel.h"

class Epoller {
public:
    Epoller(std::shared_ptr<EventLoop> loop);
    void Poll(std::vector<std::weak_ptr<Channel>>& activeChannels);
    void UpdateChannel(std::shared_ptr<Channel> channel);
    void UpdateChannel(int epollType, std::shared_ptr<Channel> channel);
    void FillActiveChannels(int num, std::vector<std::weak_ptr<Channel>>& channels);

private:
    std::shared_ptr<EventLoop> m_loop;
    std::unordered_map<int, std::shared_ptr<Channel>> m_channels;

    int m_epoll_fd;
    std::vector<epoll_event> m_events;
};