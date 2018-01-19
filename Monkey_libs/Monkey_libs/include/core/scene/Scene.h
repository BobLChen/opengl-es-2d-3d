//
//  Scene3D.h
//  Monkey_libs
//
//  Created by Neil on 3/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_Scene3D_h
#define Monkey_libs_Scene3D_h

#include "platform/PlatformMacros.h"
#include "core/base/Pivot3D.h"
#include "core/event/Event.h"
#include "core/event/TouchEvent.h"
#include "core/event/KeyboardEvent.h"
#include "core/geom/Rectangle.h"
#include "core/material/Geometry3D.h"
#include "core/material/Material3D.h"

#include <string>
#include <vector>

NS_MONKEY_BEGIN

class Camera3D;

class Scene : public Pivot3D {
    
public:
    /**
     *  渲染事件
     */
    const static std::string RENDER_EVENT;
    /**
     *  暂停事件
     */
    const static std::string PAUSED_EVENT;
    /**
     *  后期渲染事件
     */
    const static std::string POSTRENDER_EVENT;
    /**
     *  渲染前事件
     */
    const static std::string PRERENDER_EVENT;
    /**
     *  软加速事件
     */
    const static std::string SOFT_MODE_EVENT;
    
protected:
    
    static Event _postRenderEvent;
    static Event _preRenderEvent;
    static Event _pausedEvent;
    static Event _renderEvent;
    static Event _softEvent;
    
public:
    
    enum class SortMode {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT
    };
    
    struct LayerSort {
        
        int         layer;
        int         left;
        int         right;
        SortMode    mode;
        bool        active;
        
        LayerSort(int la, int le, int ri, SortMode mo) : layer(la), left(le), right(ri), mode(mo), active(false)
        {
            
        }
    };
    
    Scene();
    virtual ~Scene();
    
    /**
     *  设置背景色
     *  @param color
     */
    virtual void setBackgroundColor(unsigned int color);
    /**
     *  获取背景色
     *  @return
     */
    virtual unsigned int getBackgroundColor() const;
    /**
     *  设置viewport
     *  @param x      x
     *  @param y      y
     *  @param width  width
     *  @param height height
     */
    virtual void setViewport(float x, float y, float width, float height);
    /**
     *  获取相机
     *  @return
     */
    virtual Camera3D* getCamera() const;
    /**
     *  设置相机
     *  @param camera
     */
    virtual void setCamera(Camera3D *camera);
    /**
     *  获取帧频
     *  @return
     */
    virtual float getFrameRate() const;
    /**
     *  设置帧频
     *  @param value
     *  @return
     */
    virtual void setFrameRate(float value);
    /**
     *  设置当前帧
     *  @param camera
     */
    virtual void setupFrame(Camera3D *camera = nullptr);
    /**
     *  绘制
     *  @param includeChildren 是否一并绘制子节点
     *  @param shader          shader
     */
    virtual void draw(bool includeChildren = true, Material3D* shader = nullptr) override;
    /**
     *  更新
     *  @param advancedTime
     *  @param includeChildren
     */
    virtual void update(float advancedTime, bool includeChildren) override;
    /**
     *  render
     *  @param camera       相机
     *  @param clearDepth   是否清楚深度缓存
     */
    virtual void render(Camera3D *camera = nullptr, bool clearDepth = false);
    /**
     *  获取父节点
     *  @return
     */
    virtual Pivot3D* getParent() override;
    /**
     *  设置父级
     *  @param parent
     */
    virtual void setParent(Pivot3D *parent) override;
    /**
     *  恢复渲染
     */
    virtual void resume();
    /**
     *  暂停渲染
     */
    virtual void pause();
    /**
     *  是否暂停渲染
     *  @return
     */
    virtual bool paused();
    /**
     *  设置抗锯齿等级
     *  @param value
     */
    virtual void setAntialias(int value);
    /**
     *  获取抗锯齿等级
     *  @return
     */
    virtual int  getAntialias();
    /**
     *  获取viewport
     *  @return
     */
    virtual const Rectangle& getViewPort();
    /**
     *  获取渲染列表
     *  @return
     */
    virtual std::vector<Pivot3D*> &getRenderList();
    /**
     *  获取更新列表
     *  @return
     */
    virtual std::vector<Pivot3D*> &getUpdateList();
    /**
     *  从场景中移除
     *  @param pivot  pivot     child
     *  @param update update    是否可更新
     *  @param render render    是否可绘制
     */
    virtual void removeFromScene(Pivot3D *pivot, bool update, bool render);
    /**
     *  添加到场景
     *  @param pivot            child
     *  @param update           是否可更新
     *  @param render           是否可绘制
     */
    virtual void addToScene(Pivot3D *pivot, bool update, bool render);
    /**
     *  设置排序模式
     *  @param layer
     *  @param mode
     */
    virtual void setLayerSortMode(int layer, SortMode mode = SortMode::BACK_TO_FRONT);
    /**
     *  释放场景内存
     */
    virtual void freeMemory();
    /**
     *  销毁场景
     */
    virtual void dispose();
    /**
     *  enter scene
     *  @param advancedTime
     */
    virtual void enterScene(float advancedTime);
    
    /**
     *  touches began事件
     *  @param event
     */
    virtual void handleTouchesBegan(TouchEvent &event);
    /**
     *  touch end事件
     *  @param event
     */
    virtual void handleTouchesEnd(TouchEvent &event);
    /**
     *  touch move事件
     *  @param event
     */
    virtual void handleTouchMove(TouchEvent &event);
    /**
     *  mouse wheel事件
     *  @param event
     */
    virtual void handleMouseWheel(TouchEvent &event);
    /**
     *  key down事件
     *  @param event
     */
    virtual void handleKeyDown(KeyboardEvent &event);
    /**
     *  key up事件
     *  @param event
     */
    virtual void handleKeyUp(KeyboardEvent &event);
    
    bool skipRender;
    
    Vector3D clearColor;
    
    std::vector<Geometry3D*> geometrys;
    std::vector<Material3D*> materials;
    
protected:
    
    float _frameRate;
    float _tick;
    
    bool _paused;
    
    Camera3D* _camera;
    Camera3D* _defaultCamera;
    Rectangle _viewPort;
    
    int     _antialias;
    bool    _updated;
    
    std::vector<Pivot3D*>   _renderList;
    std::vector<Pivot3D*>   _updateList;
    std::vector<LayerSort>  _layers;
    
    int _updateLength;
    int _renderLength;
    int _updateIndex;
    int _renderIndex;
    
    
    
};

NS_MONKEY_END

#endif
