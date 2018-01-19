//
//  PerspectiveLens.h
//  Monkey_libs
//
//  Created by Neil on 3/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_PerspectiveLens_h
#define Monkey_libs_PerspectiveLens_h

#include "core/camera/lens/LensBase.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class PerspectiveLens : public LensBase {
    
public:
    
    PerspectiveLens();
    virtual ~PerspectiveLens();
    
    /**
     *  更新projection矩阵
     */
    virtual void updateProjectionMatrix() override;
    /**
     *  判断点是否在镜头内
     *  @param point     点
     *  @param radius    半径
     *  @param viewSpace viewSpace
     *  @return
     */
    virtual bool isInView(const Vector3D& point, float radius, bool viewSpace = true) override;
    /**
     *  获取屏幕拾取点射线
     *
     *  @param x     x坐标
     *  @param y     y坐标
     *  @param world 相机矩阵
     *  @param dest  dest
     */
    virtual void getPointDir(float x, float y, const Matrix3D& world, Vector3D &dest) override;
    /**
     *  get far
     *  @return
     */
    virtual float getFar() const;
    /**
     *  set far
     *  @param value
     *  @return
     */
    virtual void setFar(float value);
    /**
     *  get near
     *  @return
     */
    virtual float getNear() const;
    /**
     *  set neat
     *  @param value
     */
    virtual void setNear(float value);
    /**
     *  get zoom
     *  @return
     */
    virtual float getZoom();
    /**
     *  set zoom
     *  @param value
     */
    virtual void setZoom(float value);
    /**
     *  get fieldOfView
     *  @return
     */
    virtual float getFieldOfView() const;
    /**
     *  set fieldOfView
     *  @param value
     */
    virtual void setFieldOfView(float value);
    
protected:
    
    float _near;
    float _far;
    float _zoom;
    float _fieldOfView;
    float _aspectRatio;
};

NS_MONKEY_END

#endif
