//
//  GLViewIOS.cpp
//  Monkey_libs
//
//  Created by Neil on 2/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "platform/ios/GLViewIOS.h"
#include "platform/ios/EAGLView.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

GLViewIOS::GLViewIOS() : GLView() {
    
}

GLViewIOS::~GLViewIOS() {
    EAGLView *glview = (EAGLView*) _eaglview;
    [glview release];
}

/**
 *  根据eaglview初始化
 *  @param eaglview
 */
bool GLViewIOS::initWithEAGLView(void* eaglview) {
    _eaglview = eaglview;
    EAGLView *glview = (EAGLView*) _eaglview;
    _screenWidth  = [glview getWidth];
    _screenHeight = [glview getHeight];
    return true;
}

void GLViewIOS::setContentScaleFactor(float contentScaleFactor) {
    _scaleX = _scaleY = contentScaleFactor;
    EAGLView *eaglview = (EAGLView*) (_eaglview);
    [eaglview setNeedsLayout];
}

float GLViewIOS::getContentScaleFactor() const {
    EAGLView *eaglview = (EAGLView*) (_eaglview);
    float scaleFactor = [eaglview contentScaleFactor];
    return scaleFactor;
}

void GLViewIOS::swapBuffers() {
    if (!_eaglview) {
        return;
    }
    EAGLView *eaglview = (EAGLView*) (_eaglview);
    [eaglview swapBuffers];
}

void GLViewIOS::setIMEKeyboardState(bool open) {
    EAGLView *eaglview = (EAGLView*) (_eaglview);
    if (open) {
        [eaglview becomeFirstResponder];
    } else {
        [eaglview resignFirstResponder];
    }
}

NS_MONKEY_END
