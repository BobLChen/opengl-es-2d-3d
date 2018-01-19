//
//  FontFNTCache.h
//  Monkey
//
//  Created by Neil on 24/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _FontFNTCache_h
#define _FontFNTCache_h

#include "2d/ui/font/Font.h"
#include "core/base/Object.h"

#include <string>
#include <map>

NS_MONKEY_BEGIN

class FontFNT;

class FontCache : public Object {
    
public:
    /**
     *  获取FNT字体
     *  @param fntName 字体名称(xxx.fnt)
     *  @return
     */
    static FontFNT* getFontFNT(const std::string& fntName);
    /**
     *  释放所有的字体
     */
    static void purgeAll();
    
private:
    static std::map<std::string, Font*> _fontMap;
    
    FontCache() : Object() {};
    ~FontCache() {};
};

NS_MONKEY_END

#endif
