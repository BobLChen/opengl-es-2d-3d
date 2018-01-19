//
//  TextureCache.h
//  Monkey
//
//  Created by Neil on 10/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _TextureCache_h
#define _TextureCache_h

#include <string>
#include <map>

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class Texture2D;

/**
 *  Texture缓存
 */
class TextureCache {
    
public:
    
    /**
     *  根据名称获取贴图
     *  @param name 贴图名称
     *  @return Texture2D
     */
    Texture2D* getTexture(const std::string &name);
    
    /**
     *  销毁Texture
     *  @param name 贴图名称
     */
    void disposeTexture(const std::string &name);
    
    /**
     *  获取贴图缓存实例
     *  @return
     */
    static TextureCache* getInstance();
    
private:
    
    TextureCache();
    ~TextureCache();
    
    static TextureCache* _instance;
    
    std::map<std::string, Texture2D*> _textures;
    
};

NS_MONKEY_END

#endif
