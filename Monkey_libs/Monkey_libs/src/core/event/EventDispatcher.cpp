//
//  EventDispatcher.cpp
//  Opengl2D
//
//  Created by Neil on 6/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "platform/PlatformMacros.h"
#include "core/event/Event.h"
#include "core/event/EventDispatcher.h"

#include <algorithm>

NS_MONKEY_BEGIN

EventDispatcher::EventDispatcher() : Object() {

}

EventDispatcher::~EventDispatcher() {
    for (auto listeners = _listenersDict.begin(); listeners != _listenersDict.cend(); ++listeners) {
        (listeners->second).clear();
    }
    _listenersDict.clear();
    for (auto monitors = _monitorDict.begin(); monitors != _monitorDict.cend(); monitors++) {
        (monitors->second).clear();
    }
    _monitorDict.clear();
}

void EventDispatcher::addEventListener(std::string type, Object *monitor, const EventFunction listener) {
    
    auto it = _listenersDict.find(type);
    // 如果表中没有、则添加一个list
    if (it == _listenersDict.end()) {
        _listenersDict.insert(std::make_pair(type, std::vector<EventFunction>()));
        _monitorDict.insert(std::make_pair(type, std::vector<Object*>()));
        it = _listenersDict.find(type);
    }
    // 未找到listener
    auto it2 = std::find((it->second).begin(), (it->second).end(), listener);
    if (it2 == (it->second).end()) {
        (it->second).push_back(listener);
        // 添加monitor
        auto miter = _monitorDict.find(type);
        (miter->second).push_back(monitor);
    }
}

void EventDispatcher::dispatchEvent(Event &event) {
    
    if (event.getEventPhase() == Event::EventPhase::AT_TARGET) {
        event.setTarget(this);
    }
    if (event.isBubbles()) {
        event.setEventPhase(Event::EventPhase::BUBBLING_PHASE);
    } else {
        event.setTarget(this);
        event.setEventPhase(Event::EventPhase::AT_TARGET);
    }
    
    event.setCurrentTarget(this);
    
    if (event.isImmediatePropagation()) {
        return;
    }
    
    auto it = _listenersDict.find(event.type);
    if (it == _listenersDict.end()) {
        return;
    }
    // 派发事件
    int idx = 0;
    for (auto listener = (it->second).begin(); listener != (it->second).end(); ++listener) {
        EventFunction func = *listener;
        Object *_sender = (_monitorDict.find(event.type)->second).at(idx);
        (_sender->*func)(event);
        idx++;
    }
}

bool EventDispatcher::hasEventListener(std::string type) {
    auto it = _listenersDict.find(type);
    if (it == _listenersDict.end()) {
        return false;
    }
    return true;
}

void EventDispatcher::removeEventListener(std::string type, Object *monitor, const EventFunction listener) {
    auto it = _listenersDict.find(type);
    if (it == _listenersDict.end()) {
        return;
    }
    auto it2 = std::find((it->second).begin(), (it->second).end(), listener);
    if (it2 == (it->second).end()) {
        return;
    }
    (it->second).erase(it2);
    // monitor数据一定是和lister对应起来的
    auto mvector = (_monitorDict.find(type))->second;
    auto midx = std::find(mvector.begin(), mvector.end(), monitor);
    mvector.erase(midx);
}

NS_MONKEY_END
