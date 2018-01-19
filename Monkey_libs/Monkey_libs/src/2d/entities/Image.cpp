//
//  Image.cpp
//  Opengl2D
//
//  Created by Neil on 9/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "App.h"

#include "core/texture/Texture2D.h"
#include "core/texture/FrameTexture.h"
#include "core/texture/TextureAtlas.h"

#include "core/geom/Rectangle.h"
#include "core/utils/TextureCache.h"

#include "2d/material/TextureMaterial2D.h"
#include "2d/utils/QuadUtils.h"
#include "2d/entities/Image.h"

NS_MONKEY_BEGIN

Image* Image::create(const std::string &textureName) {
    Image *image = new Image();
    image->initWithTexture(textureName);
    return image;
}

Image* Image::create(Texture2D *texture) {
    Image *image = new Image();
    image->initWithTexture(texture);
    return image;
}

Image* Image::create(Texture2D *texture, const Rectangle &rect) {
    Image *image = new Image();
    image->initWithTexture(texture, rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
    return image;
}

Image* Image::create(Texture2D *texture, float x, float y, float width, float height) {
    Image *image = new Image();
    image->initWithTexture(texture, x, y, width, height);
    return image;
}

Image* Image::createFrameTexture(const std::string &frameTextureName) {
    Image *image = new Image();
    image->initWithFrameTexture(frameTextureName);
    return image;
}

Image* Image::create(FrameTexture *frameTexture) {
    Image *image = new Image();
    image->initWithFrameTexture(frameTexture);
    return image;
}

Image* Image::create(FrameTexture *frameTexture, float width, float height) {
    Image *image = new Image();
    image->initWithFrameTexture(frameTexture, width, height);
    return image;
}

Image* Image::create(FrameTexture *frameTexture, const Vector2D &size) {
    Image *image = new Image();
    image->initWithFrameTexture(frameTexture, size);
    return image;
}

Image::Image() :
DisplayObject(),
_texture(nullptr),
_frameTexture(nullptr) {
    
}

Image::~Image() {
    
}

void Image::initWithTexture(const std::string &textureName) {
    initWithTexture(TextureCache::getInstance()->getTexture(textureName));
}

void Image::initWithTexture(Texture2D *texture) {
    initWithTexture(texture, 0, 0, texture->getWidth(), texture->getHeight());
}

void Image::initWithTexture(Texture2D *texture, const Rectangle &rect) {
    initWithTexture(texture, rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

void Image::initWithTexture(Texture2D *texture, float x, float y, float width, float height) {
    
    if (_geometry) {
        delete _geometry;
        _geometry = nullptr;
    }
    
    _width  = width;
    _height = height;
    _min.setTo(0, 0);
    _max.setTo(_width, _height);
    
    float su = x / texture->getWidth();
    float sv = y / texture->getHeight();
    float eu = (x + width) / texture->getWidth();
    float ev = (y + height) / texture->getHeight();
    
    _geometry = createQuadGeometry(_width, _height, _anchorPoint.x, _anchorPoint.y, su, sv, eu, ev);
    
    if (texture->isAlpha()) {
        setBlendMode(BlendMode::ALPHA);
    }
    _texture  = texture;
    _textureRect.set(x, y, width, height);
}

void Image::initWithFrameTexture(const std::string &frameTextureName) {
    initWithFrameTexture(TextureAtlas::getInstance()->getFrameTextureByName(frameTextureName));
}

void Image::initWithFrameTexture(FrameTexture *frameTexture) {
    initWithFrameTexture(frameTexture, frameTexture->getSourceSize());
}

void Image::initWithFrameTexture(FrameTexture *frameTexture, const Vector2D &size) {
    initWithFrameTexture(frameTexture, size.x, size.y);
}

void Image::initWithFrameTexture(FrameTexture *frameTexture, float width, float height) {
    
    _width  = width;
    _height = height;
    _min.setTo(0, 0);
    _max.setTo(_width, _height);
    
    // 获取Texture宽度
    float w = frameTexture->getTexture()->getWidth();
    float h = frameTexture->getTexture()->getHeight();
    // 获取FrameTexture区域
    float tx = frameTexture->getFrame().getLeft();
    float ty = frameTexture->getFrame().getTop();
    float tw = frameTexture->getFrame().getWidth();
    float th = frameTexture->getFrame().getHeight();
    // 旋转，获取正常的矩形区域
    if (frameTexture->getRotated()) {
        float tmp = tw;
        tw = th;
        th = tmp;
    }
    // 计算uv值
    float su = tx / w;
    float sv = ty / h;
    float eu = (tx + tw) / w;
    float ev = (ty + th) / h;
    
    if (_geometry) {
        delete _geometry;
        _geometry = nullptr;
    }
    
    _geometry = createQuadGeometry(_width, _height, _anchorPoint.x, _anchorPoint.y, su, sv, eu, ev, frameTexture->getRotated());
    // 透明贴图一定开启混合模式
    if (frameTexture->getTexture()->isAlpha()) {
        setBlendMode(BlendMode::ALPHA);
    }
    
    _frameTexture = frameTexture;
    _texture      = frameTexture->getTexture();
}

void Image::draw(bool includeChildren, Material3D* shader) {
    
    _enterDrawEvent.reset();
    dispatchEvent(_enterDrawEvent);
    
    if (inView() && _visible && _texture && _geometry) {
        // draw-began
        DisplayObject::setGPUStats();
        App::getInstance()->mvp.identity();
        App::getInstance()->mvp.append(getWorld());
        App::getInstance()->mvp.append(App::getInstance()->view);
        App::getInstance()->mvp.append(App::getInstance()->projection);
        TextureMaterial2D::getInstance()->draw(_geometry, _texture, App::getInstance()->mvp, _alpha);
        DisplayObject::disableGPUStats();
        // draw-end
    }
    
    if (includeChildren) {
        // draw children
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            (*iter)->draw(includeChildren, shader);
        }
    }
    
    _exitDrawEvent.reset();
    dispatchEvent(_exitDrawEvent);
}

void Image::setAnchor(float x, float y) {
    if (_anchorPoint.x == x && _anchorPoint.y == y) {
        return;
    }
    _anchorPoint.setTo(x, y);
    if (_frameTexture) {
        initWithFrameTexture(_frameTexture, _width, _height);
    } else if (_texture) {
        initWithTexture(_texture, _textureRect.getX(), _textureRect.getY(), _textureRect.getWidth(), _textureRect.getHeight());
    }
}

Texture2D* Image::getTexture() {
    return _texture;
}

NS_MONKEY_END