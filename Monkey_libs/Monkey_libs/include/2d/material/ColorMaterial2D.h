//
//  ColorMaterial2D.h
//  Monkey
//
//  Created by Neil on 8/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _ColorMaterial2D_h
#define _ColorMaterial2D_h

#include "core/material/Material3D.h"

NS_MONKEY_BEGIN

/**
 *  使用单例模式。只支持纯色。
 */
class ColorMaterial2D : public Material3D {
    
public:
    /**
     *  设置颜色
     *  @param red   红
     *  @param green 绿
     *  @param blue  蓝
     *  @param alpha alpha
     */
    virtual void setColor(float red, float green, float blue, float alpha);
    /**
     *  绘制
     *  @param geometry 网格数据
     *  @param mvp      mvp矩阵
     */
    virtual void draw(Geometry3D *geometry, Matrix3D &mvp);
    /**
     *  获取colorMaterial2D实例
     *  @return
     */
    static ColorMaterial2D* getInstance();
    /**
     *  销毁单例
     */
    static void dispose();
private:
    
    ColorMaterial2D();
    virtual ~ColorMaterial2D();
    
    GLuint _posVa;
    GLuint _colorAlphaUniform;
    GLint  _mvpUniform;
    
    float  _alpha;
    float  _red;
    float  _green;
    float  _blue;
    
    static ColorMaterial2D* _instance;
};

NS_MONKEY_END

#endif
