//
//  BatchDisplayObjection.h
//  Opengl2D
//
//  Created by Neil on 21/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _BatchDisplayObject_h
#define _BatchDisplayObject_h

#include "core/base/GLBase.h"
#include "core/texture/Texture2D.h"

#include "2d/entities/DisplayObject.h"

#include <vector>
#include <map>

NS_MONKEY_BEGIN

#define BATCH_DEFAULT_SIZE 50

class Image;

/**
 *  批处理2d显示对象，目前只支持带纹理贴图的显示对象。
 *  为了性能考量，添加或者删除都是出于无序状态。
 */
class BatchDisplayObject : public DisplayObject {
   
public:
    
    BatchDisplayObject(int size = BATCH_DEFAULT_SIZE);
    
    virtual ~BatchDisplayObject();
    /**
     *  设置Texture
     *  @param texture
     */
    virtual void setupTexture(Texture2D *texture);
    /**
     *  添加一个child
     *  @param child
     */
    virtual void addChild(Image *child);
    /**
     *  添加一个child
     *  @param child
     *  @param idx
     */
    virtual void addChildAt(Image *child, int idx);
    /**
     *  移除child
     *  @param child
     */
    virtual void removeChild(Image *child);
    /**
     *  移除child
     *  @param idx
     */
    virtual void removeChildAt(int idx);
    /**
     *  绘制
     *  @param includeChildren
     */
    virtual void draw(bool includeChildren = true, Material3D* shader = nullptr) override;
    /**
     *  节点长度
     *  @return
     */
    virtual int getLength();
    /**
     *  设置是否自动释放节点
     *  @param value
     */
    virtual void setAutoRelease(bool value);
    
protected:
    
    /**
     *  节点transform更新事件
     *  @param e
     */
    virtual void onNodeTransformUpdate(Event *e);
    /**
     *  设置顶点数据
     */
    virtual void setupVertices();
    /**
     *  设置uv数据
     */
    virtual void setupUvs();
    /**
     *  设置索引数据
     */
    virtual void setupIndices();
    /**
     *  更新顶点以及uv数据
     */
    virtual void updateVertexData();
    
    std::map<Image*, bool> _nodesMap; // 待更新节点字典
    
    Texture2D*  _texture;   //
    bool        _contentDirty;
    bool        _autoRelease;
    bool        _inited;    // 是否初始化
    int         _quadsLimit;// quad最大数量
    int         _totalQuads;// quad总数
    float*      _vertices;  // 顶点数据
    float*      _uvs;       // uv数据
    
    unsigned short*    _indices;   // 索引数据
    
    // gpu各种buffer
    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint indexBuffer;
};

NS_MONKEY_END

#endif
