//
//  App.cpp
//  Opengl2D
//
//  Created by Neil on 3/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

// TODO:change to cpp

#include "App.h"

#include "core/utils/Log.h"
#include "core/geom/Matrix3D.h"
#include "core/texture/Texture2D.h"
#include "core/texture/TextureAtlas.h"
#include "core/scene/Scene.h"

#include "platform/GLView.h"
#include "platform/FileUtils.h"
#include "platform/PlatformMacros.h"

#include "core/event/TouchEvent.h"

#include "core/event/TouchEvent.h"
#include "core/utils/Input3D.h"

#include "2d/scene/Scene2D.h"
#include "2d/entities/DisplayObject.h"
#include "2d/ui/label/LabelFNT.h"

#include <algorithm>

NS_MONKEY_BEGIN

/**
 *  version
 *  @return 版本号
 */
const char* version() {
    return "beta 1.0";
}
// _instance
static App *_instance = nullptr;

App::App() : EventDispatcher() {}

App::~App() {
    if (_status) {
        delete _status;
    }
}

App* App::getInstance() {
    if (!_instance) {
        _instance = new App();
        _instance->init();
    }
    return _instance;
}

float App::getRunningTime() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return (float) (( now.tv_sec - start_time.tv_sec)
                               + (0.000001 * (now.tv_usec - start_time.tv_usec)) );
}

bool App::init() {
    
    _fps        = 60;
    _showStats  = true;
    _status     = nullptr;
    _glview     = nullptr;
    _paused     = false;
    _width      = -1;
    _height     = -1;
    _fpsFrame   = 0;
    _fpsTime    = 0;
    _scaleFactor= 1.0f;
    _enbaleBlend        = false;
    _enableDepthTest    = false;
    _enabelStencilTest  = false;
    
    gettimeofday(&start_time, NULL);
    Texture2D::setDefaultPixelFormat(Texture2D::PixelFormat::RGBA8888);
    
    _preTime = getRunningTime();
    return true;
}

float App::getFps() {
    return _fps;
}

void App::setFps(float value) {
    _fps = value;
}

bool App::isShowStats() {
    return _showStats;
}

void App::setVisiableStats(bool value) {
    _showStats = value;
}

GLView* App::getOpenGLView() {
    return _glview;
}

void App::setOpenGLView(GLView *glview) {
    
    if (!glview) {
        LOGE("GLView should not be NULL");
        return;
    }
    
    if (_glview != glview) {
        _glview = glview;
        // get gpu params
        _valueDict["vendor"]    = Value((const char*)glGetString(GL_VENDOR));           //
        _valueDict["renderer"]  = Value((const char*)glGetString(GL_RENDERER));         // gpu
        _valueDict["version"]   = Value((const char*)glGetString(GL_VERSION));          // gl version
        _extensions             = (char *)glGetString(GL_EXTENSIONS);                   // extensions
        
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_maxTextureUnits);
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        glGetIntegerv(GL_MAX_SAMPLES_APPLE, &_maxSamplesAllowed);
        _valueDict["gl.max_samples_allowed"] = Value((int)_maxSamplesAllowed);
#endif
        
        _valueDict["gl.max_texture_size"]    = Value((int)_maxTextureSize);
        _valueDict["gl.max_texture_units"]   = Value((int)_maxTextureUnits);
        
        enableBlend(true);
        enableDepthTest(true);
        enableStencilTest(true);
    }
    
}

int App::getMaxTextureSize() {
    return _maxTextureSize;
}

int App::getMaxTextureSamples() {
    return _maxSamplesAllowed;
}

int App::getMaxTextureUnits() {
    return _maxTextureUnits;
}

bool App::isPaused() {
    return _paused;
}

void App::pause() {
    _paused = true;
}

void App::resume() {
    _paused = false;
}

void App::setViewport(int x, int y, int width, int height) {
#if CC_TARGET_PLATFORM != CC_PLATFORM_MAC || CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM != CC_PLATFORM_LINUX
    if (_glview) {
        glViewport(x, y, width, height);
    }
#endif
    for (auto iter = _scene2DList.begin(); iter != _scene2DList.end(); iter++) {
        (*iter)->setViewport(x, y, width, height);
    }
    for (auto iter = _scene3DList.begin(); iter != _scene3DList.end(); iter++) {
        (*iter)->setViewport(x, y, width, height);
    }
    _width = width;
    _height = height;
}

int App::getWidth() {
    return _width;
}

int App::getHeight() {
    return _height;
}

void App::addScene2D(Scene2D *scene2D) {
    auto iter = std::find(_scene2DList.begin(), _scene2DList.end(), scene2D);
    if (iter == _scene2DList.end()) {
        _scene2DList.push_back(scene2D);
    }
}

void App::removeScene2D(monkey::Scene2D *scene2D) {
    auto iter = std::find(_scene2DList.begin(), _scene2DList.end(), scene2D);
    _scene2DList.erase(iter);
}

void App::addScene3D(Scene *scene) {
    auto iter = std::find(_scene3DList.begin(), _scene3DList.end(), scene);
    if (iter == _scene3DList.end()) {
        _scene3DList.push_back(scene);
    }
}

void App::removeScene3D(Scene *scene) {
    auto iter = std::find(_scene3DList.begin(), _scene3DList.end(), scene);
    _scene3DList.erase(iter);
}

void App::enableBlend(bool value) {
    if (_glview) {
        if (value) {
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }
        _enbaleBlend = value;
    }
}

void App::enableDepthTest(bool value) {
    if (_glview) {
        if (value) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
        _enableDepthTest = value;
    }
}

void App::enableStencilTest(bool value) {
    if (_glview) {
        if (value) {
            glEnable(GL_STENCIL_TEST);
        } else {
            glEnable(GL_STENCIL_TEST);
        }
        _enabelStencilTest = value;
    }
}

bool App::isEnableBlend() {
    return _enbaleBlend;
}

bool App::isEnableDepth() {
    return _enableDepthTest;
}

bool App::isEnableStencil() {
    return _enabelStencilTest;
}

void App::setBackcolor(int color) {
    if (_glview) {
        _glview->setBackgroundColor(color);
    }
}

void App::update() {
    if (_glview) {
    	
        if (_paused) {
            return;
        }
        
        Input3D::update();
        
        if (isEnableDepth() && isEnableStencil()) {
            _glview->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        } else if (isEnableDepth() && !isEnableStencil()) {
            _glview->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        } else if (!isEnableDepth() && isEnableStencil()) {
            _glview->clear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        } else {
            _glview->clear(GL_COLOR_BUFFER_BIT);
        }
        
        // time
        float currentTime = getRunningTime();
        float deltaTime   = currentTime - _preTime;
        _fpsTime += deltaTime;
        _fpsFrame++;
        
        // fps
        App::getInstance()->drawcalls = 0;
        App::getInstance()->vertices  = 0;
        App::getInstance()->triangles = 0;
        
        // render 3d
        for (auto iter = _scene3DList.begin(); iter != _scene3DList.end(); iter++) {
            (*iter)->enterScene(currentTime - _preTime);
        }
        // render 2d
        for (auto iter = _scene2DList.begin(); iter != _scene2DList.end(); iter++) {
            (*iter)->enterScene(currentTime - _preTime);
        }
        
        _preTime = currentTime;
        
        if (_fpsTime >= 1.0f) {
            _fps = _fpsFrame;
            _fpsFrame = 0;
            _fpsTime  = 0;
            
            if (_showStats) {
                char buf[1024];
                sprintf(buf, "FPS:%.2f\nTRI:%d\nDRA:%d\n", _fps, triangles, drawcalls);
                std::string statusText(buf);
                _status->setText(statusText);
                _status->setPosition(0, 0, 0);
            }
        }
        
        if (_showStats) {
            if (_status == nullptr) {
                _status = LabelFNT::create("FPS.fnt", "0");
            }
            _status->setPosition(0, 0, 0);
            _status->draw();
        }
        
        _glview->swapBuffers();
    }
}

bool App::dispose() {
    pause();
    
    FileUtils::getInstance()->dispose();
    TextureAtlas::getInstance()->dispose();
    
    delete _instance;
    return true;
}

void App::setScaleFactor(float value) {
    _scaleFactor = value;
}

float App::getScaleFactor() {
    return _scaleFactor;
}

void App::handleTouchesBegan(monkey::TouchEvent &event) {
    for (auto iter = _scene2DList.begin(); iter != _scene2DList.end(); iter++) {
        (*iter)->handleTouchesBegan(event);
    }
    for (auto iter = _scene3DList.begin(); iter != _scene3DList.end(); iter++) {
        (*iter)->handleTouchesBegan(event);
    }
}

void App::handleTouchesEnd(monkey::TouchEvent &event) {
    for (auto iter = _scene2DList.begin(); iter != _scene2DList.end(); iter++) {
        (*iter)->handleTouchesEnd(event);
    }
    for (auto iter = _scene3DList.begin(); iter != _scene3DList.end(); iter++) {
        (*iter)->handleTouchesEnd(event);
    }
}

void App::handleTouchesMove(monkey::TouchEvent &event) {
    for (auto iter = _scene2DList.begin(); iter != _scene2DList.end(); iter++) {
        (*iter)->handleTouchMove(event);
    }
    for (auto iter = _scene3DList.begin(); iter != _scene3DList.end(); iter++) {
        (*iter)->handleTouchMove(event);
    }
}

void App::handleMouseWheelEvent(TouchEvent &event) {
    for (auto iter = _scene2DList.begin(); iter != _scene2DList.end(); iter++) {
        (*iter)->handleMouseWheel(event);
    }
    for (auto iter = _scene3DList.begin(); iter != _scene3DList.end(); iter++) {
        (*iter)->handleMouseWheel(event);
    }
}

void App::handleKeyDownEvent(monkey::KeyboardEvent &event) {
    for (auto iter = _scene2DList.begin(); iter != _scene2DList.end(); iter++) {
        (*iter)->handleKeyDown(event);
    }
    for (auto iter = _scene3DList.begin(); iter != _scene3DList.end(); iter++) {
        (*iter)->handleKeyDown(event);
    }
}

void App::handleKeyUpEvent(monkey::KeyboardEvent &event) {
    for (auto iter = _scene2DList.begin(); iter != _scene2DList.end(); iter++) {
        (*iter)->handleKeyUp(event);
    }
    for (auto iter = _scene3DList.begin(); iter != _scene3DList.end(); iter++) {
        (*iter)->handleKeyUp(event);
    }
}

NS_MONKEY_END
