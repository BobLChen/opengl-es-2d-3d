//
//  TextureCache.cpp
//  Monkey
//
//  Created by Neil on 10/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/utils/TextureCache.h"
#include "core/utils/Log.h"
#include "core/utils/BitmapData.h"
#include "core/texture/Texture2D.h"
#include "platform/FileUtils.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

TextureCache* TextureCache::_instance = nullptr;

TextureCache::TextureCache() {}
TextureCache::~TextureCache() {}

Texture2D* TextureCache::getTexture(const std::string &name) {
    
    std::string fullpath = FileUtils::getInstance()->getFullPath(name);
    
    if (fullpath.size() == 0) {
        return nullptr;
    }
    
    auto it = _textures.find(fullpath);
    if (it != _textures.end()) {
        return it->second;
    }
    // 未找到对应贴图、开始加载贴图
    BitmapData *bmd = new BitmapData();
    bool bdDone = bmd->initWithFile(fullpath);
    
    if (!bdDone) {
        LOGE("BitmapData Faild :%s\n", fullpath.c_str());
        delete bmd;
        return nullptr;
    }
    
    Texture2D *texture = new Texture2D();
    bool tDone = texture->initWithBitmapData(bmd);
    
    if (!tDone) {
        LOGE("Texture init Faild :%s\n", fullpath.c_str());
        delete texture;
        return nullptr;
    }
    // cache
    _textures.insert(std::make_pair(fullpath, texture));
    
    delete bmd;
    
    LOGE("load image -> %s", name.c_str());
    
    return texture;
}

void TextureCache::disposeTexture(const std::string &name) {
    auto it = _textures.find(name);
    if (it != _textures.end()) {
        _textures.erase(it);
        delete it->second;
    }
}

TextureCache* TextureCache::getInstance() {
    if (!_instance) {
        _instance = new TextureCache();
    }
    return _instance;
}

NS_MONKEY_END