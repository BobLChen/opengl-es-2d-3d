//
//  FileUtilsMac.cpp
//  Monkey_libs
//
//  Created by Neil on 2/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "FileUtilsMac.h"
#include "platform/PlatformMacros.h"

#import <Foundation/Foundation.h>

NS_MONKEY_BEGIN

FileUtils* FileUtils::getInstance() {
    if (!_instance) {
        _instance = new FileUtilsMac();
    }
    return _instance;
}

std::string FileUtilsMac::getFullPath(const std::string &filename) {
    
    if (filename[0] == '/') {
        return filename;
    }
    
    NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:filename.c_str()]
                                                         ofType:nil];
    if (fullpath != nil) {
        return [fullpath UTF8String];
    }
    return nullptr;
}

NS_MONKEY_END