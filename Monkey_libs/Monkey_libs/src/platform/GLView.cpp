//
//  GLView.cpp
//  Monkey_libs
//
//  Created by Neil on 2/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "platform/GLView.h"
#include "platform/PlatformMacros.h"
#include "core/utils/Log.h"

NS_MONKEY_BEGIN

GLView::GLView() :
_scaleX(1.0f),
_scaleY(1.0f),
_screenHeight(0.0f),
_screenWidth(0.0f),
_contentScaleFactor(1.0f),
_eaglview(nullptr)
{
    
}

GLView::~GLView() {
  
}

void GLView::setContentScaleFactor(float contentScaleFactor) {
    _contentScaleFactor = contentScaleFactor;
}

float GLView::getContentScaleFactor() const {
    return _contentScaleFactor;
}

bool GLView::isRetinaDisplay() const {
    return getContentScaleFactor() == 2.0;
}

void GLView::clear(GLbitfield mask) {
    if (_eaglview) {
        glClear(mask);
    }
}

void GLView::setBackgroundColor(int color) {
    if (!_eaglview) {
        return;
    }
    float b = (color & 0xFF) * 1.0f / 0xFF;
    float g = ((color >> 8)  & 0xFF) * 1.0f / 0xFF;
    float r = ((color >> 16) & 0xFF) * 1.0f / 0xFF;
    
    glClearColor(r, g, b, 1.0f);
}

void GLView::setViewPort(int x, int y, int width, int height) {
    if (!_eaglview) {
        return;
    }
    _screenWidth = width;
    _screenHeight = height;
    glViewport(x, y, width, height);
}

bool GLView::isOpenGLReady() {
    return _eaglview != nullptr;
}

void GLView::swapBuffers() {
    
}

void GLView::setIMEKeyboardState(bool bOpen) {
    
}

NS_MONKEY_END
