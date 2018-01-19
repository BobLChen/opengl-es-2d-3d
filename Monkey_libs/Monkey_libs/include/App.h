//
//  App.h
//  Opengl2D
//
//  Created by Neil on 3/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __App__
#define __App__

#include "core/base/GLBase.h"
#include "core/utils/Value.h"
#include "core/geom/Matrix3D.h"
#include "core/geom/Vector2D.h"
#include "core/event/EventDispatcher.h"
#include "platform/PlatformMacros.h"
#include "platform/PlatformConfig.h"

#include <sys/time.h>
#include <vector>

NS_MONKEY_BEGIN

class Value;
class Scene;
class Scene2D;
class LabelFNT;
class Event;
class TouchEvent;
class KeyboardEvent;
class GLView;

class App : public EventDispatcher {
    
public:
    
    /**
     *  模型矩阵
     */
    Matrix3D model;
    /**
     *  相机view矩阵
     */
    Matrix3D view;
    /**
     *  投影矩阵
     */
    Matrix3D projection;
    /**
     *  view projection
     */
    Matrix3D viewProjection;
    /**
     *  mvp矩阵
     */
    Matrix3D mvp;
    
    int vertices;
    int drawcalls;
    int triangles;
    
    /**
     *  App实例
     *  @return App
     */
    static App* getInstance();
    
    /**
     *  获取fps
     *  @return fps FrameRate
     */
    float getFps();
    /**
     *  设置fps,区间[1,60]
     *  @param value
     */
    void setFps(float value);
    /**
     *  是否正在显示opengl状态
     *  @return
     */
    bool isShowStats();
    /**
     *  显示或者隐藏opengl状态显示
     *  @param value visiable
     */
    void setVisiableStats(bool value);
    /** 
     *  获取OpenGLView
     *  @return glview
     */
    GLView* getOpenGLView();
    /**
     *  设置OpenGLView
     *  @param glview glview
     */
    void setOpenGLView(GLView *glview);
    /**
     *  是否暂停渲染
     *  @return
     */
    bool isPaused();
    /**
     *  暂停渲染
     */
    void pause();
    /**
     *  恢复渲染
     */
    void resume();
    /**
     *  设置viewport、对应设置opengl viewport。决定opengl渲染区域
     *
     *  @param x      x坐标
     *  @param y      y坐标
     *  @param width  宽度
     *  @param height 高度
     */
    void setViewport(int x, int y, int width, int height);
    /**
     *  获取opengl宽度
     *  @return
     */
    int getWidth();
    /**
     *  获取opengl高度
     *  @return
     */
    int getHeight();
    /**
     *  添加scene2d
     *  @param scene2D
     */
    void addScene2D(Scene2D *scene2D);
    /**
     *  移除scene2d
     *  @param scene2D
     */
    void removeScene2D(Scene2D *scene2D);
    /**
     *  添加scene3d
     *  @param scene
     */
    void addScene3D(Scene *scene);
    /**
     *  移除scene3d
     *  @param scene
     */
    void removeScene3D(Scene *scene);
    /**
     *  最大贴图尺寸
     *  @return
     */
    int getMaxTextureSize();
    /**
     *  支持最大多重贴图数量
     *  @return
     */
    int getMaxTextureSamples();
    /**
     *  可用贴图单元数量
     *  @return
     */
    int getMaxTextureUnits();
    /**
     *  启用混合模式
     *  @param value
     */
    void enableBlend(bool value);
    /**
     *  启用深度检测
     *
     *  @param value
     */
    void enableDepthTest(bool value);
    /**
     *  启用stencil测试
     *
     *  @param value
     */
    void enableStencilTest(bool value);
    /**
     *  设置背景色
     *
     *  @param color
     */
    void setBackcolor(int color);
    /**
     *  update
     */
    void update();
    /**
     *  设置缩放倍数
     *  @param value 缩放倍数(retina屏)
     */
    void setScaleFactor(float value);
    /**
     *  缩放倍数
     *
     *  @return
     */
    float getScaleFactor();
    /**
     *  是否启用混合模式
     *
     *  @return
     */
    bool isEnableBlend();
    /**
     *  是否启用深度检测
     *
     *  @return
     */
    bool isEnableDepth();
    /**
     *  是否启用stencil测试
     *
     *  @return
     */
    bool isEnableStencil();
    /**
     *  释放app实例
     *
     *  @return
     */
    bool dispose();
    /**
     *  获取运行时间
     *
     *  @return
     */
    float getRunningTime();
    /**
     *  handle touch began event
     *  @param event
     */
    void handleTouchesBegan(TouchEvent &event);
    /**
     *  handle touch move event
     *  @param event
     */
    void handleTouchesMove(TouchEvent &event);
    /**
     *  handle touch end event
     *  @param event
     */
    void handleTouchesEnd(TouchEvent &event);
    /**
     *  handle mousewheel event
     *  @param event
     */
    void handleMouseWheelEvent(TouchEvent &event);
    /**
     *  handle key down event
     *  @param event
     */
    void handleKeyDownEvent(KeyboardEvent &event);
    /**
     *  handle key up event
     *  @param event
     */
    void handleKeyUpEvent(KeyboardEvent &event);
    
private:
    
    /**
     *  单例模式，因此隐藏掉构造函数以及析构函数。
     */
    App();
    /**
     *  单例模式，隐藏掉析构函数，由dispose接管销毁
     */
    ~App();
    
    /**
     * 初始化实例
     * @return
     */
    bool    init();
    
    std::vector<Scene2D*> _scene2DList;
    std::vector<Scene*>   _scene3DList;
    
    struct timeval  start_time;
    LabelFNT*       _status;
    float           _preTime;
    float           _fps;
    bool            _showStats;
    bool            _paused;
    int             _fpsFrame;
    float           _fpsTime;
    int             _width;
    int             _height;
    GLView*         _glview;
    bool            _enbaleBlend;
    bool            _enableDepthTest;
    bool            _enabelStencilTest;
    float           _scaleFactor;
    char*           _extensions;
    GLint          _maxTextureSize;
    GLint          _maxTextureUnits;
    GLint          _maxSamplesAllowed;
    ValueMap        _valueDict;
};

NS_MONKEY_END

#endif
