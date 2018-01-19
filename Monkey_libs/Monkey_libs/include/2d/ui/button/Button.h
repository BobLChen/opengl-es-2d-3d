//
//  Button.h
//  Monkey
//
//  Created by Neil on 26/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _Button_h
#define _Button_h

#include "2d/ui/Widget.h"

NS_MONKEY_BEGIN

class Button : public Widget {
    
public:
    
    enum ButtonStats {
        UP,
        OVER,
        DOWN
    };
    
    Button();
    virtual ~Button();
    
protected:
    /**
     *  设置按钮状态
     *  @param stats
     */
    virtual void setButtonStatus(ButtonStats stats);
    /**
     *  Touch Began事件
     *  @param e
     */
    void onTouchBegan(Event* e);
    /**
     *  Touch End事件
     *  @param e
     */
    void onTouchEnd(Event* e);
    /**
     *  Touch Move事件
     *  @param e
     */
    void onTouchMove(Event* e);
    /**
     *  Touch Out事件
     *  @param e
     */
    void onTouchOut(Event* e);
    
    ButtonStats _buttonStats;
};

NS_MONKEY_END

#endif
