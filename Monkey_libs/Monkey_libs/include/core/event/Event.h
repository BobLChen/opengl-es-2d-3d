//
//  Event.h
//  Opengl2D
//
//  Created by Neil on 6/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _Event_h
#define _Event_h

#include "core/base/Object.h"
#include <string>

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class EventDispatcher;

class Event : public Object {
    
public:
    
    static const std::string ACTIVE;
    static const std::string DISABLE;
    static const std::string COMPLETE;
    
public:
    /**
     * 事件阶段
     */
    enum EventPhase {
        CAPTURING_PHASE,         // 捕获阶段
        AT_TARGET,               // 目标阶段
        BUBBLING_PHASE          // 冒泡阶段
    };
    
    /**
     *  @param type     事件类型
     *  @param bubbles  是否冒泡
     */
    Event(std::string type, bool bubbles = false);
    virtual ~Event();
    /**
     *  复制
     *  @param event
     */
    virtual void copyFrom(Event *event);
    /**
     *  停止对事件流中当前节点中和所有后续节点中的事件侦听器进行处理。
     */
    virtual void    stopImmediatePropagation();
    /**
     *  停止对事件流中当前节点的后续节点中的所有事件侦听器进行处理。
     */
    virtual void    stopPropagation();
    /**
     *  是否为冒泡事件
     *  @return
     */
    virtual bool    isBubbles() const;
    /**
     *  是否立即停止事件
     *  @return
     */
    virtual bool    isImmediatePropagation() const;
    /**
     *  当次事件完成之后，停止后续冒泡
     *  @return
     */
    virtual bool    isPropagation() const;
    /**
     *  当前事件派发对象
     *  @return
     */
    virtual EventDispatcher*    getCurrentTarget() const;
    /**
     *  目标派发对象
     *  @return
     */
    virtual EventDispatcher*    getTarget() const;
    /**
     *  设置当前派发对象
     *  @param target
     */
    virtual void                setCurrentTarget(EventDispatcher *target);
    /**
     *  设置目标
     *  @param target
     */
    virtual void                setTarget(EventDispatcher *target);
    /**
     *  设置事件阶段
     *  @param phase
     */
    virtual void                setEventPhase(EventPhase phase);
    /**
     *  事件阶段
     *  @return
     */
    virtual EventPhase          getEventPhase() const;
    /**
     *  重置event
     */
    virtual void reset();
    
    /**
     *  事件类型
     */
    std::string type;
    
protected:
    
    bool    _bubbles;
    bool    _stopPropagation;
    bool    _stopImmediatePropagation;
    
    EventDispatcher*    _currentTarget;
    EventDispatcher*    _target;
    EventPhase          _eventPhase;
};

NS_MONKEY_END

#endif
