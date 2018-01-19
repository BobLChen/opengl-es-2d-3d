//
//  EventDispatcher.h
//  Opengl2D
//
//  Created by Neil on 6/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _EventDispatcher_h
#define _EventDispatcher_h

#include <string>
#include <map>
#include <vector>

#include "core/base/Object.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class Event;

/**
 *  定义回调函数
 *  @param Event 事件
 *  @return
 */
typedef void (Object::*EventFunction)(Event &e);
#define EVENT_CALLBACK(_FUNC) (EventFunction)(&_FUNC)

class EventDispatcher : public Object {
    
public:
    
    EventDispatcher();
    virtual ~EventDispatcher();
    /**
     *  添加监听器
     *  @param type     事件类型
     *  @param monitor  监听者
     *  @param listener 回调函数
     */
    virtual void addEventListener(std::string type, Object *monitor, const EventFunction listener);
    /**
     *  派发事件
     *  @param event 事件
     */
    virtual void dispatchEvent(Event &event);
    /**
     *  是否存在监听器
     *  @param type  事件类型
     *  @return
     */
    virtual bool hasEventListener(std::string type);
    /**
     *  移除监听器
     *  @param type     事件类型
     *  @param monitor  监听者
     *  @param listener 回调函数
     */
    virtual void removeEventListener(std::string type, Object *monitor, const EventFunction listener);
    
protected:
    std::map<std::string, std::vector<EventFunction>> _listenersDict;
    std::map<std::string, std::vector<Object*>> _monitorDict;
};

NS_MONKEY_END

#endif
