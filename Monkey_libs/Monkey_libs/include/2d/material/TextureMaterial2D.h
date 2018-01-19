//
//  QuadMaterial2D.h
//  Opengl2D
//
//  Created by Neil on 7/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Opengl2D_QuadMaterial2D_h
#define Opengl2D_QuadMaterial2D_h

#include "core/material/Material3D.h"

NS_MONKEY_BEGIN

class Texture2D;

/**
 *  TextureMaterial2D
 *  使用单例模式
 */
class TextureMaterial2D : public Material3D {
    
public:
    /**
     *  销毁单例program
     */
    static void dispose();
    /**
     *  获取单例shader
     *  @return
     */
    static TextureMaterial2D* getInstance();
    /**
     *  绘制
     *  @param geometry 网格数据
     *  @param texture  贴图
     *  @param mvp      mvp矩阵
     *  @param alpha    透明度
     */
    virtual void draw(Geometry3D *geometry, Texture2D *texture, Matrix3D &mvp, float alpha = 1.0f);
    
private:
    
    TextureMaterial2D();
    virtual ~TextureMaterial2D();
    
    GLuint           _posVaInstance;
    GLuint           _uvVaInstance;
    GLint            _textureUnifrom;
    GLint            _mvpUniform;
    GLint            _alphaUniform;
    
    static TextureMaterial2D* _instance;
};

NS_MONKEY_END

#endif
