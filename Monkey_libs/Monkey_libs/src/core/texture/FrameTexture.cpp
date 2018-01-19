//
//  FrameTexture.cpp
//  Opengl2D
//
//  Created by Neil on 12/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/texture/FrameTexture.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

FrameTexture::FrameTexture():
_texture(nullptr),
_rotated(false),
_trimmed(false) {
    _frame.set(0, 0, 0, 0);
    _spriteSourceSize.set(0, 0, 0, 0);
    _sourceSize.setTo(0, 0);
}

FrameTexture::~FrameTexture() {
    
}

void FrameTexture::initWidth(std::string filename, const Rectangle &frame, bool rotated, bool trimmed, const Rectangle &spriteSourceSize, const Vector2D &sourceSize, Texture2D* texture) {
    _filename = filename;
    _rotated  = rotated;
    _trimmed  = trimmed;
    _sourceSize.x = sourceSize.x;
    _sourceSize.y = sourceSize.y;
    _texture = texture;
    _frame.copyFrom(frame);
    _spriteSourceSize.copyFrom(spriteSourceSize);
}

Texture2D* FrameTexture::getTexture() const {
    return _texture;
}

const std::string& FrameTexture::getFilename() const {
    return _filename;
}

const Rectangle& FrameTexture::getFrame() const {
    return _frame;
}

const Rectangle& FrameTexture::getSpriteSourceSize() const {
    return _spriteSourceSize;
}

const Vector2D& FrameTexture::getSourceSize() const {
    return _sourceSize;
}

bool FrameTexture::getRotated() const {
    return _rotated;
}

bool FrameTexture::getTrimmed() const {
    return _trimmed;
}

NS_MONKEY_END
