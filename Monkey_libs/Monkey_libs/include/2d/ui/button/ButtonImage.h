//
//  ButtonImage.h
//  Monkey
//
//  Created by Neil on 27/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _ButtonImage_h
#define _ButtonImage_h

#include "2d/ui/button/Button.h"
#include "2d/entities/Image.h"

NS_MONKEY_BEGIN

class ButtonImage : public Button {
    
public:
    
    ButtonImage();
    virtual ~ButtonImage();
    
    /**
     *  初始化
     *
     *  @param normal
     *  @param selected
     *  @param disable
     *  @param type     type(Texture Or TextureFrame)
     */
    virtual void initWithImage(const std::string &up, const std::string &down, Type type = Type::TEXTURE);
    
protected:
    /**
     *  设置按钮状态
     *  @param stats
     */
    virtual void setButtonStatus(ButtonStats stats);
    /**
     * 初始化button渲染的必要组件
     */
    void initButtonRender();
    /**
     *  初始化NormalImage
     *  @param name 贴图名称
     *  @param type  贴图类型
     */
    void initUpImage(const std::string &name, ButtonImage::Type type);
    /**
     *  初始化DisableImage
     *  @param name 贴图名称
     *  @param type  贴图类型
     */
    void initDownImage(const std::string &name, ButtonImage::Type type);
    
    Image*  _upImage;
    Image*  _downImage;
};

NS_MONKEY_END

#endif
