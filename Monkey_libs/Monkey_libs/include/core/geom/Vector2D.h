//
//  Point.h
//  Monkey
//
//  Created by Neil on 3/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __Vector2D__
#define __Vector2D__

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class Vector2D {
    
public:
    
    float x;
    float y;
    
    Vector2D();
    Vector2D(float x, float y);
    Vector2D(const Vector2D &p);
    Vector2D(Vector2D *p);
    
    ~Vector2D();
    /**
     *  设置
     *
     *  @param x x
     *  @param y y
     */
    void setTo(float x, float y);
    /**
     *  复制
     *  @param v
     */
    void copyFrom(const Vector2D &v);
    /**
     *  规格化
     */
    void normalize();
    /**
     *  缩放
     *  @param value
     */
    void scaleBy(float value);
};

typedef Vector2D Point2D;

NS_MONKEY_END

#endif
