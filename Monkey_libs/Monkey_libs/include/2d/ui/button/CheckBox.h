//
//  CheckBox.h
//  Monkey_libs
//
//  Created by Neil on 24/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_CheckBox_h
#define Monkey_libs_CheckBox_h

#include "2d/ui/Widget.h"
#include "2d/entities/Image.h"

NS_MONKEY_BEGIN

class CheckBox : public Widget {
    
public:
    
    CheckBox();
    
    virtual ~CheckBox();
    /**
     *  设置checkbox状态
     *
     *  @param value    true or false
     */
    virtual void setValue(bool value);
    /**
     *  初始化
     *
     *  @param disable          取消
     *  @param disableSelected  取消被按下
     *  @param active           启用
     *  @param activeSeltected  启用被按下
     *  @param type             图片类型。
     */
    virtual void initwithImage(const std::string &disable, const std::string &disableSelected, const std::string &active, const std::string &activeSeltected, Type type = Type::TEXTURE);
    
protected:
    
    void initRenderer();
    /**
     *  press
     *  @param e
     */
    void onTouchBegin(Event *e);
    /**
     *  press up
     *  @param e
     */
    void onTouchEnd(Event *e);
    /**
     *  初始化未选中状态
     *  @param name     texture名称
     *  @param type     texture类型
     */
    void initDisableRenderer(const std::string &name, Type type);
    /**
     *  初始化 按下 未选中状态
     *  @param name texture名称
     *  @param type texture类型
     */
    void initDisableSeltectedRenderer(const std::string &name, Type type);
    /**
     *  初始化激活状态
     *  @param name texture名称
     *  @param type texture类型
     */
    void initActiveRenderer(const std::string &name, Type type);
    /**
     *  初始化 按下 激活状态
     *  @param name texture名称
     *  @param type texture类型
     */
    void initActiveSeltectedRenderer(const std::string &name, Type type);
    
    void hideAll();
    
    void onPressActive();
    
    void onPressDisable();
    
    void onActive();
    
    void onDisable();
    
    Image* _disableRenderer;
    Image* _disableSelectedRenderer;
    Image* _activeRenderer;
    Image* _activeSeltectedRenderer;
    
    Event _activeEvent;
    Event _disableEvent;
    
    bool   _active;
    
};

NS_MONKEY_END

#endif
