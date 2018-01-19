//
//  TextureUtilsIOS.h
//  Monkey
//
//  Created by Neil on 21/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _TextureUtilsIOS_h
#define _TextureUtilsIOS_h

#import "platform/PlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "platform/TextureUtils.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class TextureUtilsIOS : public TextureUtils {
    
public:
    
    ByteArray*  getTextureDataWithText(const char* text, const TextFormatter &format, int &width, int &height, bool &hasAlpha) override;
    
};

NS_MONKEY_END

#endif

#endif
