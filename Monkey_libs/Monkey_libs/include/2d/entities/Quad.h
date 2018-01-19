//
//  Quad.h
//  Monkey
//
//  Created by Neil on 8/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _Quad_h
#define _Quad_h

#include "platform/PlatformMacros.h"
#include "2d/entities/DisplayObject.h"

NS_MONKEY_BEGIN

class Quad : public DisplayObject {
    
public:
    
    /**
     *  cretae quad
     *  自行释放
     *  @param width  宽度
     *  @param height 高度
     *  @param color  颜色
     *  @param alpha  透明度
     *  @return quad
     */
    static Quad* create(float width, float height, int color, float alpha = 1.0f);
    
    Quad(float width, float height, int color, float alpha = 1.0f);
    ~Quad();
    
    /**
     *  @param includeChildren
     */
    virtual void draw(bool includeChildren, Material3D* shader = nullptr) override;
    /**
     *  设置锚点
     *  @param x
     *  @param y
     */
    virtual void setAnchor(float x, float y) override;
    
private:
    float _red;
    float _green;
    float _blue;
};

NS_MONKEY_END

#endif
