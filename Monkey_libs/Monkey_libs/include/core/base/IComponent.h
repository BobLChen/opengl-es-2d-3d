//
//  Component.h
//  Monkey_libs
//
//  Created by Neil on 2/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_Component_h
#define Monkey_libs_Component_h

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class Pivot3D;

class IComponent {
    
public:
    
    virtual ~IComponent() {
        
    }
    
    /**
     *  组件被添加
     *  @param pivot
     *  @return
     */
    virtual bool added(Pivot3D *pivot) = 0;
    /**
     *  组件被移除
     *  @return
     */
    virtual bool removed() = 0;
    /**
     *  克隆组件
     *  @return
     */
    virtual IComponent* clone();
    /**
     *  销毁组件
     */
    virtual void dispose();
};

NS_MONKEY_END

#endif
