//
//  MovieClip.h
//  Monkey_libs
//
//  Created by Neil on 5/11/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_MovieClip_h
#define Monkey_libs_MovieClip_h

#include "2d/entities/DisplayObject.h"

NS_MONKEY_BEGIN

class MovieClip : public DisplayObject {

public:
    
    enum class Type {
        TEXTURE,
        TEXTURE_FRAME
    };
    
    MovieClip();
    
    virtual ~MovieClip();
    
    /**
     *  更新transform
     *  @param includeChildren
     */
    virtual void updateTransforms(bool includeChildren = true) override;
    /**
     *  添加一帧
     *  @param frame
     *  @param type
     */
    virtual void addFrame(const std::string &frame, Type type = Type::TEXTURE);
    /**
     *  绘制
     *  @param includeChildren 是否一并绘制子节点
     *  @param shader          shader
     */
    virtual void draw(bool includeChildren = true, Material3D* shader = nullptr) override;
    /**
     *  设置当前帧
     *  @param value
     */
    virtual void setCurrentFrame(float value) override;
    
protected:
    
    std::vector<DisplayObject*> _frames;
    DisplayObject*              _currentFrameDisp;
    
};

NS_MONKEY_END

#endif
