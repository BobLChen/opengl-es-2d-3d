//
//  Material3D.h
//  Monkey
//
//  Created by Neil on 31/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __Material3D__
#define __Material3D__

#include "core/base/GLBase.h"
#include "platform/PlatformMacros.h"

#include <string>

NS_MONKEY_BEGIN

class Geometry3D;
class Matrix3D;
class GLSLProgram;

/**
 *  shader
 */
class Material3D {
    
public:
    
    Material3D();
    /**
     *  @param vertPath 顶点程序路径
     *  @param fragPath 片段程序路径
     */
    Material3D(const std::string &vertPath, const std::string &fragPath);
    
    virtual ~Material3D();
    /**
     *  绘制模型
     *  @param geometry 模型数据
     */
    virtual void draw(Geometry3D *geometry);
    /**
     *  获取program
     *  @return
     */
    virtual GLSLProgram* getProgram();
    
protected:
    GLSLProgram *program;
};

NS_MONKEY_END

#endif
