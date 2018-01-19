//
//  GLViewMac.cpp
//  Monkey_libs
//
//  Created by Neil on 1/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "glfw3.h"
#include "platform/desktop/GLViewDesktop.h"
#include "platform/PlatformMacros.h"
#include "core/utils/Log.h"
#include "core/event/KeyboardEvent.h"
#include "core/utils/Input3D.h"
#include "core/event/TouchEvent.h"
#include "core/event/KeyboardEvent.h"

#include "App.h"

#include <float.h>
#include <math.h>
#include <unordered_map>

NS_MONKEY_BEGIN

class GLFWEventHandler {
    
public:
    
    static void onGLFWError(int errorID, const char* errorDesc) {
        if (_view)
            _view->onGLFWError(errorID, errorDesc);
    }
    
    static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify) {
        if (_view)
            _view->onGLFWMouseCallBack(window, button, action, modify);
    }
    
    static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y) {
        if (_view)
            _view->onGLFWMouseMoveCallBack(window, x, y);
    }
    
    static void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y) {
        if (_view)
            _view->onGLFWMouseScrollCallback(window, x, y);
    }
    
    static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (_view)
            _view->onGLFWKeyCallback(window, key, scancode, action, mods);
    }
    
    static void onGLFWCharCallback(GLFWwindow* window, unsigned int character) {
        if (_view)
            _view->onGLFWCharCallback(window, character);
    }
    
    static void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y) {
        if (_view)
            _view->onGLFWWindowPosCallback(windows, x, y);
    }
    
    static void onGLFWframebuffersize(GLFWwindow* window, int w, int h){
        if (_view)
            _view->onGLFWframebuffersize(window, w, h);
    }
    
    static void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height) {
        if (_view)
            _view->onGLFWWindowSizeFunCallback(window, width, height);
    }
    
    static void setGLView(GLViewDesktop* view) {
        _view = view;
    }
    
private:
    static GLViewDesktop* _view;
};

GLViewDesktop* GLFWEventHandler::_view = nullptr;

////////////////////////////////////////////////////

struct keyCodeItem {
    int glfwKeyCode;
    KeyboardEvent::KeyCode keyCode;
};

static std::unordered_map<int, KeyboardEvent::KeyCode> g_keyCodeMap;

static keyCodeItem g_keyCodeStructArray[] = {
    /* The unknown key */
    { GLFW_KEY_UNKNOWN         , KeyboardEvent::KeyCode::KEY_NONE          },
    
    /* Printable keys */
    { GLFW_KEY_SPACE           , KeyboardEvent::KeyCode::KEY_SPACE         },
    { GLFW_KEY_APOSTROPHE      , KeyboardEvent::KeyCode::KEY_APOSTROPHE    },
    { GLFW_KEY_COMMA           , KeyboardEvent::KeyCode::KEY_COMMA         },
    { GLFW_KEY_MINUS           , KeyboardEvent::KeyCode::KEY_MINUS         },
    { GLFW_KEY_PERIOD          , KeyboardEvent::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_SLASH           , KeyboardEvent::KeyCode::KEY_SLASH         },
    { GLFW_KEY_0               , KeyboardEvent::KeyCode::KEY_0             },
    { GLFW_KEY_1               , KeyboardEvent::KeyCode::KEY_1             },
    { GLFW_KEY_2               , KeyboardEvent::KeyCode::KEY_2             },
    { GLFW_KEY_3               , KeyboardEvent::KeyCode::KEY_3             },
    { GLFW_KEY_4               , KeyboardEvent::KeyCode::KEY_4             },
    { GLFW_KEY_5               , KeyboardEvent::KeyCode::KEY_5             },
    { GLFW_KEY_6               , KeyboardEvent::KeyCode::KEY_6             },
    { GLFW_KEY_7               , KeyboardEvent::KeyCode::KEY_7             },
    { GLFW_KEY_8               , KeyboardEvent::KeyCode::KEY_8             },
    { GLFW_KEY_9               , KeyboardEvent::KeyCode::KEY_9             },
    { GLFW_KEY_SEMICOLON       , KeyboardEvent::KeyCode::KEY_SEMICOLON     },
    { GLFW_KEY_EQUAL           , KeyboardEvent::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_A               , KeyboardEvent::KeyCode::KEY_A             },
    { GLFW_KEY_B               , KeyboardEvent::KeyCode::KEY_B             },
    { GLFW_KEY_C               , KeyboardEvent::KeyCode::KEY_C             },
    { GLFW_KEY_D               , KeyboardEvent::KeyCode::KEY_D             },
    { GLFW_KEY_E               , KeyboardEvent::KeyCode::KEY_E             },
    { GLFW_KEY_F               , KeyboardEvent::KeyCode::KEY_F             },
    { GLFW_KEY_G               , KeyboardEvent::KeyCode::KEY_G             },
    { GLFW_KEY_H               , KeyboardEvent::KeyCode::KEY_H             },
    { GLFW_KEY_I               , KeyboardEvent::KeyCode::KEY_I             },
    { GLFW_KEY_J               , KeyboardEvent::KeyCode::KEY_J             },
    { GLFW_KEY_K               , KeyboardEvent::KeyCode::KEY_K             },
    { GLFW_KEY_L               , KeyboardEvent::KeyCode::KEY_L             },
    { GLFW_KEY_M               , KeyboardEvent::KeyCode::KEY_M             },
    { GLFW_KEY_N               , KeyboardEvent::KeyCode::KEY_N             },
    { GLFW_KEY_O               , KeyboardEvent::KeyCode::KEY_O             },
    { GLFW_KEY_P               , KeyboardEvent::KeyCode::KEY_P             },
    { GLFW_KEY_Q               , KeyboardEvent::KeyCode::KEY_Q             },
    { GLFW_KEY_R               , KeyboardEvent::KeyCode::KEY_R             },
    { GLFW_KEY_S               , KeyboardEvent::KeyCode::KEY_S             },
    { GLFW_KEY_T               , KeyboardEvent::KeyCode::KEY_T             },
    { GLFW_KEY_U               , KeyboardEvent::KeyCode::KEY_U             },
    { GLFW_KEY_V               , KeyboardEvent::KeyCode::KEY_V             },
    { GLFW_KEY_W               , KeyboardEvent::KeyCode::KEY_W             },
    { GLFW_KEY_X               , KeyboardEvent::KeyCode::KEY_X             },
    { GLFW_KEY_Y               , KeyboardEvent::KeyCode::KEY_Y             },
    { GLFW_KEY_Z               , KeyboardEvent::KeyCode::KEY_Z             },
    { GLFW_KEY_LEFT_BRACKET    , KeyboardEvent::KeyCode::KEY_LEFT_BRACKET  },
    { GLFW_KEY_BACKSLASH       , KeyboardEvent::KeyCode::KEY_BACK_SLASH    },
    { GLFW_KEY_RIGHT_BRACKET   , KeyboardEvent::KeyCode::KEY_RIGHT_BRACKET },
    { GLFW_KEY_GRAVE_ACCENT    , KeyboardEvent::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_1         , KeyboardEvent::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_2         , KeyboardEvent::KeyCode::KEY_NONE          },
    
    /* Function keys */
    { GLFW_KEY_ESCAPE          , KeyboardEvent::KeyCode::KEY_ESCAPE        },
    { GLFW_KEY_ENTER           , KeyboardEvent::KeyCode::KEY_KP_ENTER      },
    { GLFW_KEY_TAB             , KeyboardEvent::KeyCode::KEY_TAB           },
    { GLFW_KEY_BACKSPACE       , KeyboardEvent::KeyCode::KEY_BACKSPACE     },
    { GLFW_KEY_INSERT          , KeyboardEvent::KeyCode::KEY_INSERT        },
    { GLFW_KEY_DELETE          , KeyboardEvent::KeyCode::KEY_DELETE        },
    { GLFW_KEY_RIGHT           , KeyboardEvent::KeyCode::KEY_RIGHT_ARROW   },
    { GLFW_KEY_LEFT            , KeyboardEvent::KeyCode::KEY_LEFT_ARROW    },
    { GLFW_KEY_DOWN            , KeyboardEvent::KeyCode::KEY_DOWN_ARROW    },
    { GLFW_KEY_UP              , KeyboardEvent::KeyCode::KEY_UP_ARROW      },
    { GLFW_KEY_PAGE_UP         , KeyboardEvent::KeyCode::KEY_KP_PG_UP      },
    { GLFW_KEY_PAGE_DOWN       , KeyboardEvent::KeyCode::KEY_KP_PG_DOWN    },
    { GLFW_KEY_HOME            , KeyboardEvent::KeyCode::KEY_KP_HOME       },
    { GLFW_KEY_END             , KeyboardEvent::KeyCode::KEY_END           },
    { GLFW_KEY_CAPS_LOCK       , KeyboardEvent::KeyCode::KEY_CAPS_LOCK     },
    { GLFW_KEY_SCROLL_LOCK     , KeyboardEvent::KeyCode::KEY_SCROLL_LOCK   },
    { GLFW_KEY_NUM_LOCK        , KeyboardEvent::KeyCode::KEY_NUM_LOCK      },
    { GLFW_KEY_PRINT_SCREEN    , KeyboardEvent::KeyCode::KEY_PRINT         },
    { GLFW_KEY_PAUSE           , KeyboardEvent::KeyCode::KEY_PAUSE         },
    { GLFW_KEY_F1              , KeyboardEvent::KeyCode::KEY_F1            },
    { GLFW_KEY_F2              , KeyboardEvent::KeyCode::KEY_F2            },
    { GLFW_KEY_F3              , KeyboardEvent::KeyCode::KEY_F3            },
    { GLFW_KEY_F4              , KeyboardEvent::KeyCode::KEY_F4            },
    { GLFW_KEY_F5              , KeyboardEvent::KeyCode::KEY_F5            },
    { GLFW_KEY_F6              , KeyboardEvent::KeyCode::KEY_F6            },
    { GLFW_KEY_F7              , KeyboardEvent::KeyCode::KEY_F7            },
    { GLFW_KEY_F8              , KeyboardEvent::KeyCode::KEY_F8            },
    { GLFW_KEY_F9              , KeyboardEvent::KeyCode::KEY_F9            },
    { GLFW_KEY_F10             , KeyboardEvent::KeyCode::KEY_F10           },
    { GLFW_KEY_F11             , KeyboardEvent::KeyCode::KEY_F11           },
    { GLFW_KEY_F12             , KeyboardEvent::KeyCode::KEY_F12           },
    { GLFW_KEY_F13             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F14             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F15             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F16             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F17             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F18             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F19             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F20             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F21             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F22             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F23             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F24             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F25             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_KP_0            , KeyboardEvent::KeyCode::KEY_0             },
    { GLFW_KEY_KP_1            , KeyboardEvent::KeyCode::KEY_1             },
    { GLFW_KEY_KP_2            , KeyboardEvent::KeyCode::KEY_2             },
    { GLFW_KEY_KP_3            , KeyboardEvent::KeyCode::KEY_3             },
    { GLFW_KEY_KP_4            , KeyboardEvent::KeyCode::KEY_4             },
    { GLFW_KEY_KP_5            , KeyboardEvent::KeyCode::KEY_5             },
    { GLFW_KEY_KP_6            , KeyboardEvent::KeyCode::KEY_6             },
    { GLFW_KEY_KP_7            , KeyboardEvent::KeyCode::KEY_7             },
    { GLFW_KEY_KP_8            , KeyboardEvent::KeyCode::KEY_8             },
    { GLFW_KEY_KP_9            , KeyboardEvent::KeyCode::KEY_9             },
    { GLFW_KEY_KP_DECIMAL      , KeyboardEvent::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_KP_DIVIDE       , KeyboardEvent::KeyCode::KEY_KP_DIVIDE     },
    { GLFW_KEY_KP_MULTIPLY     , KeyboardEvent::KeyCode::KEY_KP_MULTIPLY   },
    { GLFW_KEY_KP_SUBTRACT     , KeyboardEvent::KeyCode::KEY_KP_MINUS      },
    { GLFW_KEY_KP_ADD          , KeyboardEvent::KeyCode::KEY_KP_PLUS       },
    { GLFW_KEY_KP_ENTER        , KeyboardEvent::KeyCode::KEY_KP_ENTER      },
    { GLFW_KEY_KP_EQUAL        , KeyboardEvent::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_LEFT_SHIFT      , KeyboardEvent::KeyCode::KEY_SHIFT         },
    { GLFW_KEY_LEFT_CONTROL    , KeyboardEvent::KeyCode::KEY_CTRL          },
    { GLFW_KEY_LEFT_ALT        , KeyboardEvent::KeyCode::KEY_ALT           },
    { GLFW_KEY_LEFT_SUPER      , KeyboardEvent::KeyCode::KEY_HYPER         },
    { GLFW_KEY_RIGHT_SHIFT     , KeyboardEvent::KeyCode::KEY_SHIFT         },
    { GLFW_KEY_RIGHT_CONTROL   , KeyboardEvent::KeyCode::KEY_CTRL          },
    { GLFW_KEY_RIGHT_ALT       , KeyboardEvent::KeyCode::KEY_ALT           },
    { GLFW_KEY_RIGHT_SUPER     , KeyboardEvent::KeyCode::KEY_HYPER         },
    { GLFW_KEY_MENU            , KeyboardEvent::KeyCode::KEY_MENU          },
    { GLFW_KEY_LAST            , KeyboardEvent::KeyCode::KEY_NONE          }
};

GLViewDesktop::GLViewDesktop() :
GLView(),
_supportTouch(false),
_isRetinaEnabled(false),
_mainWindow(nullptr),
_monitor(nullptr),
_mouseX(0.0f),
_mouseY(0.0f)
{
    _viewName = "Monkey";
    
    g_keyCodeMap.clear();
    for (auto& item : g_keyCodeStructArray) {
        g_keyCodeMap[item.glfwKeyCode] = item.keyCode;
    }
    
    GLFWEventHandler::setGLView(this);
    
    glfwSetErrorCallback(GLFWEventHandler::onGLFWError);
    glfwInit();
}

GLViewDesktop::~GLViewDesktop() {
    GLFWEventHandler::setGLView(nullptr);
    glfwTerminate();
}

void GLViewDesktop::setContentScaleFactor(float contentScaleFactor) {
    _contentScaleFactor = contentScaleFactor;
}

float GLViewDesktop::getContentScaleFactor() const {
    return _contentScaleFactor;
}

bool GLViewDesktop::isOpenGLReady() {
    return nullptr != _mainWindow;
}

void GLViewDesktop::swapBuffers() {
    if (_mainWindow) {
        glfwSwapBuffers(_mainWindow);
        glfwPollEvents();
    }
}

void GLViewDesktop::setIMEKeyboardState(bool bOpen) {
    
}

void GLViewDesktop::enableRetina(bool value) {
    if (!_isRetina) {
        return;
    }
    _isRetinaEnabled = value;
}

bool GLViewDesktop::isRetina() {
    return _isRetinaEnabled;
}

void GLViewDesktop::setViewName(const std::string &viewName) {
    _viewName = viewName;
}

bool GLViewDesktop::initWithRect(const std::string &viewName, int x, int y, int width, int height) {
    
    _eaglview = this;
    // 设置viewname
    setViewName(viewName);
    // hint
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // 创建window
    _mainWindow = glfwCreateWindow(width * _contentScaleFactor, height * _contentScaleFactor, _viewName.c_str(), _monitor, nullptr);
    // 获取framebuffer size
    glfwGetFramebufferSize(_mainWindow, &_frameWidth, &_frameHeight);
    // 获取window size
    glfwGetWindowSize(_mainWindow, &_screenWidth, &_screenHeight);
    // 获取窗口位置
    glfwGetWindowPos(_mainWindow, &_posX, &_posY);
    // 设置window content
    glfwMakeContextCurrent(_mainWindow);
    // call backs
    glfwSetMouseButtonCallback(_mainWindow, GLFWEventHandler::onGLFWMouseCallBack);
    glfwSetCursorPosCallback(_mainWindow, GLFWEventHandler::onGLFWMouseMoveCallBack);
    glfwSetScrollCallback(_mainWindow, GLFWEventHandler::onGLFWMouseScrollCallback);
    glfwSetCharCallback(_mainWindow, GLFWEventHandler::onGLFWCharCallback);
    glfwSetKeyCallback(_mainWindow, GLFWEventHandler::onGLFWKeyCallback);
    glfwSetWindowPosCallback(_mainWindow, GLFWEventHandler::onGLFWWindowPosCallback);
    glfwSetFramebufferSizeCallback(_mainWindow, GLFWEventHandler::onGLFWframebuffersize);
    glfwSetWindowSizeCallback(_mainWindow, GLFWEventHandler::onGLFWWindowSizeFunCallback);
    // 检测是否为retina屏幕
    if (_frameWidth > _screenWidth && _frameHeight > _screenHeight) {
        _isRetina = true;
    } else {
        _isRetina = false;
    }
    setContentScaleFactor(_frameWidth / _screenWidth);
    // 启用retina
    enableRetina(true);
    adaptViewport();
    initGlew();
    // Enable point size by default.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    // 启用剔除
    glEnable(GL_CULL_FACE);
    // 设置顺时针为正面、剔除掉逆时针
    glFrontFace(GL_CW);
    // 启用深度测试
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // 启用模板
    glEnable(GL_STENCIL_TEST);
    
    return true;
}

void GLViewDesktop::adaptViewport() {
    if (_isRetina && _isRetinaEnabled) {
        App::getInstance()->setViewport(0, 0, _frameWidth, _frameHeight);
    } else {
        App::getInstance()->setViewport(0, 0, _screenWidth, _screenHeight);
    }
}

bool GLViewDesktop::isMouseInWindow() {
    if (_mouseX < 0 || _mouseY < 0 || _mouseX > _screenWidth || _mouseY > _screenHeight) {
        return false;
    }
    return true;
}

bool GLViewDesktop::initWithFullScreen(const std::string &viewName) {
    _monitor = glfwGetPrimaryMonitor();
    if (_monitor == nullptr) {
        return false;
    }
    const GLFWvidmode* videoMode = glfwGetVideoMode(_monitor);
    return initWithRect(viewName, 0, 0, videoMode->width, videoMode->height);
}

void GLViewDesktop::onGLFWError(int errorID, const char *errorDesc) {
    LOGE("GLFWError #%d Happen, %s\n", errorID, errorDesc);
}

/**
 *  glfw鼠标回调
 *  TODO:...
 *
 *  @param window window
 *  @param button button
 *  @param action action
 *  @param modify modify
 */
void GLViewDesktop::onGLFWMouseCallBack(GLFWwindow *window, int button, int action, int modify) {
    
    if (!isMouseInWindow()) {
        return;
    }
    
    Point2D *point = new Point2D(_mouseX, _mouseY);
    
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (GLFW_PRESS == action) {
                MouseEvent event(MouseEvent::TOUCH_BEGAN, true, point, 1);
                App::getInstance()->handleTouchesBegan(event);
                Input3D::mouseDown(point, 1);
            } else if (GLFW_RELEASE == action) {
                MouseEvent event(MouseEvent::TOUCH_END, true, point, 1);
                App::getInstance()->handleTouchesEnd(event);
                Input3D::mouseUP(point, 1);
            }
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (GLFW_PRESS == action) {
                MouseEvent event(MouseEvent::RIGHT_MOUSE_DOWN, true, point, 1);
                App::getInstance()->handleTouchesBegan(event);
                Input3D::rightMouseDown(point, 1);
            } else if (GLFW_RELEASE == action) {
                MouseEvent event(MouseEvent::RIGHT_MOUSE_UP, true, point, 1);
                App::getInstance()->handleTouchesEnd(event);
                Input3D::rightMouseUp(point, 1);
            }
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            if (GLFW_PRESS == action) {
                MouseEvent event(MouseEvent::MIDDLE_MOUSE_DOWN, true, point, 1);
                App::getInstance()->handleTouchesBegan(event);
                Input3D::middleMouseDown(point, 1);
            } else if (GLFW_RELEASE == action) {
                MouseEvent event(MouseEvent::MIDDLE_MOUSE_UP, true, point, 1);
                App::getInstance()->handleTouchesEnd(event);
                Input3D::middleMouseUp(point, 1);
            }
            break;
        default:
            break;
    }
    
    free(point);
}

void GLViewDesktop::onGLFWMouseMoveCallBack(GLFWwindow *window, double x, double y) {
    
    _mouseX = (float)x;
    _mouseY = (float)y;
    
    if (!isMouseInWindow()) {
        return;
    }
    
    _mouseY *= getContentScaleFactor();
    _mouseX *= getContentScaleFactor();
    
    Point2D *point = new Point2D(_mouseX, _mouseY);
    MouseEvent event(MouseEvent::TOUCH_MOVE, false, point, 1);
    App::getInstance()->handleTouchesMove(event);
    Input3D::mouseMove(point, 1);
    
    free(point);
}

void GLViewDesktop::onGLFWMouseScrollCallback(GLFWwindow *window, double x, double y) {
    
    if (!isMouseInWindow()) {
        return;
    }
    
    Input3D::mouseWheel((float)x, (float)y);
    
    Point2D *point = new Point2D(_mouseX, _mouseY);
    MouseEvent event(MouseEvent::TOUCH_MOVE, false, point, 1);
    
    event.deltaX = x;
    event.deltaY = y;
    App::getInstance()->handleMouseWheelEvent(event);
    
    free(point);
}

void GLViewDesktop::onGLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (GLFW_REPEAT != action) {
        if (GLFW_PRESS == action) {
            Input3D::keyDown(g_keyCodeMap[key]);
            KeyboardEvent e(KeyboardEvent::KEY_DOWN, g_keyCodeMap[key]);
            App::getInstance()->handleKeyDownEvent(e);
        } else if (GLFW_RELEASE == action) {
            KeyboardEvent e(KeyboardEvent::KEY_UP, g_keyCodeMap[key]);
            Input3D::keyUp(g_keyCodeMap[key]);
            App::getInstance()->handleKeyUpEvent(e);
        }
    }
}

void GLViewDesktop::onGLFWCharCallback(GLFWwindow *window, unsigned int character) {
    
}

void GLViewDesktop::onGLFWWindowPosCallback(GLFWwindow *windows, int x, int y) {
    _posX = x;
    _posY = y;
}

void GLViewDesktop::onGLFWframebuffersize(GLFWwindow* window, int w, int h) {
    _frameWidth  = w;
    _frameHeight = h;
}

void GLViewDesktop::onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height) {
    _screenWidth  = width;
    _screenHeight = height;
    adaptViewport();
}

bool GLViewDesktop::initGlew() {
    
    return true;
}

NS_MONKEY_END
