//
//  TextureAtlas.cpp
//  Opengl2D
//
//  Created by Neil on 11/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/texture/TextureAtlas.h"
#include "core/geom/Rectangle.h"
#include "core/texture/Texture2D.h"
#include "core/utils/TextureCache.h"
#include "core/utils/Log.h"

#include "platform/FileUtils.h"
#include "platform/PlatformMacros.h"

#include "rapidjson.h"
#include "document.h"

NS_MONKEY_BEGIN

TextureAtlas* TextureAtlas::_instance = nullptr;

TextureAtlas* TextureAtlas::getInstance() {
    if (!_instance) {
        _instance = new TextureAtlas();
    }
    return _instance;
}

TextureAtlas::TextureAtlas() {
    _frames.clear();
}

TextureAtlas::~TextureAtlas() {
    _frames.clear();
}

void TextureAtlas::addTextureAtlasWithJson(std::string path) {
    
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile(path);
    
    rapidjson::Document parser;
    parser.Parse<0>(jsonStr.c_str());
    
    if (parser.HasParseError() || (!parser.IsObject())) {
        LOGE("Parse Json Faild :%s", jsonStr.c_str());
        return;
    }
    
    // 获取image
    Texture2D *texture = nullptr;
    if (parser.HasMember("meta")) {
        const rapidjson::Value &meta = parser["meta"];
        texture = TextureCache::getInstance()->getTexture(meta["image"].GetString());
    } else {
        LOGE("Invalid format :%s", jsonStr.c_str());
        return;
    }
    
    if (parser.HasMember("frames")) {
        const rapidjson::Value &frames = parser["frames"];
        
        for (rapidjson::SizeType i = 0; i < frames.Size(); i++) {
            
            FrameTexture* frameTexture = new FrameTexture();
            
            const rapidjson::Value &frame = frames[i];
            const rapidjson::Value &frameSize = frame["frame"];
            const rapidjson::Value &spriteSourceSize = frame["spriteSourceSize"];
            const rapidjson::Value &sourceSize = frame["sourceSize"];
            
            std::string filename = frame["filename"].GetString();
            Rectangle frameRect(frameSize["x"].GetInt(), frameSize["y"].GetInt(), frameSize["w"].GetInt(), frameSize["h"].GetInt());
            bool rotated = frame["rotated"].GetBool();
            bool trimmed = frame["trimmed"].GetBool();
            Rectangle spriteRect(spriteSourceSize["x"].GetInt(), spriteSourceSize["y"].GetInt(), spriteSourceSize["w"].GetInt(), spriteSourceSize["h"].GetInt());
            Vector2D size(sourceSize["w"].GetInt(), sourceSize["h"].GetInt());
            
            frameTexture->initWidth(filename, frameRect, rotated, trimmed, spriteRect, size, texture);
            _frames.insert(std::make_pair(filename, frameTexture));
        }
    }
}

FrameTexture* TextureAtlas::getFrameTextureByName(std::string name) {
    return _frames.at(name);
}

void TextureAtlas::dispose() {
    
}

NS_MONKEY_END