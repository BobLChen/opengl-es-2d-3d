//
//  Rectangle.h
//  Monkey
//
//  Created by Neil on 27/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __Rectangle__
#define __Rectangle__

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class Vector2D;

class Rectangle {
    
public:
    
    Rectangle();
    Rectangle(float x, float y, float width, float height);
    
    ~Rectangle();
    /**
     *  x坐标
     *
     *  @return
     */
    float   getX() const;
    /**
     *  y坐标
     *
     *  @return
     */
    float   getY() const;
    /**
     *  高度
     *
     *  @return
     */
    float   getHeight() const;
    /**
     *  宽度
     *  @return
     */
    float   getWidth() const;
    /**
     *  top
     *  @return
     */
    float   getTop() const;
    /**
     *  left
     *  @return
     */
    float   getLeft() const;
    /**
     *  right
     *  @return
     */
    float   getRight() const;
    /**
     *  bottom
     *  @return
     */
    float   getBottom() const;
    /**
     *  中心点x
     *  @return
     */
    float   getCenterX() const;
    /**
     *  中心点y
     *  @return
     */
    float   getCenterY() const;
    /**
     *  是否包含有点
     *  @param x 点x坐标
     *  @param y 点y坐标
     *  @return
     */
    bool    contains(float x, float y) const;
    /**
     *  是否包含点
     *  @param point 点
     *  @return
     */
    bool    containsPoint(const Vector2D &point) const;
    /**
     *  是否包含一个rect
     *  @param rect
     *  @return
     */
    bool    containsRect(const Rectangle &rect) const;
    /**
     *  相等
     *  @param rect
     *  @return
     */
    bool    equals(const Rectangle &rect) const;
    /**
     *  是否相交
     *  @param rect
     *  @return
     */
    bool    intersects(const Rectangle &rect) const;
    /**
     *  复制
     *  @param rect
     */
    void    copyFrom(const Rectangle &rect);
    /**
     *  设置
     *  @param x     
     *  @param y
     *  @param width
     *  @param height
     */
    void    set(const float x, const float y, const float width, const float height);
    
private:
    float _bottom;
    float _top;
    float _left;
    float _right;
    float _centerX;
    float _centerY;
    float _x;
    float _y;
    float _width;
    float _height;
};

NS_MONKEY_END

#endif
