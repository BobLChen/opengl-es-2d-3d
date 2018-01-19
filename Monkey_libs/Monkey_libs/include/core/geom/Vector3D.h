//
//  Vector3D.h
//  Monkey
//
//  Created by Neil on 25/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __Vector3D__
#define __Vector3D__

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class Vector3D {
    
public:
    
    float x;
    float y;
    float z;
    float w;
    /**
     *  x轴
     */
    static const Vector3D X_AXIS;
    /**
     *  y轴
     */
    static const Vector3D Y_AXIS;
    /**
     *  z轴
     */
    static const Vector3D Z_AXIS;
    /**
     *  0
     */
    static const Vector3D ZERO;
    
    Vector3D(const Vector3D &v);
    ~Vector3D();
    
    Vector3D(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 0.0f);
    /**
     *  设置vector3D
     *  @param x
     *  @param y
     *  @param z
     *  @param w
     */
    void setTo(const float x, const float y, const float z, const float w);
    /**
     *  设置vector3d, w 默认为1
     *  @param x
     *  @param y
     *  @param z
     */
    void setTo(const float x, const float y, const float z);
    /**
     *  等于
     *  @param v
     *  @return
     */
    bool operator == (const Vector3D &v);
    /**
     *  不等于
     *  @param v
     *  @return
     */
    bool operator != (const Vector3D &v);
    /**
     *  赋值
     *  @param v
     *  @return
     */
    Vector3D& operator = (const Vector3D &v);
    /**
     *  add
     *  @param v
     *  @return
     */
    Vector3D& operator += (const Vector3D &v);
    /**
     *  sub
     *  @param v
     *  @return
     */
    Vector3D& operator -= (const Vector3D &v);
    /**
     *  scale
     *  @param f
     *  @return
     */
    Vector3D& operator *= (const float f);
    /**
     *  scale
     *  @param f
     *  @return
     */
    Vector3D& operator /= (const float f);
    /**
     *  copy from
     *  @param v
     */
    void copyFrom(const Vector3D &v);
    /**
     *  长度
     *  @return
     */
    float length();
    /**
     *  未开方长度
     *  @return
     */
    float lengthSquared();
    /**
     *  点乘
     *  @param v
     *  @return
     */
    float dot(const Vector3D &v);
    /**
     *  点积
     *  @param v
     *  @return
     */
    Vector3D& crossProduct(const Vector3D &v);
    /**
     *  点积
     *  @param v1
     *  @param v2
     *  @param dst
     */
    static void crossProduct(const Vector3D &v1, const Vector3D &v2, Vector3D *dst);
    /**
     *  add
     *  @param v
     *  @return
     */
    Vector3D& add(const Vector3D &v);
    /**
     *  add
     *  @param v1
     *  @param v2
     *  @param dst
     */
    static void add(const Vector3D &v1, const Vector3D &v2, Vector3D *dst);
    /**
     *  sub
     *  @param v1
     *  @param v2
     *  @param dst
     */
    static void subtract(const Vector3D &v1, const Vector3D &v2, Vector3D *dst);
    /**
     *  sub
     *  @param v
     *  @return
     */
    Vector3D& subtract(const Vector3D &v);
    /**
     *  取逆
     */
    void negate();
    /**
     *  标准化，模为1
     */
    void normalize();
    /**
     *  scale
     *  @param f
     */
    void scaleBy(const float f);
    
};

NS_MONKEY_END

#endif
