//
//  TextureUtils.h
//  Monkey
//
//  Created by Neil on 21/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _TextureUtils_h
#define _TextureUtils_h

#include "core/utils/ByteArray.h"
#include "core/utils/TextFormatter.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class TextureUtils {
    
public:
    
    /**
     *  获取TextureUtils实例
     *  @return
     */
    static TextureUtils* getInstance();
    /**
     *  根据text获取texture数据
     *  @param text     文本
     *  @param format   格式
     *  @param width    文本宽度
     *  @param height   文本高度
     *  @param hasAlpha 是否透明
     *  @return texture数据
     */
    virtual ByteArray*  getTextureDataWithText(const char* text, const TextFormatter &format, int &width, int &height, bool &hasAlpha);
    
protected:
    
    TextureUtils();
    
    virtual ~TextureUtils();
    
    static TextureUtils *_instance;
};

NS_MONKEY_END;

#endif
