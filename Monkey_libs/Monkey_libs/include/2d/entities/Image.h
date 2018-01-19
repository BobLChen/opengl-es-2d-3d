//
//  Image.h
//  Monkey
//
//  Created by Neil on 9/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _Image_h
#define _Image_h

#include "2d/entities/DisplayObject.h"

NS_MONKEY_BEGIN

class Texture2D;
class Rectangle;
class FrameTexture;

class Image : public DisplayObject {
    
public:
    
    Image();
    ~Image();
    
    // -----------------------------------------------------------------------------------------------
    // 需要手动释放创建的对象。
    static Image* create(Texture2D *texture);
    static Image* create(Texture2D *texture, const Rectangle &rect);
    static Image* create(Texture2D *texture, float x, float y, float width, float height);
    static Image* createFrameTexture(const std::string &frameTextureName);
    static Image* create(FrameTexture *frameTexture);
    static Image* create(FrameTexture *frameTexture, float width, float height);
    static Image* create(FrameTexture *frameTexture, const Vector2D &size);
    static Image* create(const std::string &textureName);
    // -----------------------------------------------------------------------------------------------
    
    /**
     * 获取texture
     * @return texture
     */
    virtual Texture2D* getTexture();
    /**
     *  通过贴图名称创建贴图
     *  @param textureName
     */
    virtual void initWithTexture(const std::string &textureName);
    /**
     * 通过贴图初始化，贴图的大小决定了Image的大小
     * @param texture   贴图
     */
    virtual void initWithTexture(Texture2D *texture);
    /**
     * 通过指定区域初始化
     * @param texture   贴图
     * @param rect      Image的区域
     */
    virtual void initWithTexture(Texture2D *texture, const Rectangle &rect);
    /**
     * 通过贴图初始化
     * @param texture   贴图
     * @param x         贴图x坐标
     * @param y         贴图y坐标
     * @param width     Image宽度
     * @param height    Image高度
     */
    virtual void initWithTexture(Texture2D *texture, float x, float y, float width, float height);
    /**
     * 通过FrameTexture名称初始化
     * @param frameTexture
     */
    virtual void initWithFrameTexture(const std::string &frameTexture);
    /**
     * 通过FrameTexture初始化
     * @param frameTexture
     */
    virtual void initWithFrameTexture(FrameTexture *frameTexture);
    /**
     * @param frameTexture
     * @param width         指定宽度
     * @param height        指定高度
     */
    virtual void initWithFrameTexture(FrameTexture *frameTexture, float width, float height);
    /**
     * @param frameTexture
     * @param size          指定size
     */
    virtual void initWithFrameTexture(FrameTexture *frameTexture, const Vector2D &size);
    /**
     *  绘制函数，重写DisplayObject.draw
     *  @param includeChildren
     */
    virtual void draw(bool includeChildren = true, Material3D* shader = nullptr) override;
    /**
     *  设置锚点
     *  @param x
     *  @param y
     */
    virtual void setAnchor(float x, float y) override;
    
private:
    Texture2D*          _texture;
    FrameTexture*       _frameTexture;
    Rectangle           _textureRect;
};

NS_MONKEY_END

#endif
