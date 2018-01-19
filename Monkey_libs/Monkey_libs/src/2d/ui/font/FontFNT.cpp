//
//  FontFNT.cpp
//  Opengl2D
//
//  Created by Neil on 24/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/ui/font/FontFNT.h"
#include "core/utils/TextureCache.h"

NS_MONKEY_BEGIN

FontFNT* FontFNT::create(const std::string fntPath) {
    FontFNTConfig *config = new FontFNTConfig(fntPath);
    FontFNT *fntFont = new FontFNT(config, TextureCache::getInstance()->getTexture(config->getImagePath()));
    return fntFont;
}

FontFNT::FontFNT(FontFNTConfig *config, Texture2D *texture) :
Font(),
_config(config),
_texture(texture)
{
    
}

FontFNT::~FontFNT() {
    
}

Texture2D* FontFNT::getTexture() {
    return _texture;
}

FontFNTConfig* FontFNT::getConfig() {
    return _config;
}

int  FontFNT::getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar) const {
    unsigned int key = (firstChar << 16) | (secondChar & 0xFFFF);
    if (_config->getKernings().find(key) == _config->getKernings().end()) {
        return 0;
    }
    return _config->getKernings().at(key).amount;
}

int* FontFNT::getHorizontalKerningForTextUTF16(const std::u16string &text, int &outNumLetters) const {
    outNumLetters = (int)text.length();
    
    if (outNumLetters == 0) {
        return 0;
    }
    
    int *sizes = new int[outNumLetters];
    
    for (int c = 0; c < outNumLetters; c++) {
        if (c < outNumLetters - 1) {
            sizes[c] = getHorizontalKerningForChars(text[c], text[c + 1]);
        } else {
            sizes[c] = 0;
        }
    }
    
    return sizes;
}

NS_MONKEY_END