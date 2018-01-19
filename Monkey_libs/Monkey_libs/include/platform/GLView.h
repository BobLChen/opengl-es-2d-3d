#ifndef _GL_VIEW
#define _GL_VIEW

#include "core/base/GLBase.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class GLView {

public:
    /**
     *  设置缩放比例(retina)
     *  @param contentScaleFactor
     *  @return
     */
    virtual void setContentScaleFactor(float contentScaleFactor);
    /**
     *  获取缩放比
     *  @return
     */
    virtual float getContentScaleFactor() const;
    /**
     *  检测是否为retina屏
     *  @return
     */
    virtual bool isRetinaDisplay() const;
    /**
     *  清楚opengl backbuffer
     *  @param mask
     */
    virtual void clear(GLbitfield mask);
    /**
     *  设置背景色
     *  @param color
     */
    virtual void setBackgroundColor(int color);
    /**
     *  设置viewport
     *  @param x
     *  @param y
     *  @param width
     *  @param height
     */
    virtual void setViewPort(int x, int y, int width, int height);
    /**
     *  检测opengl是否已经准备完成
     *  @return
     */
    virtual bool isOpenGLReady();
    /**
     *  present
     */
    virtual void swapBuffers();
    /**
     *  @param bOpen
     */
    virtual void setIMEKeyboardState(bool bOpen);
    
protected:
    
    GLView();
    virtual ~GLView();
    
    float   _scaleX;
    float   _scaleY;
    int     _screenWidth;
    int     _screenHeight;
    int     _frameWidth;
    int     _frameHeight;
    float   _contentScaleFactor;
    
    void *_eaglview;
};

NS_MONKEY_END;


#endif