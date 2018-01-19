//
//  FileUtilsMac.h
//  Monkey_libs
//
//  Created by Neil on 2/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_FileUtilsMac_h
#define Monkey_libs_FileUtilsMac_h

#import "platform/PlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include "platform/FileUtils.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN
class FileUtilsMac : public FileUtils {
    
public:
    virtual std::string getFullPath(const std::string &filename);
};

NS_MONKEY_END

#endif

#endif
