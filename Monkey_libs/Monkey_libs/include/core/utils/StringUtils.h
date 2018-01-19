//
//  StringUtils.h
//  Monkey
//
//  Created by Neil on 25/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _StringUtils_h_H
#define _StringUtils_h_H

#include <ConvertUTF.h>
#include <string>
#include <stdlib.h>

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

namespace StringUtils {
    
    /**
     *  UTF8转换为UTF16
     *  @param utf8     utf8文本
     *  @param outUtf16 输出utf16文本
     *  @return
     */
    bool UTF8ToUFT16(const std::string &utf8, std::u16string &outUtf16) {
        
        if (utf8.empty()) {
            outUtf16.clear();
            return true;
        }
        
        bool ret = false;
        
        const size_t utf16Size = (utf8.length()+1) * sizeof(char16_t);
        char16_t*    utf16      = (char16_t*)malloc(utf16Size);
        
        memset(utf16, 0, utf16Size);
        
        char* utf16ptr    = reinterpret_cast<char*>(utf16);
        const UTF8* error = nullptr;
        
        if (llvm::ConvertUTF8toWide(2, utf8, utf16ptr, error)) {
            outUtf16 = utf16;
            ret = true;
        }
        
        free(utf16);
        
        return ret;
    }
    
}

NS_MONKEY_END

#endif
