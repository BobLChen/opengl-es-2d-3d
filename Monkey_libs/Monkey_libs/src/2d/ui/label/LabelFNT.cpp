//
//  LabelFNT.cpp
//  Opengl2D
//
//  Created by Neil on 25/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/ui/label/LabelFNT.h"
#include "2d/ui/font/FontCache.h"
#include "2d/entities/Image.h"

#include "App.h"

NS_MONKEY_BEGIN

LabelFNT* LabelFNT::create(const std::string &fntFile, const std::string &txt, int maxContent) {
    FontFNT *bmFNT = FontCache::getFontFNT(fntFile);
    LabelFNT *label = new LabelFNT(maxContent);
    label->setFontFNT(bmFNT);
    label->setText(txt);
    return label;
}

LabelFNT::LabelFNT(int maxContent) :
Label(),
_fontFNT(nullptr),
_bath(nullptr),
_limitContent(maxContent),
_horizontalKernings(nullptr)
{
    
}

LabelFNT::~LabelFNT() {
    
}

void LabelFNT::setFontFNT(FontFNT *fontFNT) {
    if (_fontFNT == fontFNT) {
        return;
    }
    _fontFNT = fontFNT;
    _contentDirty = true;
}

void LabelFNT::computeHorizontalKernings(const std::u16string &txt) {
    int numLetters = 0;
    if (_horizontalKernings) {
        delete [] _horizontalKernings;
    }
    _horizontalKernings = _fontFNT->getHorizontalKerningForTextUTF16(txt, numLetters);
}

void LabelFNT::createStringSprites() {
    
    _letters.clear();
    
    int longestLine = 0;
    unsigned int totalHeight = _fontFNT->getConfig()->getCommonHeight() * _linesNum;
    int nextFontX = 0;
    int nextFontY = totalHeight;
    int contentScaleFactor = 1;
    
    int charXOffset = 0;
    int charYOffset = 0;
    int charAdvance = 0;
    int lineIdx     = 0;
    bool lineStart  = false;
    
    unsigned int stringLen = (unsigned int)_utf16Txt.length();
    auto strWhole = _utf16Txt;
    auto chars    = _fontFNT->getConfig()->getChars();
    
    FNTChar     charItem;
    FontLetter  fontLetter;
    
    for (unsigned int i = 0; i < stringLen; i++) {
        char16_t c = strWhole[i];
        
        if (chars.find(c) == chars.end()) {
            charXOffset = -1;
            charYOffset = -1;
            charAdvance = -1;
        } else {
            charItem = chars.at(c);
            charXOffset = charItem.xoffset;
            charYOffset = charItem.yoffset;
            charAdvance = charItem.xadvance;
        }
        
        if (c == '\n') {
            lineIdx++;
            nextFontX = 0;
            nextFontY -= _fontFNT->getConfig()->getCommonHeight();
            if (nextFontY < _fontFNT->getConfig()->getCommonHeight()) {
                break;
            }
            lineStart = true;
            continue;
        }
        
        fontLetter.offsetX = (nextFontX + charXOffset + _horizontalKernings[i]) / contentScaleFactor;
        fontLetter.offsetY = (nextFontY - charYOffset) / contentScaleFactor;
        fontLetter.width   = charItem.width;
        fontLetter.height  = charItem.height;
        fontLetter.U       = charItem.x;
        fontLetter.V       = charItem.y;
        
        _letters.push_back(fontLetter);
        
        nextFontX += charAdvance + _horizontalKernings[i];
        
        if (longestLine < nextFontX) {
            longestLine = nextFontX;
        }
    }
    
    float lastCharWidth = fontLetter.width * contentScaleFactor;
    
    if (charAdvance < lastCharWidth) {
        _width = longestLine - charAdvance + lastCharWidth;
    } else {
        _width = longestLine;
    }
    
    _height = totalHeight;
    
    _min.setTo(0, 0);
    _max.setTo(_width, _height);
}

void LabelFNT::updateQuads() {
    
    float dx = _letters[0].offsetX + _anchorPoint.x * _width;
    float dy = _letters[0].offsetY + _anchorPoint.y * _height;
    
    for (size_t i = 0; i < _letters.size(); i++) {
        Image *image = Image::create(_fontFNT->getTexture(), _letters[i].U, _letters[i].V, _letters[i].width, _letters[i].height);
        image->setPosition(_letters[i].offsetX - dx, _letters[i].offsetY - dy, 0.0f);
        _bath->addChild(image);
    }
}

void LabelFNT::alignText() {
    // 创建Images
    createStringSprites();
    // update quads
    updateQuads();
}

void LabelFNT::updateContent() {
    
    if (_bath) {
        removeWidget(_bath);
        delete _bath;
        _bath = nullptr;
    }
    
    _bath = new BatchDisplayObject(_limitContent);
    _bath->setAutoRelease(true);
    _bath->setupTexture(_fontFNT->getTexture());
    
    addWidget(_bath);
    
    computeLinesNum();
    
    computeHorizontalKernings(_utf16Txt);
    
    alignText();
    
    _bath->setAlpha(_alpha);
    _contentDirty = false;
}

void LabelFNT::draw(bool includeChildren, Material3D* shader) {
    
    if (!_utf16Txt.empty() && _visible && inView()) {
        if (_contentDirty) {
            updateContent();
        }
    }
    
    Widget::draw(includeChildren, shader);
}

NS_MONKEY_END