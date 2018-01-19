//
//  OrthographicLens.h
//  Monkey_libs
//
//  Created by Neil on 3/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_OrthographicLens_h
#define Monkey_libs_OrthographicLens_h

#include "core/camera/lens/LensBase.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class OrthographicLens : public LensBase {
    
public:
    
    OrthographicLens();
    virtual ~OrthographicLens();
    
    /**
     *  设置视口
     *  @param x      x
     *  @param y      y
     *  @param width  宽度
     *  @param height 高度
     */
    virtual void setViewport(float x, float y, float width, float height) override;
    /**
     *  设置near
     *  @param value
     */
    virtual void setNear(float value);
    /**
     *  设置far
     *  @param value
     */
    virtual void setFar(float value);
    /**
     *  get near
     *  @return
     */
    virtual float getNear() const;
    /**
     *  get far
     *  @return
     */
    virtual float getFar() const;
    /**
     *  设置left
     *  @param value
     */
    virtual void setLeft(float value);
    /**
     *  get left
     *  @return
     */
    virtual float getLeft() const;
    /**
     *  设置right
     *  @param value
     */
    virtual void setRight(float value);
    /**
     *  get right
     *  @return
     */
    virtual float getRight() const;
    /**
     *  set top
     *  @param value
     */
    virtual void setTop(float value);
    /**
     *  get top
     *  @return
     */
    virtual float getTop() const;
    /**
     *  set bottom
     *  @param value
     */
    virtual void setBottom(float value);
    /**
     *  get bottom
     *  @return
     */
    virtual float getBottom() const;
    /**
     *  初始化
     *
     *  @param left   left
     *  @param right  right
     *  @param bottom bootom
     *  @param top    top
     *  @param near   near
     *  @param far    far
     */
    virtual void init(float left, float right, float bottom, float top, float near, float far);
    
    /**
     *  更新projection矩阵
     */
    virtual void updateProjectionMatrix() override;
    
protected:
    
    float _left;
    float _right;
    float _top;
    float _bottom;
    float _near;
    float _far;
    
};


NS_MONKEY_END

#endif
