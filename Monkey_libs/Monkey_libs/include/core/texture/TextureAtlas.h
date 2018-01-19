//
//  TextureAtlas.h
//  Monkey
//
//  Created by Neil on 11/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _TextureAtlas_h
#define _TextureAtlas_h

#include "core/texture/FrameTexture.h"

#include <string>
#include <map>

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class Rectangle;

class TextureAtlas {
    
public:
    
    static TextureAtlas* getInstance();
    /**
     *  添加贴图集。使用TexturePacker工具，采用JsonArray格式。
     *  @param path
     */
    virtual void addTextureAtlasWithJson(std::string path);
    /**
     *  根据名称获取TextureFrame
     *  @param name
     *  @return
     */
    virtual FrameTexture* getFrameTextureByName(std::string name);
    /**
     *  销毁
     *  @return
     */
    virtual void dispose();
    
private:
    
    TextureAtlas();
    ~TextureAtlas();
    
    std::map<std::string, FrameTexture*> _frames;
    static TextureAtlas* _instance;
    
};

NS_MONKEY_END

#endif
