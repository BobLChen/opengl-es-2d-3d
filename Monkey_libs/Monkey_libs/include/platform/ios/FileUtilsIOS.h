//
//  FileUtilsIOS.h
//  Monkey
//
//  Created by Neil on 24/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __FileUtilsIOS__
#define __FileUtilsIOS__

#import "platform/PlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "platform/FileUtils.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class FileUtilsIOS : public FileUtils {
    
public:
    virtual std::string getFullPath(const std::string &filename);
};

NS_MONKEY_END

#endif

#endif
