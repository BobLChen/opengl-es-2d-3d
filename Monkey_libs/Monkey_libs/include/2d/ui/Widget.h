//
//  Widget.h
//  Monkey_libs
//
//  Created by Neil on 2/11/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_Widget_h
#define Monkey_libs_Widget_h

#include "2d/entities/DisplayObject.h"
#include <map>

NS_MONKEY_BEGIN

class Widget : public DisplayObject {
    
public:
    
    enum class Type {
        TEXTURE,
        TEXTURE_FRAME
    };
    
    Widget();
    
    virtual ~Widget();
    
    /**
     *  获取控件列表
     *  @return
     */
    virtual std::vector<DisplayObject*> &getWidgets();
    
protected:
    
    /**
     *  更新transform
     *  @param includeChildren
     */
    virtual void updateTransforms(bool includeChildren = true) override;
    /**
     *  添加一个控件
     *  @param widget   控件
     */
    virtual void addWidget(DisplayObject *widget);
    /**
     *  添加一个控件
     *
     *  @param widget 控件
     *  @param index  索引
     */
    virtual void addWidgetAt(DisplayObject *widget, int index);
    /**
     *  移除一个控件
     *  @param widget 控件
     */
    virtual void removeWidget(DisplayObject *widget);
    /**
     *  移除一个控件
     *  @param index 控件
     */
    virtual void removeWidgetAt(int index);
    /**
     *  绘制阶段
     *  @param includeChildren
     */
    virtual void draw(bool includeChildren = false, Material3D* shader = nullptr) override;
    // 组件
    std::vector<DisplayObject*>    _widgetList;
};

NS_MONKEY_END

#endif
