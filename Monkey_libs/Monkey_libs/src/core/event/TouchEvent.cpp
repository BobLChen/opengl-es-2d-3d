//
//  TouchEvent.cpp
//  Monkey_libs
//
//  Created by Neil on 4/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/event/TouchEvent.h"

NS_MONKEY_BEGIN

const std::string TouchEvent::TOUCH_BEGAN   = "TOUCH_BEGAN";
const std::string TouchEvent::TOUCH_END     = "TOUCH_END";
const std::string TouchEvent::TOUCH_HIT     = "TOUCH_HIT";

const std::string TouchEvent::RIGHT_MOUSE_DOWN  = "RIGHT_MOUSE_DOWN";
const std::string TouchEvent::RIGHT_MOUSE_UP    = "RIGHT_MOUSE_UP";
const std::string TouchEvent::RIGHT_MOUSE_CLICK = "RIGHT_MOUSE_CLICK";

const std::string TouchEvent::MIDDLE_MOUSE_DOWN = "MIDDLE_MOUSE_DOWN";
const std::string TouchEvent::MIDDLE_MOUSE_UP   = "MIDDLE_MOUSE_UP";
const std::string TouchEvent::MIDDLE_MOUSE_CLICK= "MIDDLE_MOUSE_CLICK";

const std::string TouchEvent::TOUCH_MOVE    = "TOUCH_MOVE";
const std::string TouchEvent::TOUCH_IN      = "TOUCH_IN";
const std::string TouchEvent::TOUCH_OUT     = "TOUCH_OUT";
const std::string TouchEvent::MOUSE_WHEEL   = "MOUSE_WHEEL";

TouchEvent::TouchEvent(std::string type, bool bubbles, const Point2D *mpoints, const int ssize) :
Event(type, bubbles),
points(mpoints),
size(ssize),
deltaX(0.0f),
deltaY(0.0f),
mouseX(0.0f),
mouseY(0.0f)
{
    
}

TouchEvent::~TouchEvent() {
    
}

NS_MONKEY_END