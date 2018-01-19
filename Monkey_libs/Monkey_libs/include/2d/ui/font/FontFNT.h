//
//  FontFNT.h
//  Monkey
//
//  Created by Neil on 24/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _FontFNT_h
#define _FontFNT_h

#include "2d/ui/font/Font.h"
#include "2d/ui/font/FontFNTConfig.h"

#include "core/texture/Texture2D.h"

#include <string>

NS_MONKEY_BEGIN

class FontFNT : public Font {
    
public:
    /**
     *  通过fnt文件创建FNT字体
     *  @param fntPath fnt文件名
     *  @return
     */
    static FontFNT* create(const std::string fntPath);
    
    FontFNT(FontFNTConfig *config, Texture2D *texture);
    ~FontFNT();
    /**
     *  获取FNT贴图
     *  @return
     */
    Texture2D* getTexture();
    /**
     *  获取水平字距
     *  @param text          文本
     *  @param outNumLetters 数量
     *  @return
     */
    int* getHorizontalKerningForTextUTF16(const std::u16string &text, int &outNumLetters) const;
    /**
     *  获取字距
     *  @param firstChar  第一个字符
     *  @param secondChar 第二个字符
     *  @return 字距
     */
    int  getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar) const;
    /**
     *  获取FNT字体配置
     *  @return
     */
    FontFNTConfig* getConfig();
    
private:
    
    FontFNTConfig* _config;
    Texture2D*     _texture;
};

NS_MONKEY_END

#endif
