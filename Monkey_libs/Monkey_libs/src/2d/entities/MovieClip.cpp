//
//  MovieClip.cpp
//  Monkey_libs
//
//  Created by Neil on 5/11/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/entities/MovieClip.h"
#include "2d/entities/Image.h"

NS_MONKEY_BEGIN

MovieClip::MovieClip() : DisplayObject(), _currentFrameDisp(nullptr) {
    
}

MovieClip::~MovieClip() {
    for (auto iter = _frames.begin(); iter != _frames.end(); iter++) {
        delete (*iter);
    }
    _frames.clear();
}

void MovieClip::addFrame(const std::string &frame, Type type) {
    Image *image = nullptr;
    switch (type) {
        case Type::TEXTURE:
            image = Image::create(frame);
            break;
        case Type::TEXTURE_FRAME:
            image = Image::createFrameTexture(frame);
            break;
        default:
            break;
    }
    _frames.push_back(image);
    image->parent(this);
    
    if (_frames.size() == 1) {
        _currentFrameDisp = image;
    }
    
    _to   = _frames.size();
    _from = 0;
}

void MovieClip::draw(bool includeChildren, Material3D *shader) {
    
    _enterDrawEvent.reset();
    dispatchEvent(_enterDrawEvent);
    
    if (includeChildren) {
        // draw children
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            (*iter)->draw(includeChildren, shader);
        }
    }
    
    if (_currentFrameDisp) {
        _currentFrameDisp->draw(includeChildren, shader);
    }
    
    _exitDrawEvent.reset();
    dispatchEvent(_exitDrawEvent);

}

void MovieClip::setCurrentFrame(float value) {
    if (value >= _to) {
        value = _to - 1;
    } else if (value < _from) {
        value = _from;
    }
    _currentFrame = value;
    _currentFrameDisp = _frames[(int)_currentFrame];
}

void MovieClip::updateTransforms(bool includeChildren) {
    DisplayObject::updateTransforms(includeChildren);
    if (includeChildren && _currentFrameDisp) {
        _currentFrameDisp->updateTransforms(includeChildren);
    }
}

NS_MONKEY_END