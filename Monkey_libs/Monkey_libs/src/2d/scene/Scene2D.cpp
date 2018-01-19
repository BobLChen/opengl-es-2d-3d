//
//  Scene2D.cpp
//  Monkey_libs
//
//  Created by Neil on 7/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/scene/Scene2D.h"
#include "2d/entities/DisplayObject.h"
#include "2d/ui/Widget.h"
#include "core/camera/Camera3D.h"
#include "core/camera/lens/OrthographicLens2D.h"
#include "App.h"

NS_MONKEY_BEGIN

Scene2D::Scene2D() : Scene() {
    if (_defaultCamera) {
        delete _defaultCamera;
        _defaultCamera = nullptr;
    }
    _camera = new Camera3D(new OrthographicLens2D());
    _defaultCamera = _camera;
}

Scene2D::~Scene2D() {
    
}

bool Scene2D::eventVisitor(Pivot3D *disp, monkey::TouchEvent &event) {
    if (!event.points || event.size == 0) {
        return false;
    }
    
    Widget *widget = dynamic_cast<Widget*>(disp);
    
    if (disp->getChildren().size() > 0 || widget) {
        // 控件的事件
        if (widget) {
            for (auto iter = widget->getWidgets().rbegin(); iter != widget->getWidgets().rend(); iter++) {
                bool ret = eventVisitor((*iter), event);
                if (ret) {
                    return true;
                }
            }
        }
        // 子集的事件
        for (auto iter = disp->getChildren().rbegin(); iter != disp->getChildren().rend(); iter++) {
            bool ret = eventVisitor((*iter), event);
            if (ret) {
                return true;
            }
        }
        DisplayObject *displayObject = dynamic_cast<DisplayObject*>(disp);
        if (!displayObject) {
            return false;
        }
        return displayObject->acceptTouchEvent(event);
    } else {
        // 非2d显示对象
        DisplayObject *displayObject = dynamic_cast<DisplayObject*>(disp);
        if (!displayObject) {
            return false;
        }
        return displayObject->acceptTouchEvent(event);
    }
    
    return false;
}

void Scene2D::handleTouchesBegan(monkey::TouchEvent &event) {
    dispatchEvent(event);
    eventVisitor(this, event);
}

void Scene2D::handleTouchesEnd(monkey::TouchEvent &event) {
    dispatchEvent(event);
    eventVisitor(this, event);
}

void Scene2D::handleTouchMove(monkey::TouchEvent &event) {
    dispatchEvent(event);
    eventVisitor(this, event);
}

void Scene2D::handleMouseWheel(monkey::TouchEvent &event) {
    dispatchEvent(event);
    eventVisitor(this, event);
}

/**
 *  2d的渲染不再使用层级属性。根据子父级结构来渲染。
 *  @param camera
 *  @param clearDepth
 */
void Scene2D::render(Camera3D* camera, bool clearDepth) {
    _renderLength = (int)_children.size();
    if (_renderLength == 0 || !_visible) {
        return;
    }
    _renderIndex  = 0;
    bool doRender = false;
    if (!_paused) {
        doRender = true;
        _renderEvent.reset();
        dispatchEvent(_renderEvent);
    }
    
    if (clearDepth) {
#if CC_TARGET_PLATFORM == CC_TARGET_OS_IPHONE || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        glClearDepthf(1.0);
#else
        glClearDepth(1.0);
#endif
    }
    
    if (doRender) {
        while (_renderIndex < _renderLength) {
            _children[_renderIndex]->draw(true);
            _renderIndex++;
        }
    }
}

NS_MONKEY_END
