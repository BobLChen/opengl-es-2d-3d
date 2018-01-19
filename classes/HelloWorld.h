//
//  HelloWorld.h
//  HelloMonkey
//
//  Created by Neil on 4/11/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __HelloMonkey__HelloWorld__
#define __HelloMonkey__HelloWorld__

#include "2d/scene/Scene2D.h"
#include "2d/entities/MovieClip.h"
#include "core/geom/Vector3D.h"

NS_MONKEY_BEGIN

class HellWorld : public Scene2D {
    
public:
    
    HellWorld();
    ~HellWorld();
    
    /**
     * 初始化
     */
    void init();
    /**
     *  进入帧循环
     *  @param e
     */
    void onEnterFrame(Event *e);
    
private:
    
    /**
     *  更新背景
     *  @param advanceTime
     */
    void moveBackground(float advanceTime);
    /**
     *  更新鸟
     *  @param advanceTime
     */
    void updateBird(float advanceTime);
    /**
     *  更新水管
     *  @param advanceTime
     */
    void updatePipes(float advanceTime);
    /**
     *  clamp
     *
     *  @param min   min
     *  @param max   max
     *  @param value value
     *
     *  @return value
     */
    float clamp(float min, float max, float value);
    /**
     *  触摸屏幕
     *  @param e
     */
    void onTouchScreen(TouchEvent &e);
    
    std::vector<DisplayObject*> _lands; // 地板
    std::vector<DisplayObject*> _skys;  // 天空
    std::vector<DisplayObject*> _pipes; // 水管
    
    Vector3D _temp;
    float    _speed;
    float    _lastTime;
    float    _velocity;  // 重力
    float    _pipTick;
    
    MovieClip* _bird;
};

NS_MONKEY_END

#endif /* defined(__HelloMonkey__HelloWorld__) */
