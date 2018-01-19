//
//  LabelFNT.h
//  Monkey
//
//  Created by Neil on 25/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _LabelFNT_h
#define _LabelFNT_h

#include "2d/ui/font/FontFNT.h"
#include "2d/ui/label/Label.h"
#include "2d/entities/BatchDisplayObject.h"

NS_MONKEY_BEGIN

#define MAX_CONTENT_SIZE 50

class LabelFNT : public Label {
    
public:
    
    LabelFNT(int maxContent = MAX_CONTENT_SIZE);
    ~LabelFNT();
    
    /**
     *  创建FNTLabel
     *  @param fntFile fnt文件路径
     *  @param txt     内容
     *  @return
     */
    static LabelFNT* create(const std::string &fntFile, const std::string &txt, int maxContent = MAX_CONTENT_SIZE);
    
    /**
     *  设置字体
     *  @param fontFNT
     */
    void setFontFNT(FontFNT *fontFNT);
    /**
     *  绘制
     *  @param includeChildren 是否绘制children
     *  @param shader          shader
     */
    virtual void draw(bool includeChildren = false, Material3D* shader = nullptr) override;
    /**
     *  更新文本内容
     */
    virtual void updateContent() override;
    /**
     *  计算水平字距
     *  @param txt
     */
    virtual void computeHorizontalKernings(const std::u16string &txt);
    /**
     *  排序text
     */
    virtual void alignText();
    /**
     *  创建文本quad
     */
    virtual void createStringSprites();
    /**
     *  创建quad
     */
    virtual void updateQuads();
    
private:
    int                     _limitContent;
    BatchDisplayObject*     _bath;
    std::vector<FontLetter> _letters;
    FontFNT*                _fontFNT;
    int*                    _horizontalKernings;
};

NS_MONKEY_END

#endif
