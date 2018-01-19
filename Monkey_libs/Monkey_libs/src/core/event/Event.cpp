//
//  Event.cpp
//  Monkey
//
//  Created by Neil on 6/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/event/Event.h"
#include "core/event/EventDispatcher.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

const std::string Event::ACTIVE   = "ACTIVE";
const std::string Event::DISABLE  = "DISABLE";
const std::string Event::COMPLETE = "COMPLETE";

Event::Event(std::string type, bool bubbles):
Object(),
_bubbles(bubbles),
_stopPropagation(false),
_stopImmediatePropagation(false),
_currentTarget(nullptr),
_target(nullptr),
_eventPhase(EventPhase::AT_TARGET)
{
    this->type  = type;
}

Event::~Event() {
    _currentTarget  = nullptr;
    _target         = nullptr;
}

void Event::stopImmediatePropagation() {
    _stopImmediatePropagation = true;
}

void Event::stopPropagation() {
    _stopPropagation = true;
}

bool Event::isImmediatePropagation() const {
    return _stopImmediatePropagation;
}

bool Event::isPropagation() const {
    return _stopPropagation;
}

bool Event::isBubbles() const {
    return _bubbles;
}

void Event::copyFrom(monkey::Event *event) {
    _eventPhase = event->getEventPhase();
    _target     = event->getTarget();
    _bubbles    = event->isBubbles();
    _currentTarget      = event->getCurrentTarget();
    _stopPropagation    = event->isPropagation();
    _stopImmediatePropagation = event->isImmediatePropagation();
}

EventDispatcher* Event::getCurrentTarget() const {
    return _currentTarget;
}

EventDispatcher* Event::getTarget() const {
    return _target;
}

Event::EventPhase Event::getEventPhase() const {
    return _eventPhase;
}

void Event::setCurrentTarget(EventDispatcher *target) {
    _currentTarget = target;
}

void Event::setTarget(EventDispatcher *target) {
    _target = target;
}

void Event::setEventPhase(Event::EventPhase phase) {
    _eventPhase = phase;
}

void Event::reset() {
    _target                     = nullptr;
    _currentTarget              = nullptr;
    _eventPhase                 = Event::EventPhase::AT_TARGET;
    _stopImmediatePropagation   = false;
    _stopPropagation            = false;
    _bubbles                    = false;
}
NS_MONKEY_END
