//
//  TextureUtilsMac.h
//  Monkey_libs
//
//  Created by Neil on 2/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_TextureUtilsMac_h
#define Monkey_libs_TextureUtilsMac_h

#import "platform/PlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include "platform/TextureUtils.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class TextureUtilsMac : public TextureUtils {
    
public:
    
    ByteArray*  getTextureDataWithText(const char* text, const TextFormatter &format, int &width, int &height, bool &hasAlpha) override;
    
};

NS_MONKEY_END;

#endif

#endif
