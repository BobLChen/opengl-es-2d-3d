//
//  FontFNTCache.cpp
//  Opengl2D
//
//  Created by Neil on 24/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/ui/font/FontFNT.h"
#include "2d/ui/font/FontCache.h"

NS_MONKEY_BEGIN

std::map<std::string, Font*> FontCache::_fontMap;

void FontCache::purgeAll() {
    _fontMap.clear();
}

FontFNT* FontCache::getFontFNT(const std::string &fntName) {
    auto iter = _fontMap.find(fntName);
    if (iter == _fontMap.end()) {
        auto fntFont = FontFNT::create(fntName);
        if (fntFont) {
            _fontMap[fntName] = fntFont;
        }
    }
    return static_cast<FontFNT*>(_fontMap[fntName]);
}

NS_MONKEY_END