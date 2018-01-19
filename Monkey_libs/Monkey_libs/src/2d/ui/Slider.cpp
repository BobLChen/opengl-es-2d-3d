//
//  Slider.cpp
//  Monkey_libs
//
//  Created by Neil on 2/11/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/ui/Slider.h"
#include "core/event/TouchEvent.h"
#include "core/utils/Log.h"
#include "core/utils/Input3D.h"

NS_MONKEY_BEGIN

const std::string Slider::SLIDER_BEGAN = "SLIDER_BEGAN";
const std::string Slider::SLIDER_END   = "SLIDER_END";
const std::string Slider::SLIDER_MOVE  = "SLIDER_MOVE";

Slider::Slider() :
Widget(),
_bar(nullptr),
_sliderBall(nullptr),
_progress(nullptr),
_lastMouseX(0.0f),
_lastMouseY(0.0f)
{
    
}

Slider::~Slider() {
    
}

void Slider::initWithTextures(const std::string &bar, const std::string &ballUp, const std::string &ballDown, const std::string &progress, Type type) {
    
    loadBarTexture(bar, type);
    loadProgressBarTexture(progress, type);
    loadSliderBallTextures(ballUp, ballDown, type);
    // 设置组件位置
    _bar->setAnchor(0.0f, 0.5f);        // bar摆到中间
    _bar->setPosition(_sliderBall->getWidth()/2, -_height/2, 0.0f);
    _progress->setAnchor(0.0f, 0.5f);   //
    _progress->setPosition(_sliderBall->getWidth()/2, -_height/2, 0.0f);
    _sliderBall->setPosition(0, 0, 0);
    // 启用鼠标
    enableMouse(true);
    // 设置percent
    setPercent(0.0f);
}

void Slider::loadBarTexture(const std::string &fileName, Type type) {
    if (_bar) {
        removeWidget(_bar);
        delete _bar;
        _bar = nullptr;
    }
    switch (type) {
        case Widget::Type::TEXTURE:
            _bar = Image::create(fileName);
            break;
        case Widget::Type::TEXTURE_FRAME:
            _bar = Image::createFrameTexture(fileName);
            break;
        default:
            return;
            break;
    }
    addWidget(_bar);
    _width  = _bar->getWidth();
    _min.setTo(0, 0);
    _max.setTo(_width, _height);
}

void Slider::loadSliderBallTextures(const std::string &up, const std::string &down, Type type) {
    if (_sliderBall) {
        _sliderBall->removeEventListener(TouchEvent::TOUCH_MOVE, this, EVENT_CALLBACK(Slider::onSliderBallMove));
        _sliderBall->removeEventListener(TouchEvent::TOUCH_BEGAN, this, EVENT_CALLBACK(Slider::onSliderBallBegan));
        _sliderBall->removeEventListener(TouchEvent::TOUCH_END, this, EVENT_CALLBACK(Slider::onSliderBallEnd));
        
        removeWidget(_sliderBall);
        delete _sliderBall;
        _sliderBall = nullptr;
    }
    _sliderBall = new ButtonImage();
    _sliderBall->initWithImage(up, down, type);
    // 监听事件
    _sliderBall->addEventListener(TouchEvent::TOUCH_MOVE, this, EVENT_CALLBACK(Slider::onSliderBallMove));
    _sliderBall->addEventListener(TouchEvent::TOUCH_BEGAN, this, EVENT_CALLBACK(Slider::onSliderBallBegan));
    _sliderBall->addEventListener(TouchEvent::TOUCH_END, this, EVENT_CALLBACK(Slider::onSliderBallEnd));
    
    _height = _sliderBall->getHeight();
    _max.setTo(_width, _height);
    
    addWidget(_sliderBall);
}

void Slider::loadProgressBarTexture(const std::string &progress, Type type) {
    if (_progress) {
        removeWidget(_progress);
        delete _progress;
        _progress = nullptr;
    }
    _progress = new ProgressBar();
    _progress->initWithTexture(progress, type);
    _progress->setTotalLength(_width);
    addWidget(_progress);
}

void Slider::setPercent(float value) {
    if (value < 0.0f) {
        value = 0.0f;
    } else if (value > 1.0f) {
        value = 1.0f;
    }
    _progress->setPercent(value);
    _sliderBall->setPosition(_width * value, 0.0f, 0.0f);
}

float Slider::getPercent() const {
    return _progress->getPercent();
}

void Slider::onSliderBallMove(monkey::TouchEvent *e) {
    float deltaX = e->points[0].x - _lastMouseX;
    float slideX = _sliderBall->getX() + deltaX;
    float percent = slideX / _width;
    setPercent(percent);
    _lastMouseX = e->points[0].x;
    
    Event sliderEvent(SLIDER_MOVE);
    dispatchEvent(sliderEvent);
}

void Slider::onSliderBallBegan(monkey::TouchEvent *e) {
    _lastMouseX = e->points[0].x;
    _lastMouseY = e->points[0].y;
    
    Event sliderBegan(SLIDER_BEGAN);
    dispatchEvent(sliderBegan);
}

void Slider::onSliderBallEnd(monkey::TouchEvent *e) {
    Event sliderEnd(SLIDER_END);
    dispatchEvent(sliderEnd);
}

NS_MONKEY_END