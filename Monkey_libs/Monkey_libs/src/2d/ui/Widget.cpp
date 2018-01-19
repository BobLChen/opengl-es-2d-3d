//
//  Widget.cpp
//  Monkey_libs
//
//  Created by Neil on 2/11/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/ui/Widget.h"
#include "core/event/TouchEvent.h"
#include <algorithm>

NS_MONKEY_BEGIN

Widget::Widget() {
    
}

Widget::~Widget() {
    for (auto iter = _widgetList.begin(); iter != _widgetList.end(); iter++) {
        delete (*iter);
    }
    _widgetList.clear();
}

void Widget::updateTransforms(bool includeChildren) {
    DisplayObject::updateTransforms(includeChildren);
    if (includeChildren) {
        for (auto iter = _widgetList.begin(); iter != _widgetList.end(); iter++) {
            (*iter)->updateTransforms(true);
        }
    }
}

void Widget::addWidget(monkey::DisplayObject *widget) {
    _widgetList.push_back(widget);
    widget->parent(this);
}

void Widget::addWidgetAt(monkey::DisplayObject *widget, int index) {
    _widgetList.insert(_widgetList.begin() + index, widget);
    widget->parent(this);
}

void Widget::removeWidget(monkey::DisplayObject *widget) {
    auto iter = std::find(_widgetList.begin(), _widgetList.end(), widget);
    if (iter != _widgetList.end()) {
        _widgetList.erase(iter);
        widget->parent(nullptr);
    }
}

void Widget::removeWidgetAt(int index) {
    auto iter = _widgetList.begin() + index;
    (*(_widgetList.begin() + index))->parent(nullptr);
    _widgetList.erase(iter);
}

std::vector<DisplayObject*>& Widget::getWidgets() {
    return _widgetList;
}

void Widget::draw(bool includeChildren, Material3D* shader) {
    _enterDrawEvent.reset();
    dispatchEvent(_enterDrawEvent);
    
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->draw(includeChildren, shader);
    }
    
    for (auto iter = _widgetList.begin(); iter != _widgetList.end(); iter++) {
        (*iter)->draw(includeChildren, shader);
    }
    
    _exitDrawEvent.reset();
    dispatchEvent(_exitDrawEvent);
}

NS_MONKEY_END
