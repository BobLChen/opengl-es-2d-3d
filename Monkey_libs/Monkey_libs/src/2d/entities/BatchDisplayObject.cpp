//
//  BatchDisplayObject.cpp
//  Opengl2D
//
//  Created by Neil on 21/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "App.h"

#include "2d/entities/BatchDisplayObject.h"
#include "2d/entities/Image.h"
#include "2d/material/TextureMaterial2D.h"

#include "core/geom/Matrix3DUtils.h"
#include "core/material/GLSLProgram.h"
#include "core/material/Geometry3D.h"
#include "core/utils/Log.h"

#include <algorithm>
#include <stdlib.h>

NS_MONKEY_BEGIN

#define QuadVertexSize  12      // 顶点数量
#define QuadUVSize      8       // uv数量

// 批处理不使用geometry
BatchDisplayObject::BatchDisplayObject(int size) :
DisplayObject(),
_inited(false),
_quadsLimit(size),
_totalQuads(0),
_texture(nullptr)
{
    _children.reserve(size);
    
    _vertices = (float*)malloc(sizeof(float) * 12 * _quadsLimit);
    _uvs      = (float*)malloc(sizeof(float) * 8  * _quadsLimit);
    _indices  = (unsigned short*)malloc(sizeof(unsigned short) * 6 * _quadsLimit);
    
    memset(_vertices, 0, sizeof(float) * 12 * _quadsLimit);
    memset(_uvs, 0, sizeof(float) * 8 * _quadsLimit);
    memset(_indices, 0, sizeof(unsigned short) * 6 * _quadsLimit);
    
    _min.setTo(0, 0);
    _max.setTo(0, 0);
}

BatchDisplayObject::~BatchDisplayObject() {
    
    if (_autoRelease) {
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            delete (*iter);
        }
    }
    
    _children.clear();
    _nodesMap.clear();
    
    if (_geometry) {
        delete _geometry;
        _geometry = nullptr;
    }
    
    if (vertexBuffer != 0) {
        glDeleteBuffers(1, &vertexBuffer);
        vertexBuffer = 0;
    }
    if (uvBuffer != 0) {
        glDeleteBuffers(1, &uvBuffer);
        uvBuffer = 0;
    }
    if (indexBuffer != 0) {
        glDeleteBuffers(1, &indexBuffer);
        indexBuffer = 0;
    }
    
    free(_vertices);
    free(_uvs);
    free(_indices);
    
    _vertices = nullptr;
    _uvs      = nullptr;
    _indices  = nullptr;
}

/**
 *  设置texture
 *  @param texture
 */
void BatchDisplayObject::setupTexture(Texture2D *texture) {
    _texture = texture;
    if (_texture->isAlpha()) {
        setBlendMode(BlendMode::ALPHA);
    }
}

void BatchDisplayObject::addChild(Image *child) {
    if (_children.size() > _quadsLimit) {
        LOGE("More children than %d", _quadsLimit);
        return;
    }
    if (std::find(_children.begin(), _children.end(), child) != _children.end()) {
        return;
    }
    if (!_texture) {
        _texture = child->getTexture();
    }
    _totalQuads++;
    _contentDirty = true;
    _children.push_back(child);
    _nodesMap.insert(std::make_pair(child, true));
    // 添加监听
    child->addEventListener(Pivot3D::UPDATE_TRANSFORM_EVENT, this, EVENT_CALLBACK(BatchDisplayObject::onNodeTransformUpdate));
}

void BatchDisplayObject::onNodeTransformUpdate(Event *e) {
    Image *node = dynamic_cast<Image*>(e->getTarget());
    if (!node) {
        return;
    }
    _nodesMap[node] = true;
    _contentDirty   = true;
}

void BatchDisplayObject::removeChild(Image *child) {
    if (_totalQuads <= 0) {
        return;
    }
    for (int i = 0; i < _totalQuads; i++) {
        if (_children[i] == child) {
            removeChildAt(i);
            break;
        }
    }
}

void BatchDisplayObject::removeChildAt(int idx) {
    if (_totalQuads == 0 || idx >= _totalQuads || idx < 0) {
        return;
    }
    int len = _totalQuads - 1 - idx;
    if (len > 0) {
        memmove(_vertices + QuadVertexSize * idx, _vertices + QuadVertexSize * (idx + 1), len * QuadVertexSize * sizeof(float));
        memmove(_uvs + QuadUVSize * idx, _uvs + QuadUVSize * (idx + 1), len * QuadUVSize * sizeof(float));
    }
    // 移除监听器
    _children[idx]->removeEventListener(Pivot3D::UPDATE_TRANSFORM_EVENT, this, EVENT_CALLBACK(BatchDisplayObject::onNodeTransformUpdate));
    
    _nodesMap.erase(dynamic_cast<Image*>(_children[idx]));
    _children.erase(_children.begin() + idx);
    _totalQuads--;
}

void BatchDisplayObject::addChildAt(Image *child, int idx) {
    if (_children.size() > _quadsLimit) {
        LOGE("More children than %d", _quadsLimit);
        return;
    }
    if (std::find(_children.begin(), _children.end(), child) != _children.end()) {
        return;
    }
    if (!_texture) {
        _texture = child->getTexture();
    }
    _totalQuads++;
    int len = _totalQuads - 1 - idx;
    if (len > 0) {
        memmove(_vertices + QuadVertexSize * (idx + 1), _vertices + QuadVertexSize * idx, len * QuadVertexSize * sizeof(float));
        memmove(_uvs + QuadUVSize * (idx + 1), _uvs + QuadUVSize * idx, len * QuadUVSize * sizeof(float));
    }
    _children.insert(_children.begin() + idx, child);
    _nodesMap.insert(std::make_pair(child, true));
    _contentDirty = true;
    // 添加监听
    child->addEventListener(Pivot3D::UPDATE_TRANSFORM_EVENT, this, EVENT_CALLBACK(BatchDisplayObject::onNodeTransformUpdate));
}

/**
 *  初始化索引数据
 */
void BatchDisplayObject::setupIndices() {
    for (int i = 0; i < _quadsLimit; i++) {
        int step0 = i * 6;
        int step1 = i * 4;
        _indices[step0 + 0] = step1 + 0;
        _indices[step0 + 1] = step1 + 1;
        _indices[step0 + 2] = step1 + 2;
        _indices[step0 + 3] = step1 + 2;
        _indices[step0 + 4] = step1 + 1;
        _indices[step0 + 5] = step1 + 3;
    }
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 6 * _quadsLimit, _indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
 *  初始顶点数据
 */
void BatchDisplayObject::setupVertices() {
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 * _quadsLimit, _vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 *  初始uv数据
 */
void BatchDisplayObject::setupUvs() {
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * _quadsLimit, _uvs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 *  更新顶点数据
 */
void BatchDisplayObject::updateVertexData() {
    // 遍历所有节点
    int idx = 0;
    int floatSize = sizeof(float);
    float vertData[QuadVertexSize] = {0.0f};
    
    _min.setTo(MAX_B, MAX_B);
    _max.setTo(MIN_B, MIN_B);
    
    // 更新顶点数据以及uv数据
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        if (*iter == nullptr) {
            continue;
        }
        Image* disp = dynamic_cast<Image*>((*iter));
        // 该节点需要更新
        if (_nodesMap.find(disp)->second) {
            _nodesMap.find(disp)->second = false;
            
            const char* posBuf = disp->getGeometry3d()->getVertexBuffer(Geometry3D::VertexType::POSITION);
            for (int i = 0; i < 4; i++) {
                _tempVec30.setTo(*(float*)(posBuf + floatSize * (i * 3)), *(float*)(posBuf + floatSize * (i * 3 + 1)), *(float*)(posBuf + floatSize * (i * 3 + 2)), 1.0f);
                
                Matrix3DUtils::transformVector(disp->getWorld(), _tempVec30, _tempVec30);
                vertData[i * 3 + 0] = _tempVec30.x;
                vertData[i * 3 + 1] = _tempVec30.y;
                vertData[i * 3 + 2] = _tempVec30.z;
                
                if (_min.x > _tempVec30.x) {
                    _min.x = _tempVec30.x;
                }
                if (_min.y > _tempVec30.y) {
                    _min.y = _tempVec30.y;
                }
                if (_max.x < _tempVec30.x) {
                    _max.x = _tempVec30.x;
                }
                if (_max.y < _tempVec30.y) {
                    _max.y = _tempVec30.y;
                }
                
                // 更新顶点数据
                memcpy(_vertices + idx * QuadVertexSize, vertData, sizeof(vertData));
                // 更新uv数据
                const char* uvBuf = disp->getGeometry3d()->getVertexBuffer(Geometry3D::VertexType::UV0);
                memcpy(_uvs + idx * QuadUVSize, uvBuf, sizeof(float) * QuadUVSize);
                
            }
        }
        idx++;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * QuadVertexSize * _quadsLimit, _vertices);
    
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * QuadUVSize * _quadsLimit, _uvs);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}

/**
 *  目前暂时只支持带Texture的
 *  @param includeChildren
 */
void BatchDisplayObject::draw(bool includeChildren, Material3D* shader) {
    
    _enterDrawEvent.reset();
    dispatchEvent(_enterDrawEvent);
    
    // draw-began
    if (_visible || _texture || inView()) {
        if (!_inited) {
            setupVertices();
            setupUvs();
            setupIndices();
            _inited = true;
        }
        
        if (_contentDirty) {
            updateVertexData();
            _contentDirty = false;
        }
        
        setGPUStats();
        
        App::getInstance()->vertices  += 4 * _quadsLimit;
        App::getInstance()->drawcalls += 1 * _quadsLimit;
        App::getInstance()->triangles += 2 * _quadsLimit;
        
        App::getInstance()->mvp.identity();
        App::getInstance()->mvp.append(getWorld());
        App::getInstance()->mvp.append(App::getInstance()->view);
        App::getInstance()->mvp.append(App::getInstance()->projection);
        
        GLSLProgram *program = TextureMaterial2D::getInstance()->getProgram();
        
        program->enable();
        _texture->enableTexture();
        
        program->setUniform1i("texture", 0);
        program->setUniform1f("alpha", _alpha);
        program->setUniformMatrix4fv("mvp", App::getInstance()->mvp.rawData, 1, GL_FALSE);
        
        GLint posVa = program->getAttribLocation("posVa");
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableVertexAttribArray(posVa);
        glVertexAttribPointer(posVa, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        
        GLint uvVa  = program->getAttribLocation("uvVa");
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glEnableVertexAttribArray(uvVa);
        glVertexAttribPointer(uvVa, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glDrawElements(GL_TRIANGLES, 6 * _quadsLimit, GL_UNSIGNED_SHORT, 0);
        
        glDisableVertexAttribArray(posVa);
        glDisableVertexAttribArray(uvVa);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        _texture->disableTexture();
        
        disableGPUStats();
    }
    // draw-end
    _exitDrawEvent.reset();
    dispatchEvent(_exitDrawEvent);
}

int BatchDisplayObject::getLength() {
    return _totalQuads;
}

void BatchDisplayObject::setAutoRelease(bool value) {
    _autoRelease = value;
}

NS_MONKEY_END
