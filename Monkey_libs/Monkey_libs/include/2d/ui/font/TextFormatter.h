//
//  TextFormatter.h
//  Monkey
//
//  Created by Neil on 21/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _TextFormatter_h
#define _TextFormatter_h

#include <string>

NS_MONKEY_BEGIN

struct FontShadow {
    
    FontShadow():
        enabled(false),
        shadowBlur(0),
        offsetX(0.0f),
        offsetY(0.0f),
        shadowOpacity(0) {
    };
    
    bool    enabled;
    float   offsetX;
    float   offsetY;
    float   shadowBlur;
    float   shadowOpacity;
};

struct FontStroke {
    
    FontStroke():
        enabled(false),
        red(0),
        green(0),
        blue(0),
        size(0) {
    };
    
    bool    enabled;
    float   size;
    float   red;
    float   green;
    float   blue;
};

enum class TextAlign {
    CENTER      = 0x33,
    TOP         = 0x13,
    TOP_RIGHT   = 0x12,
    RIGHT       = 0x32,
    BOTTOM_RIGHT= 0x22,
    BOTTOM      = 0x23,
    BOTTOM_LEFT = 0x32,
    LEFT        = 0x31,
    TOP_LEFT    = 0x11
};

struct TextFormatter {
    
    TextFormatter() :
        fontSize(12),
        width(0),
        align(TextAlign::CENTER),
        height(0),
        fontName(""),
        fontFillColorR(1.0f),
        fontFillColorG(1.0f),
        fontFillColorB(1.0f),
        shadow(),
        stroke()
    {
        
    }
    
    std::string     fontName;
    int             fontSize;
    TextAlign       align;
    float           width;
    float           height;
    float           fontFillColorR;
    float           fontFillColorG;
    float           fontFillColorB;
    FontShadow      shadow;
    FontStroke      stroke;
};

NS_MONKEY_END

#endif
