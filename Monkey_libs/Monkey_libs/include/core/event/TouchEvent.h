//
//  TouchEvent.h
//  Monkey
//
//  Created by Neil on 15/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _TouchEvent_h
#define _TouchEvent_h

#include "core/event/Event.h"
#include "core/geom/Vector2D.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class TouchEvent : public Event {
    
public:
    
    // 左键
    static const std::string TOUCH_BEGAN;
    static const std::string TOUCH_END;
    static const std::string TOUCH_HIT;
    // 右键
    static const std::string RIGHT_MOUSE_DOWN;
    static const std::string RIGHT_MOUSE_UP;
    static const std::string RIGHT_MOUSE_CLICK;
    // 中键
    static const std::string MIDDLE_MOUSE_DOWN;
    static const std::string MIDDLE_MOUSE_UP;
    static const std::string MIDDLE_MOUSE_CLICK;
    // mouse
    static const std::string TOUCH_MOVE;
    static const std::string TOUCH_IN;
    static const std::string TOUCH_OUT;
    static const std::string MOUSE_WHEEL;
    
    TouchEvent(std::string type, bool bubbles, const Point2D *mpoints = nullptr, const int ssize = 0);
    virtual ~TouchEvent();
    
    const Point2D *points;
    const int size;
    // mouse wheel
    float deltaX;
    float deltaY;
    // mouse (x,y)
    float mouseX;
    float mouseY;
};

typedef TouchEvent MouseEvent;

NS_MONKEY_END

#endif
