//
//  LensBase.h
//  Monkey_libs
//
//  Created by Neil on 3/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_LensBase_h
#define Monkey_libs_LensBase_h

#include "platform/PlatformMacros.h"
#include "core/event/EventDispatcher.h"
#include "core/geom/Matrix3D.h"
#include "core/geom/Rectangle.h"

NS_MONKEY_BEGIN

class LensBase : public EventDispatcher {
    
public:
    
    /**
     *  projection更新事件
     */
    const static std::string PROJECTION_UPDATE_EVNET;
    
    LensBase();
    
    virtual ~LensBase();
    
    /**
     *  获取Projection
     *  @return
     */
    virtual Matrix3D& getProjection();
    /**
     *  更新projection矩阵
     */
    virtual void updateProjectionMatrix();
    /**
     *  判断点是否在镜头内
     *  @param point     点
     *  @param radius    半径
     *  @param viewSpace viewSpace
     *  @return
     */
    virtual bool isInView(const Vector3D& point, float radius, bool viewSpace = true);
    /**
     *  获取屏幕拾取点射线
     *
     *  @param x     x坐标
     *  @param y     y坐标
     *  @param world 相机矩阵
     *  @param dest  dest
     */
    virtual void getPointDir(float x, float y, const Matrix3D& world, Vector3D &dest);
    /**
     *  设置视口
     *  @param x      x
     *  @param y      y
     *  @param width  宽度
     *  @param height 高度
     */
    virtual void setViewport(float x, float y, float width, float height);
    /**
     *  invalid projection
     */
    virtual void invalidProjection();
    
protected:
    
    static Event _projectionUpdateEvent;
    
    bool  _dirty;
    
    Matrix3D    _projection;
    Rectangle   _viewport;
};


NS_MONKEY_END

#endif
