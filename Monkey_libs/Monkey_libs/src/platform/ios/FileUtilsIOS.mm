//
//  FileUtilsIOS.cpp
//  TestOpenglES
//
//  Created by Neil on 24/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "platform/ios/FileUtilsIOS.h"
#include "platform/PlatformMacros.h"

#import <Foundation/Foundation.h>

NS_MONKEY_BEGIN

std::string FileUtilsIOS::getFullPath(const std::string &filename) {
    
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

FileUtils* FileUtils::getInstance() {
    if (!_instance) {
        _instance = new FileUtilsIOS();
    }
    return _instance;
}

NS_MONKEY_END
