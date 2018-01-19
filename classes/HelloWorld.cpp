//
//  HelloWorld.cpp
//  HelloMonkey
//
//  Created by Neil on 4/11/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "HelloWorld.h"
#include "App.h"
#include "2d/entities/Quad.h"
#include "2d/scene/Scene2D.h"
#include "2d/entities/Image.h"
#include "core/texture/TextureAtlas.h"
#include "core/utils/Log.h"
#include "2d/ui/button/ButtonImage.h"
#include "2d/ui/Slider.h"
#include "2d/entities/MovieClip.h"

NS_MONKEY_BEGIN

static float INTERVAL = 1.0f;

HellWorld::HellWorld() :
Scene2D(),
_speed(30.0f),
_lastTime(0.0f),
_bird(nullptr),
_pipTick(1.0f),
_velocity(0.0f)
{
    init();
}

HellWorld::~HellWorld() {
    
}

void HellWorld::init() {
    
    _speed = 240; // 速度240像素每秒
    
    App::getInstance()->setBackcolor(0xFF00FF);
    
    float screenWidth  = App::getInstance()->getWidth();
    float screenHeight = App::getInstance()->getHeight();
    // 载入资源
    TextureAtlas::getInstance()->addTextureAtlasWithJson("flappbird.json");
    // 添加背景
    Image *background = Image::create("background.png");
    background->setScale(2, 2, 2);
    addChild(background);
    // 初始化地板以及天空
    for (int i = 0; i < 10; i++) {
        Image *land = Image::createFrameTexture("land.png");
        land->setScale(1, 1, 1);
        land->setPosition(i * land->getWidth(), -screenHeight + land->getHeight(), -1.0f);
        addChild(land);
        _lands.push_back(land);
        
        Image *sky = Image::createFrameTexture("sky.png");
        sky->setPosition(i * sky->getWidth(), land->getY() + sky->getHeight() - 10, 0);
        addChild(sky);
        _skys.push_back(sky);
    }
    // 初始化水管
    // 初始化鸟
    _bird = new MovieClip();
    for (int i = 1; i < 5; i++) {
        char str[50];
        sprintf(str, "bird-0%d.png", i);
        std::string frame(str);
        _bird->addFrame(frame, MovieClip::Type::TEXTURE_FRAME);
    }
    _bird->setPosition(screenWidth/2, -screenHeight/2, 0);
    _bird->setFps(15);
    _bird->play();
    addChild(_bird);
    
    _lastTime = App::getInstance()->getRunningTime();
    
    addEventListener(TouchEvent::TOUCH_BEGAN, this, EVENT_CALLBACK(HellWorld::onTouchScreen));
    addEventListener(Scene2D::RENDER_EVENT, this, EVENT_CALLBACK(HellWorld::onEnterFrame));
}

void HellWorld::onEnterFrame(monkey::Event *e) {
    float currentTime = App::getInstance()->getRunningTime();
    
    moveBackground(currentTime - _lastTime);
    updateBird(currentTime - _lastTime);
    updatePipes(currentTime - _lastTime);
    
    _lastTime = currentTime;
}

void HellWorld::updatePipes(float advanceTime) {
    _pipTick += advanceTime;
    
    // 产生一对水管
    if (_pipTick >= INTERVAL) {
        float w = App::getInstance()->getWidth();
        float h = App::getInstance()->getHeight();
        // 上
        Image *up = Image::createFrameTexture("PipeUp.png");
        up->setScaleY(2.0f);
        up->setPosition(w + w/10 * randomf(), -h / 2 - randomf() * h / 6, 0.0f);
        addChild(up);
        _pipes.push_back(up);
        // 下
        Image *down = Image::createFrameTexture("PipeDown.png");
        down->setScaleY(2.0f);
        down->setPosition(w + w/10 * randomf(), randomf() * h / 4, 0.0);
        addChild(down);
        _pipes.push_back(down);
        
        _pipTick = 0.0f;
    }
    
    float speed = advanceTime * _speed;
    for (auto iter = _pipes.begin(); iter != _pipes.end(); iter++) {
        (*iter)->setX((*iter)->getX() - (int)speed);
        
        if ((*iter)->getX() + (*iter)->getWidth() < 0) {
            removeChild((*iter));
            delete (*iter);
            _pipes.erase(iter);
        }
    }
}

void HellWorld::moveBackground(float advanceTime) {
    float speed = advanceTime * _speed;
    // 滚动背景
    for (auto iter = _skys.begin(); iter != _skys.end(); iter++) {
        (*iter)->getPosition(_temp);
        (*iter)->setX((*iter)->getX() - (int)speed);
        if ((*iter)->getX() + (*iter)->getWidth() < 0) {
            (*iter)->setX((*iter)->getWidth() * (_skys.size() - 1));
        }
    }
    // 滚动陆地
    for (auto iter = _lands.begin(); iter != _lands.end(); iter++) {
        (*iter)->getPosition(_temp);
        (*iter)->setX((*iter)->getX() - (int)speed);
        if ((*iter)->getX() + (*iter)->getWidth() < 0) {
            (*iter)->setX((*iter)->getWidth() * (_lands.size() - 1));
        }
    }
}

float HellWorld::clamp(float min, float max, float value) {
    if (value > max) {
        return max;
    } else if (value < min) {
        return min;
    } else {
        return value;
    }
}

void HellWorld::updateBird(float advanceTime) {
    // 让鸟一直往下掉
    _velocity -= 0.7f;
    float rotation = clamp(-90, 90, _velocity * (_velocity < 0 ? 5 : 3));
    // 更新鸟得方向
    _bird->setRotation(0, 0, rotation);
    _bird->setY(_bird->getY() + _velocity);
    if (_velocity < -7.0f) {
        _velocity = -7.0f;
    }
}

void HellWorld::onTouchScreen(monkey::TouchEvent &e) {
    _velocity = 10.0f;
}

NS_MONKEY_END
