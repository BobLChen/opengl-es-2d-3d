//
//  TextureUtils.cpp
//  Opengl2D
//
//  Created by Neil on 21/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "platform/TextureUtils.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

TextureUtils* TextureUtils::_instance = nullptr;

TextureUtils::TextureUtils() {
    
}

TextureUtils::~TextureUtils() {
    
}

ByteArray* TextureUtils::getTextureDataWithText(const char *text, const TextFormatter &format, int &width, int &height, bool &hasAlpha) {
    return nullptr;
}

NS_MONKEY_END