//
//  Label.h
//  Opengl2D
//
//  Created by Neil on 21/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _Label_h
#define _Label_h

#include "core/utils/TextFormatter.h"
#include "2d/ui/Widget.h"

NS_MONKEY_BEGIN

struct FontLetter {
    unsigned short charID;
    float U;
    float V;
    float width;
    float height;
    float offsetX;
    float offsetY;
    int   xAdvance;
};

class Label : public Widget {
    
public:
    
    Label();
    virtual ~Label();
    /**
     *  创建系统字体
     *
     *  @param txt       内容
     *  @param fontName  字体名称
     *  @param fontSize  字体大小
     *  @param fontColor 字体颜色
     *  @param align     对齐方式
     *  @return
     */
    static Label* create(const std::string &txt, const std::string &fontName, int fontSize = 14, unsigned int fontColor = 0xFFFFFF, TextAlign align = TextAlign::CENTER);
    /**
     * 通过Texture初始化
     * @papram texture  系统字体texture
     */
    void initWithTexture(Texture2D *texture);
    /**
     * 通过textformat初始化
     * @param txt           文本内容
     * @param format        文本格式
     */
    void initWithTextFormat(const std::string &txt, const TextFormatter &format);
    
    /**
     *  @param txt       文本内容
     *  @param fontName  字体名称
     *  @param fontSize  字体大小
     *  @param fontColor 字体颜色
     *  @param align     对齐方式
     */
    void initWithText(const std::string &txt, const std::string &fontName, int fontSize = 14, unsigned int fontColor = 0xFFFFFF, TextAlign align = TextAlign::CENTER);
    
    /**
     *  设置文本内容
     *  @param text
     */
    virtual void setText(std::string text);
    /**
     *  设置字体
     *  @param fontName
     */
    void setFontName(std::string fontName);
    /**
     *  设置对齐方式
     *  @param align
     */
    void setAlign(TextAlign align);
    /**
     *  设置字体大小
     *  @param size
     */
    void setFontSize(int size);
    /**
     *  设置字体颜色
     *  @param color
     */
    void setFontColor(int color);
    /**
     *  绘制阶段
     *  @param includeChildren
     */
    virtual void draw(bool includeChildren = false, Material3D* shader = nullptr) override;
    /**
     *  更新文本内容
     */
    virtual void updateContent();
    /**
     *  计算文本行数
     */
    virtual void computeLinesNum();
    /**
     *  设置锚点
     *  @param x                宽度百分比
     *  @param y                高度百分比
     */
    virtual void setAnchor(float x, float y);
    
protected:
    
    std::u16string  _utf16Txt;
    std::string     _txt;
    bool            _contentDirty;
    int             _linesNum;
    
    DisplayObject*  _display;
    Texture2D*      _texture;
    
private:
    std::string     _fontName;
    int             _fontSize;
    unsigned int    _fontColor;
    TextAlign       _align;
};

NS_MONKEY_END

#endif
