//
//  Matrix3DUtils.h
//  Monkey
//
//  Created by Neil on 25/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __Matrix3DUtils__
#define __Matrix3DUtils__

#include "Vector3D.h"
#include "Matrix3D.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class Matrix3DUtils {

public:
    /**
     *  获取右方方向向量
     *  @param m
     *  @param out
     */
    static void getRight(const Matrix3D &m, Vector3D &out);
    /**
     *  获取上方方向向量
     *  @param m
     *  @param out
     */
    static void getUp(const Matrix3D &m, Vector3D &out);
    /**
     *  获取前方方向向量
     *  @param m
     *  @param out
     */
    static void getDir(const Matrix3D &m, Vector3D &out);
    /**
     *  获取左方方向向量
     *  @param m
     *  @param out
     */
    static void getLeft(const Matrix3D &m, Vector3D &out);
    /**
     *  获取后方方向向量
     *  @param m
     *  @param out
     */
    static void getBackward(const Matrix3D &m, Vector3D &out);
    /**
     *  获取下方方向向量
     *  @param m
     *  @param out
     */
    static void getDown(const Matrix3D &m, Vector3D &out);
    /**
     *  获取位移
     *  @param m
     *  @param out
     */
    static void getPosition(const Matrix3D &m, Vector3D &out);
    /**
     *  获取缩放
     *  @param m
     *  @param out
     */
    static void getScale(const Matrix3D &m, Vector3D &out);
    /**
     *  设置位移
     *  @param m
     *  @param x
     *  @param y
     *  @param z
     *  @param .0f
     */
    static void setPosition(Matrix3D &m, const float x, const float y, const float z, const float smooth = 1.0f);
    /**
     *  设置朝向
     *
     *  @param m
     *  @param dir
     *  @param up
     *  @param smooth
     */
    static void setOrientation(Matrix3D &m, const Vector3D &dir, const Vector3D &up, const float smooth = 1.0f);
    /**
     *  设置矩阵
     *  @param m
     *  @param right
     *  @param up
     *  @param dir
     */
    static void setVectors(Matrix3D &m, const Vector3D &right, const Vector3D &up, const Vector3D &dir);
    /**
     *  look at
     *  @param m
     *  @param x
     *  @param y
     *  @param z
     *  @param up
     *  @param smooth
     */
    static void lookAt(Matrix3D &m, const float x, const float y, const float z, const Vector3D &up, const float smooth = 1.0f);
    /**
     *  设置位移
     *  @param m
     *  @param x
     *  @param y
     *  @param z
     */
    static void setTranslation(Matrix3D &m, const float x, const float y, const float z);
    /**
     *  沿着模型x轴位移
     *  @param m
     *  @param distance
     */
    static void translateX(Matrix3D &m, const float distance);
    /**
     *  沿着模型y轴位移
     *  @param m
     *  @param distance
     */
    static void translateY(Matrix3D &m, const float distance);
    /**
     *  沿着模型z轴位移
     *  @param m
     *  @param distance
     */
    static void translateZ(Matrix3D &m, const float distance);
    /**
     *  沿着轴位移
     *  @param m
     *  @param distance
     *  @param axis
     */
    static void translateAxis(Matrix3D &m, const float distance, const Vector3D &axis);
    /**
     *  设置缩放
     *  @param m
     *  @param x
     *  @param y
     *  @param z
     *  @param smooth
     */
    static void setScale(Matrix3D &m, float x, float y, float z, const float smooth = 1.0f);
    /**
     *  设置x轴缩放
     *  @param m
     *  @param scale
     */
    static void scaleX(Matrix3D &m, float scale);
    /**
     *  设置y轴缩放
     *  @param m
     *  @param scale
     */
    static void scaleY(Matrix3D &m, float scale);
    /**
     *  设置z轴缩放
     *  @param m
     *  @param scale
     */
    static void scaleZ(Matrix3D &m, float scale);
    /**
     *  获取旋转值
     *  @param m
     *  @param out
     */
    static void getRotation(const Matrix3D &m, Vector3D &out);
    /**
     *  设置旋转(角度值)
     *  @param m
     *  @param x
     *  @param y
     *  @param z
     */
    static void setRotation(Matrix3D &m, const float x, const float y, const float z);
    /**
     *  绕轴Axis旋转
     *  @param m
     *  @param angle
     *  @param axis
     *  @param pivot
     */
    static void rotateAxis(Matrix3D &m, const float angle, const Vector3D &axis, Vector3D *pivot = nullptr);
    /**
     *  绕模型x轴旋转
     *  @param m
     *  @param angle
     *  @param local
     *  @param pivot
     */
    static void rotateX(Matrix3D &m, const float angle, bool local = true, Vector3D *pivot = nullptr);
    /**
     *  绕模型y轴旋转
     *  @param m
     *  @param angle
     *  @param local
     *  @param pivot
     */
    static void rotateY(Matrix3D &m, const float angle, bool local = true, Vector3D *pivot = nullptr);
    /**
     *  绕模型z轴旋转
     *  @param m
     *  @param angle
     *  @param local
     *  @param pivot
     */
    static void rotateZ(Matrix3D &m, const float angle, bool local = true, Vector3D *pivot = nullptr);
    /**
     *  转换到模型空间
     *  @param m
     *  @param in
     *  @param out
     */
    static void transformVector(const Matrix3D &m, const Vector3D &in, Vector3D &out);
    /**
     *  转换到模型空间，忽略位移信息
     *  @param m
     *  @param in
     *  @param out
     */
    static void deltaTransformVector(const Matrix3D &m, const Vector3D &in, Vector3D &out);
    /**
     *  逆矩阵
     *  @param m
     *  @param out
     */
    static void invert(const Matrix3D &m, Matrix3D &out);
    /**
     *  绝对值。。。辅助计算
     *  @param f
     *  @return
     */
    static float absf(float f);
    /**
     *  相等
     *  @param a
     *  @param b
     *  @return
     */
    static bool equal(const Matrix3D &a, const Matrix3D &b);
    /**
     *  建立正交矩阵
     *  @param left
     *  @param right
     *  @param top
     *  @param bottom
     *  @param near
     *  @param far
     *  @param out
     */
    static void buildOrthoProjection(float left, float right, float top, float bottom, float near, float far, Matrix3D &out);
    
private:
    static float RAW_DATA_CONTAINER[16];
    static float _raw[16];
    static float _toRad;
    static float _toAng;
    static Vector3D _vector;
    static Vector3D _right;
    static Vector3D _up;
    static Vector3D _dir;
    static Vector3D _scale;
    static Vector3D _pos;
    static float _x;
    static float _y;
    static float _z;
};

NS_MONKEY_END

#endif 
