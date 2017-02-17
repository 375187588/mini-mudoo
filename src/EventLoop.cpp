#include <thread>
#include <iostream>
#include <vector>

#include "EventLoop.h"

EventLoop::EventLoop():
    m_quit(false),
    m_thread_id(std::this_thread::get_id()),
    m_poller(std::make_shared<Epoller>(shared_from_this())) {

}

void EventLoop::Loop() {
    while (!m_quit) {
        std::vector<std::weak_ptr<Channel>> activeChannels;
        m_poller->Poll(activeChannels);

        for(auto& channel: activeChannels){
            channel->HandleEvent();
        }
    }
}

void EventLoop::UpdateChannel(std::shared_ptr<Channel> channel) const {
    m_poller->UpdateChannel(channel);
}

void EventLoop::Quit() {
    m_quit = true;
}