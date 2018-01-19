//
//  Slider.h
//  Monkey_libs
//
//  Created by Neil on 2/11/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_Slider_h
#define Monkey_libs_Slider_h

#include "2d/entities/DisplayObject.h"
#include "2d/entities/Image.h"
#include "2d/ui/Widget.h"
#include "2d/ui/button/ButtonImage.h"
#include "2d/ui/ProgressBar.h"

NS_MONKEY_BEGIN

class Slider : public Widget {
    
public:
    
    static const std::string SLIDER_BEGAN;
    static const std::string SLIDER_END;
    static const std::string SLIDER_MOVE;
    
    Slider();
    
    virtual ~Slider();
    
    /**
     *  初始化slider
     *
     *  @param bar       bar
     *  @param ballUp    sliderball up
     *  @param ballDown  sliderball down
     *  @param progress  slidder progress
     *  @param type      texture type
     */
    void initWithTextures(const std::string &bar, const std::string &ballUp, const std::string &ballDown, const std::string &progress, Type type = Type::TEXTURE);
    
    /**
     *  设置进度
     *
     *  @param value
     */
    void setPercent(float value);
    
    /**
     *  获取进度
     *  @return
     */
    float getPercent() const;
    
protected:
    
    /**
     *  加载bar图片
     *  @param fileName bar资源名称
     *  @param type     类型
     */
    void loadBarTexture(const std::string &fileName, Type type = Type::TEXTURE);
    
    /**
     *  加载sliderball图片资源
     *
     *  @param up              正常状态
     *  @param down            按下状态
     *  @param type            图片资源格式
     */
    void loadSliderBallTextures(const std::string &up, const std::string &down, Type type = Type::TEXTURE);
    
    /**
     *  加载进度条
     *
     *  @param progress  进度条资源
     *  @param type
     */
    void loadProgressBarTexture(const std::string &progress, Type type = Type::TEXTURE);
    
    /**
     *  sliderball移动
     *  @param e
     */
    void onSliderBallMove(TouchEvent *e);
    
    /**
     *  点击sliderball
     *  @param e
     */
    void onSliderBallBegan(TouchEvent *e);
    
    /**
     *  释放sliderball
     *  @param e
     */
    void onSliderBallEnd(TouchEvent *e);
    
    Image*          _bar;           // bar
    ButtonImage*    _sliderBall;    // ball
    ProgressBar*    _progress;      // progress
    float _lastMouseX;
    float _lastMouseY;
};

NS_MONKEY_END

#endif
