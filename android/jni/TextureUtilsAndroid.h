//
//  TextureUtilsIOS.h
//  Monkey
//
//  Created by Neil on 21/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _TextureUtilsAndroid_h
#define _TextureUtilsAndroid_h

#include "platform/PlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/TextureUtils.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

#define ALIGN_TOP    1
#define ALIGN_CENTER 3
#define ALIGN_BOTTOM 2

typedef struct {
    unsigned int    height;
    unsigned int    width;
    bool            isPremultipliedAlpha;
    bool            hasShadow;
    float           offsetX;
    float           offsetY;
    float           shadowBlur;
    float           shadowOpacity;
    bool            hasStroke;
    float           strokeR;
    float           strokeG;
    float           strokeB;
    float           strokeSize;
    float           tintR;
    float           tintG;
    float           tintB;
    unsigned char*  data;
} TextureInfo;

class TextureUtilsAndroid : public TextureUtils {
    
public:
    
	static TextureInfo *sharedInfo;
	
    ByteArray*  getTextureDataWithText(const char* text, const TextFormatter &format, int &width, int &height, bool &hasAlpha) override;
    
};

NS_MONKEY_END

#endif

#endif
