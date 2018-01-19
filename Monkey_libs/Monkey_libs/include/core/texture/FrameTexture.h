//
//  FrameTexture.h
//  Monkey
//
//  Created by Neil on 12/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _FrameTexture_h
#define _FrameTexture_h

#include "core/geom/Rectangle.h"
#include "core/geom/Vector2D.h"
#include "core/texture/Texture2D.h"

#include <string>

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class FrameTexture {
    
public:
    
    FrameTexture();
    
    virtual ~FrameTexture();
    /**
     *
     * @param filename  图片名称
     * @param frame     图片区域
     * @param rotated   是否旋转
     * @param trimmed   ???
     * @param spriteSourceSize ???
     * @param sourceSize 图片大小
     */
    virtual void initWidth(std::string filename, const Rectangle &frame, bool rotated, bool trimmed, const Rectangle &spriteSourceSize, const Vector2D &sourceSize, Texture2D* texture);
    
    /**
     *  获取texture
     *  @return
     */
    Texture2D*              getTexture() const;
    /**
     *  获取名称
     *  @return
     */
    const std::string&      getFilename() const;
    /**
     *  获取区域
     *  @return
     */
    const Rectangle&        getFrame() const;
    /**
     *  是否旋转
     *  @return
     */
    bool                    getRotated() const;
    /**
     *  trimmed
     *  @return
     */
    bool                    getTrimmed() const;
    /**
     *  图片大小
     *  @return
     */
    const Rectangle&        getSpriteSourceSize() const;
    /**
     *  图片大小
     *  @return
     */
    const Vector2D&         getSourceSize() const;
    
private:
    
    std::string _filename;
    Rectangle   _frame;
    bool        _rotated;
    bool        _trimmed;
    Rectangle   _spriteSourceSize;
    Vector2D    _sourceSize;
    Texture2D*  _texture;
};

NS_MONKEY_END

#endif
