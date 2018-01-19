//
//  Geometry3D.h
//  Monkey
//
//  Created by Neil on 30/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __Geometry3D__
#define __Geometry3D__

#include "core/base/GLBase.h"
#include "platform/PlatformMacros.h"

#include <string>

NS_MONKEY_BEGIN

// 网格数据
class Geometry3D {
    
public:
    
    /**
     *  顶点数据格式
     */
    enum VertexType {
        POSITION = 0,           // 顶点
        NORMAL,                 // 法线
        UV0,                    // uv0
        UV1,                    // uv1
        UV2,                    // uv2
        UV3,                    // uv3
        TANGENT,                // 正切->bumpmap
        BITANGENT,              // 余切->bumpmap
        SKIN_WEIGHTS,           // 骨骼权重数据
        SKIN_INDICES,           // 骨骼索引数据
        CUSTOM1,                // 自定义0
        CUSTOM2,                // 自定义1
        CUSTOM3,                // 自定义2
        CUSTOM4,                // 自定义3
        CUSTOM5,                // 自定义4
        CUSTOM6                 // 自定义5
    };
    
    Geometry3D();
    virtual ~Geometry3D();
    
    /**
     *  添加顶点数据流，默认不支持混合顶点数据。
     *
     *  @param type       顶点类型
     *  @param data       顶点数据
     *  @param size       顶点数据大小
     *  @param formatSize gpu数据断大小
     */
    virtual void addVertexBuffer(Geometry3D::VertexType type, const char *data, const ssize_t size, const int formatSize);
    /**
     *  获取顶点数据
     *  @param type 顶点类型
     *  @return
     */
    virtual const char* getVertexBuffer(Geometry3D::VertexType type);
    /**
     *  移除buffer
     *  @param type 顶点类型
     */
    virtual void removeVertexBuffer(Geometry3D::VertexType type);
    /**
     *  启用顶点
     *  @param type     数据类型
     *  @param index    shader位置
     */
    virtual void enableVertexBuffer(Geometry3D::VertexType type, const GLuint &index);
    /**
     *  关闭顶点
     *  @param type
     *  @param index
     */
    virtual void disableVertexBuffer(Geometry3D::VertexType type, const GLuint &index);
    /**
     *  设置索引(索引数据只能为GLuint)
     *
     *  @param data         顶点数据
     *  @param size         数据大小
     *  @param triangleNum  顶点数量(顶点数量/3=三角形数量)
     */
    virtual void setIndexBuffer(const char *data, const ssize_t size, const int triangleNum);
    /**
     *  获取所以buffer标识
     *  @return
     */
    virtual GLuint& getIndexBuffer();
    /**
     *  获取索引数量
     *  @return
     */
    virtual int    getTrianglesNum();
    
protected:
    int             formats[VertexType::CUSTOM6 + 1];
    
    GLuint          vertexBuffers[VertexType::CUSTOM6 + 1];
    void*           bufferDatas[VertexType::CUSTOM6 + 1];
    int             dataSizes[VertexType::CUSTOM6 + 1];
    
    void*           indexbufferData;
    int             indexSize;
    int             triangleNum;
    
    GLuint          indexBuffer;
};

NS_MONKEY_END

#endif