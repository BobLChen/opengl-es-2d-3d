//
//  Pivot3D.h
//  monkey
//
//  Created by Neil on 30/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _Pivot3D_h
#define _Pivot3D_h

#include "platform/PlatformMacros.h"
#include "core/event/Event.h"
#include "core/event/EventDispatcher.h"
#include "core/geom/Vector2D.h"
#include "core/geom/Vector3D.h"
#include "core/geom/Matrix3D.h"
#include "core/geom/Matrix3DUtils.h"
#include "core/geom/mmath.h"
#include "core/base/IComponent.h"
#include "core/material/Material3D.h"

#include <string>
#include <vector>

NS_MONKEY_BEGIN

class Scene;

class Pivot3D : public EventDispatcher {
    
public:
    // ----------- 事件 --------------
    /**
     *  添加到父节点
     */
    static const std::string ADDED_EVENT;
    /**
     *  从父节点移除
     */
    static const std::string REMOVED_EVENT;
    /**
     *  被添加到场景
     */
    static const std::string ADDED_TO_SCENE_EVENT;
    /**
     *  从场景中移除
     */
    static const std::string REMOVED_FROM_SCENE_EVENT;
    /**
     *  动画播放完成
     */
    static const std::string ANIMATION_COMPLETE_EVENT;
    /**
     *  进入帧循环
     */
    static const std::string ENTER_FRAME_EVENT;
    /**
     *  退出帧循环
     */
    static const std::string EXIT_FRAME_EVENT;
    /**
     *  开始绘制
     */
    static const std::string ENTER_DRAW_EVENT;
    /**
     *  结束绘制
     */
    static const std::string EXIT_DRAW_EVENT;
    /**
     *  更新矩阵
     */
    static const std::string UPDATE_TRANSFORM_EVENT;
    /**
     *  上传
     */
    static const std::string UPLOAD_EVENT;
    /**
     *  卸载
     */
    static const std::string DOWN_LOAD_EVENT;
    /**
     *  更新事件
     */
    static const std::string UPDATE_EVENT;
    
protected:
    
    static Event _addedEvent;
    static Event _removedEvent;
    static Event _addedToSceneEvent;
    static Event _removedFromSceneEvent;
    static Event _animationCompleteEvent;
    static Event _enterFrameEvent;
    static Event _exitFrameEvent;
    static Event _enterDrawEvent;
    static Event _exitDrawEvent;
    static Event _updateTransformEvent;
    static Event _uploadEvent;
    static Event _downLoadEvent;
    static Event _updateEvent;
    
    // 临时变量
    static Vector3D _tempVec30;
    static Vector3D _tempVec31;
    static Vector2D _tempVec20;
    static Vector2D _tempVec21;
    
public:
    
    enum class AnimationType {
        LOOP,
        STOP,
        PING_PONG
    };
    
    Pivot3D();
    virtual ~Pivot3D();
    
    /**
     *  pivot名称
     */
    std::string name;
    /**
     *  自定义数据
     */
    void*       userData;
    /**
     *  获取Pivot帧频
     *  @return
     */
    virtual float getFps() const;
    /**
     *  设置帧频
     *  @param value
     */
    virtual void setFps(float value);
    /**
     *  获取播放速度
     *  @return
     */
    virtual float getFpsSpeed() const;
    /**
     *  获取层级
     *  @return
     */
    virtual int getLayer() const;
    /**
     *  是否Lock
     *  @return
     */
    virtual bool isLoock() const;
    /**
     *  lock
     *  @param value
     */
    virtual void setLoock(bool value);
    /**
     *  显示隐藏
     *  @param value
     *  @return
     */
    virtual void setVisiable(bool value);
    /**
     *  是否显示
     *  @return
     */
    virtual bool getVisiable() const;
    /**
     *  是否在scene中
     *  @return
     */
    virtual bool getInScene() const;
    /**
     *  是否启用动画
     *  @return
     */
    virtual bool isAnimationEnabled() const;
    /**
     *  是否启用鼠标
     *  @return
     */
    virtual bool isMouseEnabled() const;
    /**
     *  启用鼠标
     *  @param value
     *  @return
     */
    virtual void enableMouse(bool value);
    /**
     *  启用动画
     *  @param value
     *  @return
     */
    virtual void enableAnimation(bool value);
    /**
     *  设置frameSpeed
     *  @param value
     */
    virtual void setFrameSpeed(float value);
    /**
     *  获取transform
     *  @return
     */
    virtual Matrix3D& getTransform();
    /**
     *  设置transform
     *  @param mt
     */
    virtual void setTransform(const Matrix3D &mt);
    /**
     *  @return
     */
    virtual bool getDirty();
    /**
     *  @param value
     */
    virtual void setDirty(bool value);
    /**
     *  添加组件
     *  @param component
     *  @return
     */
    virtual bool addComponent(IComponent *component);
    /**
     *  移除组件
     *  @param component
     *  @return
     */
    virtual bool removeComponent(IComponent *component);
    /**
     *  上传
     *  @param includeChildren  子节点是否一并上传
     */
    virtual void upload(bool includeChildren);
    /**
     *  卸载
     *  @param includeChildren 是否包含子节点
     */
    virtual void download(bool includeChildren);
    /**
     *  复制
     *  @param pivot
     */
    virtual void copyFrom(Pivot3D *pivot);
    /**
     *  设置坐标
     *
     *  @param x        x
     *  @param y        y
     *  @param z        z
     *  @param smooth   smooth
     *  @param local    local
     */
    virtual void setPosition(float x, float y, float z, float smooth = 1.0f, bool local = true);
    /**
     *  设置坐标
     *  @param pos
     *  @param smooth
     *  @param local
     */
    virtual void setPosition(const Vector3D &pos, float smooth = 1.0f, bool local = true);
    /**
     *  获取坐标
     *  @param dest
     *  @param local
     */
    virtual void getPosition(Vector3D &dest, bool local = true);
    /**
     *  缩放
     *  @param x   x轴缩放值
     *  @param y   y轴缩放值
     *  @param z   z轴缩放值
     *  @param smooth
     */
    virtual void setScale(float x, float y, float z, float smooth = 1.0f);
    /**
     *  缩放
     *  @param scale
     *  @param smooth
     */
    virtual void setScale(const Vector3D &scale, float smooth = 1.0f);
    /**
     *  获取缩放值
     *  @param dest
     *  @param bool
     */
    virtual void getScale(Vector3D &dest, bool = true);
    /**
     *  获取Y轴角度
     *  @param local
     *  @return
     */
    virtual float getRotationY(bool local = true);
    /**
     *  获取x轴角度
     *  @param local
     *  @return
     */
    virtual float getRotationX(bool local = true);
    /**
     *  获取Z轴角度
     *  @param local
     *  @return
     */
    virtual float getRotationZ(bool local = true);
    /**
     *  设置角度
     *  @param x
     *  @param y
     *  @param z
     */
    virtual void setRotation(float x, float y, float z);
    /**
     *  设置角度
     *  @param rotation
     */
    virtual void setRoatation(const Vector3D &rotation);
    /**
     *  获取角度
     *  @param dest
     *  @param local
     */
    virtual void getRotation(Vector3D &dest, bool local = true);
    /**
     *  lookat
     *
     *  @param x        x
     *  @param y        y
     *  @param z        z
     *  @param up       UP_AXIS
     *  @param smooth
     */
    virtual void lookAt(float x, float y, float z, const Vector3D &up = Vector3D::Y_AXIS, float smooth = 1.0f);
    /**
     *  lookat
     *
     *  @param target
     *  @param up
     *  @param smooth
     */
    virtual void lookAt(const Vector3D &target, const Vector3D &up = Vector3D::Y_AXIS, float smooth = 1.0f);
    /**
     *  设置朝向
     *
     *  @param x        x
     *  @param y        y
     *  @param z        z
     *  @param up       UP
     *  @param smooth
     */
    virtual void setOrientation(float x, float y, float z, const Vector3D &up = Vector3D::Y_AXIS, float smooth = 1.0f);
    /**
     *  设置朝向
     *
     *  @param dir
     *  @param UP
     *  @param smooth
     */
    virtual void setOrientation(const Vector3D &dir, const Vector3D &up = Vector3D::Y_AXIS, float smooth = 1.0f);
    /**
     *  绕x轴旋转
     *
     *  @param angle        角度
     *  @param local        local
     *  @param pivotPoint   中心点
     */
    virtual void rotateX(float angle, bool local = true, Vector3D *pivotPoint = nullptr);
    /**
     *  绕y轴旋转
     *  @param angle      角度
     *  @param local      local
     *  @param pivotPoint 中心点
     */
    virtual void rotateY(float angle, bool local = true, Vector3D *pivotPoint = nullptr);
    /**
     *  绕z轴渲染
     *  @param angle      角度
     *  @param local      local
     *  @param pivotPoint 中心点
     */
    virtual void rotateZ(float angle, bool local = true, Vector3D *pivotPoint = nullptr);
    /**
     *  绕Axis轴旋转
     *  @param angle      角度
     *  @param axis       轴
     *  @param pivotPoint 中心点
     */
    virtual void rotateAxis(float angle, const Vector3D &axis, Vector3D *pivotPoint = nullptr);
    /**
     *  缩放x轴
     *
     *  @param value
     */
    virtual void setScaleX(float value);
    /**
     *  缩放Y轴
     *  @param value
     */
    virtual void setScaleY(float value);
    /**
     *  缩放z轴
     *  @param value
     */
    virtual void setScaleZ(float value);
    /**
     *  获取x轴缩放值
     *  @return
     */
    virtual float getScaleX() const;
    /**
     *  获取y轴缩放值
     *  @return
     */
    virtual float getScaleY() const;
    /**
     *  获取z轴缩放值
     *  @return
     */
    virtual float getScaleZ() const;
    /**
     *  设置位移
     *  @param x     x轴位移
     *  @param y     y轴位移
     *  @param z     z轴位移
     *  @param local local
     */
    virtual void setTranslation(float x, float y, float z, bool local = true);
    /**
     *  设置位移
     *  @param pos
     *  @param local
     */
    virtual void setTranslation(const Vector3D &pos, bool local = true);
    /**
     *  x轴平移
     *  @param distance 距离
     *  @param local
     */
    virtual void translateX(float distance, bool local = true);
    /**
     *  y轴平移
     *  @param distance 距离
     *  @param local
     */
    virtual void translateY(float distance, bool local = true);
    /**
     *  z轴平移
     *  @param distance 距离
     *  @param local
     */
    virtual void translateZ(float distance, bool local = true);
    /**
     *  绕Axis轴平移
     *  @param distance 距离
     *  @param x        x
     *  @param y        y
     *  @param z        z
     */
    virtual void translateAxis(float distance, float x, float y, float z);
    /**
     *  绕axis轴平移
     *  @param distance 距离
     *  @param axis     axis轴
     */
    virtual void translateAxis(float distance, const Vector3D &axis);
    /**
     *  复制transform矩阵
     *
     *  @param source 源
     *  @param local
     */
    virtual void copyTransformFrom(Pivot3D *source, bool local = true);
    /**
     *  重置矩阵
     */
    virtual void resetTransform();
    /**
     *  获取x坐标
     *  @return
     */
    virtual float getX();
    /**
     *  获取y坐标
     *  @return
     */
    virtual float getY();
    /**
     *  获取z坐标
     *  @return
     */
    virtual float getZ();
    /**
     *  设置x坐标
     *  @param value
     */
    virtual void setX(float value);
    /**
     *  设置y坐标
     *  @param value
     */
    virtual void setY(float value);
    /**
     *  设置z坐标
     *  @param value
     */
    virtual void setZ(float value);
    /**
     *  获取右边方向
     *  @param dest
     *  @param local
     */
    virtual void getRight(Vector3D &dest, bool local = true);
    /**
     *  获取左边方向
     *  @param dest
     *  @param local
     */
    virtual void getLeft(Vector3D &dest, bool local = true);
    /**
     *  获取上方方向
     *  @param dest
     *  @param local
     */
    virtual void getUP(Vector3D &dest, bool local = true);
    /**
     *  获取下方方向
     *  @param dest
     *  @param local
     */
    virtual void getDown(Vector3D &dest, bool local = true);
    /**
     *  获取前方方向
     *  @param dest
     *  @param local
     */
    virtual void getFront(Vector3D &dest, bool local = true);
    /**
     *  获取后方方向
     *  @param dest
     *  @param local
     */
    virtual void getBackward(Vector3D &dest, bool local = true);
    /**
     *  本地转全局
     *  @param dest 输出目标
     *  @param src  源
     */
    virtual void localToGlobal(Vector3D &dest, const Vector3D &src);
    /**
     *  本地转全局，忽略位移
     *  @param dest 输出目标
     *  @param src  源
     */
    virtual void localToGlobalVector(Vector3D &dest, const Vector3D &src);
    /**
     *  全局转本地
     *  @param dest
     *  @param src
     */
    virtual void globalToLocal(Vector3D &dest, const Vector3D &src);
    /**
     *  全局转本地
     *  @param dest
     *  @param src
     */
    virtual void globalToLocalVector(Vector3D &dest, const Vector3D &src);
    /**
     *  获取global矩阵
     *  @return
     */
    virtual Matrix3D& getWorld();
    /**
     *  设置global矩阵
     *  @param mt
     */
    virtual void setWorld(const Matrix3D &mt);
    /**
     *  获取global逆矩阵
     *  @return
     */
    virtual Matrix3D& getInvWorld();
    /**
     *  更新transform
     *  @param includeChildren
     */
    virtual void updateTransforms(bool includeChildren = true);
    /**
     *  获取子集
     *  @return
     */
    virtual std::vector<Pivot3D*> &getChildren();
    /**
     *  获取父节点
     *  @return
     */
    virtual Pivot3D* getParent();
    /**
     *  设置父级
     *  @param parent
     */
    virtual void setParent(Pivot3D *parent);
    /**
     *  添加到场景
     *  @param scene
     */
    virtual void addedToScene(Scene *scene);
    /**
     *  从场景中移除
     */
    virtual void removedFromScene();
    /**
     *  添加child
     *  @param pivot          child
     *  @param index          index
     *  @param useGlobalSpace
     */
    virtual void addChildAt(Pivot3D *pivot, int index, bool useGlobalSpace = false);
    /**
     *  添加child
     *  @param pivot
     *  @param useGlobalSpace
     */
    virtual void addChild(Pivot3D *pivot, bool useGlobalSpace = false);
    /**
     *  移除节点
     *  @param pivot
     */
    virtual void removeChild(Pivot3D *pivot);
    /**
     *  通过名称获取child
     *  @param name             名称
     *  @param startIndex       搜寻起始位置
     *  @param includeChildren  是否搜寻子节点
     *  @return
     */
    virtual Pivot3D* getChildByName(const std::string &name, int startIndex = 0, bool includeChildren = true);
    /**
     *  gotoAndStop
     *  @param frame
     */
    virtual void gotoAndStop(float frame);
    /**
     *  gotoAndPlay
     *  @param frame
     */
    virtual void gotoAndPlay(float frame, AnimationType type = AnimationType::LOOP);
    /**
     *  获取当前帧
     *  @return
     */
    virtual float getCurrentFrame();
    /**
     *  设置当前帧
     *  @param value
     */
    virtual void setCurrentFrame(float value);
    /**
     *  播放
     */
    virtual void play(AnimationType type = AnimationType::LOOP);
    /**
     *  暂停
     */
    virtual void stop();
    /**
     *  前一帧
     *  @param advancedTime
     */
    virtual void prevFrame(float advancedTime);
    /**
     *  后一帧
     *  @param advancedTime
     */
    virtual void nextFrame(float advancedTime);
    /**
     *  更新
     *  @param advancedTime
     *  @param includeChildren
     */
    virtual void update(float advancedTime, bool includeChildren);
    /**
     *  获取scene
     *  @return
     */
    virtual Scene* getScene();
    /**
     *  显示
     */
    virtual void show();
    /**
     *  隐藏
     */
    virtual void hide();
    /**
     *  绘制
     *  @param includeChildren 是否一并绘制子节点
     *  @param shader          shader
     */
    virtual void draw(bool includeChildren = true, Material3D* shader = nullptr);
    /**
     *  绘制深度
     *  @param includeChildren
     */
    virtual void drawDepth(bool includeChildren = true, Material3D* shader = nullptr);
    /**
     *  是否在camera镜头内
     *  @return
     */
    virtual bool inView();
    /**
     *  设置层级
     *  @param layer
     *  @param includeChildren
     *  @return
     */
    virtual void setLayer(int layer, bool includeChildren = true);
    /**
     *  是否可更新
     *  @return
     */
    virtual bool getUpdatable();
    /**
     *  设置为可更新
     *  @param value
     */
    virtual void setUpdatable(bool value);
    /**
     *  是否为可绘制
     *  @return
     */
    virtual bool getDrable();
    /**
     *  设置为可绘制
     *  @param value
     *  @return
     */
    virtual void setDrable(bool value);
    
protected:
    
    float   _fps;                       // 帧频
    float   _fpsSpeed;                  // 帧速度
    int     _layer;                     // 层级
    
    bool    _dirty;                     // 本地矩阵待更新
    bool    _dirtyInv;                  // 逆世界矩阵待更新
    bool    _lock;                      // lock
    bool    _visible;                   // 是否显示
    bool    _inScene;                   // 是否在场景中
    bool    _animationEnabled;          // 是否启用动画
    bool    _mouseEnabled;              // 是否启用鼠标
    AnimationType _animationType;       // 动画类型
    
    float   _from;                      // 起始帧
    float   _to;                        // 结束帧
    float   _currentFrame;              // 当前帧
    float   _frameSpeed;                // 动画播放速度
    float   _laseFrame;                 // lastFrame
    bool    _isPlaying;                 // 是否正在播放动画
    bool    _updatable;                 // 可更新
    bool    _drable;                    // 可绘制
    
    Pivot3D*                _parent;    // 父节点
    std::vector<Pivot3D*>   _children;  // 子节点
    Scene*                  _scene;     // scene
    std::vector<IComponent*> _components;// 组件
    
    Matrix3D _transform;                // 本地空间矩阵
    Matrix3D _world;                    // 世界空间矩阵
    Matrix3D _invWorld;                 // 逆世界空间矩阵
    
};

NS_MONKEY_END

#endif
