//
//  Camera3D.h
//  Monkey_libs
//
//  Created by Neil on 3/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_Camera3D_h
#define Monkey_libs_Camera3D_h

#include "platform/PlatformMacros.h"
#include "core/base/Pivot3D.h"
#include "core/camera/lens/LensBase.h"

NS_MONKEY_BEGIN

class Camera3D : public Pivot3D {
    
public:
    
    const static std::string LENS_CHANGE_EVENT;
    
    static Event _lensChangeEvent;
    
    Camera3D(LensBase *lens = nullptr);
    virtual ~Camera3D();
    
    /**
     *  设置镜头
     *  @param lens
     */
    virtual void setLens(LensBase *lens);
    /**
     *  获取镜头
     *  @return
     */
    virtual LensBase* getLens() const;
    /**
     *  判断点是否在相机内
     *  @param point     点
     *  @param radius    半径
     *  @param viewSpace
     *  @return
     */
    virtual bool isInView(const Vector3D& point, float radius, bool viewSpace = true);
    /**
     *  获取拾取点的方向
     *  @param x    x
     *  @param y    y
     *  @param dest
     */
    virtual void getPointDir(float x, float y, Vector3D& dest);
    /**
     *  设置viewport
     *  @param x      x
     *  @param y      y
     *  @param width  宽度
     *  @param height 高度
     */
    virtual void setViewport(float x, float y, float width, float height);
    /**
     *  获取Projection
     *  @return
     */
    virtual Matrix3D& getProjection();
    /**
     *  view
     *  @return
     */
    virtual Matrix3D& getView();
    /**
     *  view projection
     *  @return
     */
    virtual Matrix3D& getViewProjection();
    
protected:
    
    LensBase* _lens;
    Matrix3D  _viewProjection;
};

NS_MONKEY_END


#endif
