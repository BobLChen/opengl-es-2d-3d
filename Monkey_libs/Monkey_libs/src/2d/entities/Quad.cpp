//
//  Quad.cpp
//  Opengl2D
//
//  Created by Neil on 8/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "App.h"
#include "2d/entities/Quad.h"
#include "2d/utils/QuadUtils.h"
#include "2d/material/ColorMaterial2D.h"

#include "2d/material/Shaders2D.h"
#include "core/material/GLSLProgram.h"

NS_MONKEY_BEGIN

Quad* Quad::create(float width, float height, int color, float alpha) {
    Quad *quad = new Quad(width, height, color, alpha);
    return quad;
}

Quad::Quad(float width, float height, int color, float alpha) : DisplayObject() {
    
    _geometry = createQuadGeometry(width, height, _anchorPoint.x, _anchorPoint.y);
    
    _blue   = (color & 0xFF) * 1.0f / 0xFF;
    _green  = ((color >> 8)  & 0xFF) * 1.0f / 0xFF;
    _red    = ((color >> 16) & 0xFF) * 1.0f / 0xFF;
    
    _width  = width;
    _height = height;
    _min.setTo(0, 0);
    _max.setTo(_width, _height);
    
    if (alpha < 1.0f) {
        setBlendMode(BlendMode::ALPHA);
    }
    
    setAlpha(alpha);
}

Quad::~Quad() {
    if (_geometry) {
        delete _geometry;
    }
}

void Quad::setAnchor(float x, float y) {
    if (_anchorPoint.x == x && _anchorPoint.y == y) {
        return;
    }
    if (_geometry) {
        delete _geometry;
    }
    _anchorPoint.setTo(x, y);
    _geometry = createQuadGeometry(_width, _height, _anchorPoint.x, _anchorPoint.y);
}


void Quad::draw(bool includeChildren, Material3D* shader) {
    _enterDrawEvent.reset();
    dispatchEvent(_enterDrawEvent);
    
    if (inView() && _visible) {
        // draw quad-began
        DisplayObject::setGPUStats();
        
        App::getInstance()->mvp.identity();
        App::getInstance()->mvp.append(getWorld());
        App::getInstance()->mvp.append(App::getInstance()->view);
        App::getInstance()->mvp.append(App::getInstance()->projection);
        
        ColorMaterial2D::getInstance()->setColor(_red, _green, _blue, _alpha);
        ColorMaterial2D::getInstance()->draw(_geometry, App::getInstance()->mvp);
        
        DisplayObject::disableGPUStats();
        // draw quad-end
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

NS_MONKEY_END
