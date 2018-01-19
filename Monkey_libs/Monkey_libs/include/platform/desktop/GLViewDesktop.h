//
//  GLViewMac.h
//  Monkey_libs
//
//  Created by Neil on 2/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_GLViewDesktop_h
#define Monkey_libs_GLViewDesktop_h

#include "platform/GLView.h"
#include "platform/PlatformMacros.h"

#include <string>

NS_MONKEY_BEGIN

class GLViewDesktop : public GLView {
    
public:
    
    GLViewDesktop();
    
    virtual ~GLViewDesktop();
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
     *  opengl是否准备好
     *  @return
     */
    virtual bool isOpenGLReady() override;
    /**
     *  swap buffer
     */
    virtual void swapBuffers() override;
    /**
     *  设置键盘状态
     *  @param bOpen
     */
    virtual void setIMEKeyboardState(bool bOpen) override;
    /**
     *  如果是retina屏幕，该选项可以启用retina或者禁用retina。如果为非retina屏幕，该API无任何效果。
     *  @param value
     */
    virtual void enableRetina(bool value);
    /**
     *  是否启用retian
     *  @return
     */
    virtual bool isRetina();
    /**
     *  初始化window
     *  @param viewName        窗口名称
     *  @param x               x
     *  @param y               y
     *  @param width           宽度
     *  @param height          高度
     *  @param frameZoomFactor
     *  @return
     */
    bool initWithRect(const std::string& viewName, int x, int y, int width, int height);
    /**
     *  全屏window
     *  @param viewName 窗口名称
     *  @return
     */
    bool initWithFullScreen(const std::string& viewName);
    /**
     *  设置窗口名称
     *  @param viewName
     */
    void setViewName(const std::string &viewName);
    
protected:
    /**
     * 初始化glew
     */
    bool initGlew();
    // call back
    /**
     *  glfw错误
     *
     *  @param errorID   错误id
     *  @param errorDesc 错误信息
     */
    void onGLFWError(int errorID, const char* errorDesc);
    /**
     *  鼠标回调事件
     *  @param window
     *  @param button
     *  @param action 鼠标行为
     *  @param modify
     */
    void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
    /**
     *  鼠标移动回调
     *  @param window
     *  @param x      x
     *  @param y      y
     */
    void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
    /**
     *  鼠标滚轮
     *
     *  @param window
     *  @param x      x偏移
     *  @param y      y偏移
     */
    void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y);
    /**
     *  键盘
     *
     *  @param window
     *  @param key      key
     *  @param scancode
     *  @param action   action
     *  @param mods
     */
    void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    /**
     *  ???
     *
     *  @param window
     *  @param character ???
     */
    void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
    /**
     *  窗口位置改变回调函数
     *
     *  @param windows
     *  @param x       x
     *  @param y       y
     */
    void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y);
    /**
     *  改变缓冲区尺寸
     *
     *  @param window
     *  @param w      宽度
     *  @param h      高度
     */
    void onGLFWframebuffersize(GLFWwindow* window, int w, int h);
    /**
     *  窗口改变尺寸
     *  @param window
     *  @param width  宽度
     *  @param height 高度
     */
    void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height);
    /**
     * 设置viewport.
     */
    void adaptViewport();
    /**
     *  检测鼠标是否在window中
     *  @return
     */
    bool isMouseInWindow();
    
    bool _supportTouch;
    bool _isRetinaEnabled;
    bool _isRetina;
    
    GLFWwindow*  _mainWindow;
    GLFWmonitor* _monitor;
    
    std::string _viewName;
    
    float _mouseX;
    float _mouseY;
    
    int _posX;
    int _posY;
    
    friend class GLFWEventHandler;
};

NS_MONKEY_END;

#endif
