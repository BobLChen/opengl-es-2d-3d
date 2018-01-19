//
//  GLViewIOS.h
//  Monkey_libs
//
//  Created by Neil on 2/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _GLViewIOS_h
#define _GLViewIOS_h

#include "platform/GLView.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class GLViewIOS : public GLView {
    
public:
    
    GLViewIOS();
    virtual ~GLViewIOS();
    
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
     *  present
     */
    virtual void swapBuffers();
    /**
     *  @param bOpen
     */
    virtual void setIMEKeyboardState(bool bOpen);
    /**
     *  根据eaglview初始化
     *  @param eaglview
     */
    virtual bool initWithEAGLView(void* eaglview);
    
protected:
    
};

NS_MONKEY_END

#endif
