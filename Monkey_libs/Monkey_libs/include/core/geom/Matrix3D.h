//
//  Matrix3D.h
//  Monkey
//
//  Created by Neil on 25/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _Matrix3D_h
#define _Matrix3D_h

#include "Vector3D.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

// 主行矩阵
// 谁说的opengl一定非要用主列矩阵
class Matrix3D {
    
public:
    /**
     * 角度解包方式，欧拉角、四元数等。
     */
    enum Style {
        EulerAngles,
        AxisAngle,
        Quaternion
    };
    /**
     *  矩阵数据
     */
    float rawData[16];
    
    Matrix3D();
    Matrix3D(const float *v);
    
    ~Matrix3D() {
        
    }
    /**
     *  append，右乘矩阵
     *  @param lhs 矩阵
     */
    void append(const Matrix3D &lhs);
    /**
     *  复制一列
     *  @param column 列号
     *  @param vec    数据
     */
    void copyColumnFrom(const int column, const Vector3D &vec);
    /**
     *  获取一列数据
     *  @param column 列号
     *  @param vec    输出组件
     */
    void copyColumnTo(const int column, Vector3D &vec) const;
    /**
     *  复制
     *  @param mt
     */
    void copyFrom(const Matrix3D &mt);
    /**
     *  复制
     *  @param v
     */
    void copyRawDataFrom(const float *v);
    /**
     *  获取矩阵数据
     *  @param v
     */
    void copyRawDataTo(float *v) const;
    /**
     *  复制一行
     *
     *  @param raw 行号
     *  @param vec 数据源
     */
    void copyRawFrom(int raw, const Vector3D &vec);
    /**
     *  获取一行数据
     *
     *  @param raw 行号
     *  @param vec 目标
     */
    void copyRawTo(int raw, Vector3D &vec) const;
    /**
     *  获取矩阵数据
     *  @param dest
     */
    void copyToMatrix3D(Matrix3D &dest) const;
    /**
     *  解包矩阵
     *  @param style 方式
     *  @return
     */
    void decompose(Style style, Vector3D *out) const;
    /**
     *  将向量v转换到矩阵空间，最好使用Matrix3DUtils.deltaTransformVector
     *  @param v    向量
     *  @return
     */
    Vector3D deltaTransformVector(const Vector3D v) {
        float x = v.x;
        float y = v.y;
        float z = v.z;
        
        return Vector3D(
                        (x * rawData[0] + y * rawData[4] + z * rawData[8]),
                        (x * rawData[1] + y * rawData[5] + z * rawData[9]),
                        (x * rawData[2] + y * rawData[6] + z * rawData[10]),
                        (x * rawData[3] + y * rawData[7] + z * rawData[11])
                        );
    }
    /**
     *  标准化
     */
    void identity();
    /**
     *  插值
     *  @param dest    目标矩阵
     *  @param percent 百分比
     */
    void interpolateTo(Matrix3D &dest, float percent);
    /**
     *  可逆
     *  @return
     */
    float determinant();
    /**
     *  求逆矩阵
     */
    void invert();
    /**
     *  左乘
     *  @param rhs
     */
    void prepend(const Matrix3D &rhs);
    /**
     *  获取Axis(x,y,z)轴矩阵
     *
     *  @param x       轴x
     *  @param y       轴y
     *  @param z       轴z
     *  @param a       锚点x
     *  @param b       锚点y
     *  @param c       锚点z
     *  @param degress 角度值
     *  @param dst     目标矩阵
     */
    static void getAxisRotation(float x, float y, float z, const float a, const float b, const float c, const float degress, Matrix3D &dst);
    /**
     *  预乘旋转
     *  @param degrees 角度值
     *  @param axis    轴
     *  @param pivot   锚点
     */
    void prependRotation(const float degrees, const Vector3D &axis, Vector3D *pivot = nullptr);
    /**
     *  预乘缩放
     *  @param x
     *  @param y
     *  @param z
     */
    void prependScale(const float x, const float y, const float z);
    /**
     *  设置位移
     *  @param x
     *  @param y
     *  @param z
     */
    void setPosition(const float x, const float y, const float z);
    /**
     *  追加缩放值
     *  @param x
     *  @param y
     *  @param z
     */
    void appendScale(const float x, const float y, const float z);
    /**
     *  追加旋转
     *
     *  @param degrees 角度
     *  @param axis    轴
     *  @param pivot   锚点
     */
    void appendRotation(const float degrees, const Vector3D &axis, Vector3D *pivot = nullptr);
    /**
     *  追加位移
     *  @param x
     *  @param y
     *  @param z
     */
    void appendTranslation(const float x, const float y, const float z);
    /**
     *  设置位移
     *  @param position
     */
    void setPosition(const Vector3D &position);
    /**
     *  预设位移
     *  @param x
     *  @param y
     *  @param z
     */
    void prependTranslation(const float x, const float y, const float z);
    /**
     *  解包矩阵
     *  @param components
     */
    void recompose(const Vector3D *components);
    /**
     *  转换到模型空间
     *  @param in
     *  @param out
     */
    void transformVector(const Vector3D &in, Vector3D &out);
    /**
     *  转换到模型空间
     *  @param vin
     *  @param vout
     */
    void transformVectors(const float *vin, float *vout);
    /**
     *  倒置矩阵
     */
    void transpose();
    
private:
    /**
     *  临时变量
     */
    static Matrix3D _mt;
    
};

NS_MONKEY_END

#endif
