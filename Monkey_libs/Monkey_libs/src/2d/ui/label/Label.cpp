//
//  Label.cpp
//  Opengl2D
//
//  Created by Neil on 24/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "App.h"

#include "2d/material/TextureMaterial2D.h"
#include "2d/utils/QuadUtils.h"
#include "2d/ui/label/Label.h"
#include "2d/entities/Image.h"

#include "core/texture/Texture2D.h"
#include "core/utils/StringUtils.h"

NS_MONKEY_BEGIN

Label* Label::create(const std::string &txt, const std::string &fontName, int fontSize, unsigned int fontColor, TextAlign align) {
    Label *label = new Label();
    label->setFontName(fontName);
    label->setFontSize(fontSize);
    label->setFontColor(fontColor);
    label->setAlign(align);
    label->setText(txt);
    label->initWithText(txt, fontName, fontSize, fontColor, align);
    return label;
}

Label::Label() :
Widget(),
_contentDirty(true),
_texture(nullptr),
_display(nullptr),
_linesNum(0),
_fontName(""),
_fontSize(12),
_fontColor(0xFFFFFF),
_align(TextAlign::CENTER)
{
    
}

Label::~Label() {
    if (_texture) {
        delete _texture;
        _texture = nullptr;
    }
}

void Label::initWithText(const std::string &txt, const std::string &fontName, int fontSize, unsigned int fontColor, TextAlign align) {
    
    float b = (fontColor & 0xFF) * 1.0f;
    float g = ((fontColor >> 8)  & 0xFF) * 1.0f;
    float r = ((fontColor >> 16) & 0xFF) * 1.0f;
    
    TextFormatter format;
    format.fontName = fontName;
    format.fontSize = fontSize;
    format.align    = align;
    format.width    = 0;
    format.height   = 0;
    format.fontFillColorR = (int)r;
    format.fontFillColorG = (int)g;
    format.fontFillColorB = (int)b;
    
    setFontColor(fontColor);
    setFontName(fontName);
    setFontSize(fontSize);
    setAlign(align);
    setText(txt);
    
    initWithTextFormat(txt, format);
}

void Label::initWithTextFormat(const std::string &txt, const TextFormatter &format) {
    Texture2D *texture = new Texture2D();
    texture->initWithString(txt.c_str(), format);
    initWithTexture(texture);
}

void Label::initWithTexture(Texture2D *texture) {
    // 设置label的宽度和高度
    _width  = texture->getWidth();
    _height = texture->getHeight();
    _min.setTo(0, 0);
    _max.setTo(_width, _height);
    
    if (_texture) {
        delete _texture;
        _texture = nullptr;
    }
    
    if (_display) {
        removeWidget(_display);
        delete _display;
        _display = nullptr;
    }
    
    _display = Image::create(texture);
    _display->setAlpha(_alpha);
    _texture      = texture;
    _contentDirty = false;
    
    addWidget(_display);
}

void Label::setText(std::string text) {
    if (text.compare(_txt)) {
        _txt = text;
        std::u16string utf16Str;
        if (StringUtils::UTF8ToUFT16(_txt, utf16Str)) {
            _utf16Txt = utf16Str;
        }
        _contentDirty = true;
    }
}

void Label::setFontName(std::string fontName) {
    if (_fontName.compare(fontName)) {
        _fontName = fontName;
        _contentDirty = true;
    }
}

void Label::setAlign(TextAlign align) {
    if (_align == align) {
        return;
    }
    _align = align;
    _contentDirty = true;
}

void Label::setFontSize(int size) {
    if (_fontSize == size) {
        return;
    }
    _fontSize = size;
    _contentDirty = true;
}

void Label::setFontColor(int color) {
    if (_fontColor == color) {
        return;
    }
    _fontColor = color;
    _contentDirty = true;
}

void Label::computeLinesNum() {
    _linesNum = 1;
    if (_utf16Txt.empty()) {
        _linesNum = 0;
        return;
    }
    size_t len = _utf16Txt.length() - 1;
    for (size_t i = 0; i < len; i++) {
        if (_utf16Txt[i] == '\n') {
            _linesNum++;
        }
    }
}

void Label::setAnchor(float x, float y) {
    if (_anchorPoint.x == x && _anchorPoint.y == y) {
        return;
    }
    _anchorPoint.setTo(x, y);
    _contentDirty = true;
}

void Label::updateContent() {
    initWithText(_txt, _fontName, _fontSize, _fontColor, _align);
    _contentDirty = false;
}

void Label::draw(bool includeChildren, Material3D* shader) {
    
    if (_txt.empty() || _utf16Txt.empty()) {
        return;
    }
    
    if (_contentDirty) {
        updateContent();
    }
    
    Widget::draw(includeChildren, shader);
}

NS_MONKEY_END