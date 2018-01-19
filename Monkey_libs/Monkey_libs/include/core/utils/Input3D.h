//
//  Input3D.h
//  Monkey_libs
//
//  Created by Neil on 4/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_Input3D_h
#define Monkey_libs_Input3D_h

#include "platform/PlatformMacros.h"

#include "core/geom/Vector2D.h"
#include "core/base/Object.h"
#include "core/event/KeyboardEvent.h"

#include <vector>

NS_MONKEY_BEGIN

class Input3D : public Object {
    
private:
    
    static std::vector<unsigned int> _ups;
    static std::vector<unsigned int> _downs;
    static std::vector<unsigned int> _hits;
    
    static int _keyCode;
    static float _deltaX;
    static float _deltaY;
    static int _deltaMove;
    static int _mouseUp;
    static int _mouseHit;
    static int _mouseDown;
    static int _rightMouseUp;
    static int _rightMouseHit;
    static int _rightMouseDown;
    static int _middleMouseUp;
    static int _middleMouseHit;
    static int _middleMouseDown;
    static int _mouseDoubleClick;
    static float _mouseX;
    static float _mouseY;
    static float _stageX;
    static float _stageY;
    static float _mouseXSpeed;
    static float _mouseYSpeed;
    static bool  _mouseUpdated;
    static int   _currFrame;
    static float _movementX;
    static float _movementY;
    
public:
    
    
    /**
     *  mouse move
     *  @param xs  x坐标
     *  @param ys  y坐标
     *  @param num 数量
     */
    static void mouseMove(Point2D *points, int num);
    /**
     *  mouse up
     *
     *  @param xs  x坐标
     *  @param ys  y坐标
     *  @param num 数量
     */
    static void mouseUP(Point2D *points, int num);
    /**
     *  mouse Down
     *
     *  @param xs  x坐标
     *  @param ys  y坐标
     *  @param num 数量
     */
    static void mouseDown(Point2D *points, int num);
    /**
     *  mouse wheel
     *  @param deltaX
     *  @param deltaY
     */
    static void mouseWheel(float deltaX, float deltaY);
    /**
     *  right mouse down
     *
     *  @param xs  x坐标
     *  @param ys  y坐标
     *  @param num 数量
     */
    static void rightMouseDown(Point2D *points, int num);
    /**
     *  right mouse up
     *  @param xs  x坐标
     *  @param ys  y坐标
     *  @param num 数量
     */
    static void rightMouseUp(Point2D *points, int num);
    /**
     *  millde mouse down
     *  @param xs  x坐标
     *  @param ys  y坐标
     *  @param num 数量
     */
    static void middleMouseDown(Point2D *points, int num);
    /**
     *  middle mouse up
     *  @param xs  x坐标
     *  @param ys  y坐标
     *  @param num 数量
     */
    static void middleMouseUp(Point2D *points, int num);
    /**
     *  double click
     *
     *  @param xs  x坐标
     *  @param ys  y坐标
     *  @param num 数量
     */
    static void doubleClick(Point2D *points, int num);
    /**
     *  key down
     *  @param keycode 键code
     */
    static void keyDown(KeyboardEvent::KeyCode keycode);
    /**
     *  key up
     *  @param keycode
     */
    static void keyUp(KeyboardEvent::KeyCode keycode);
    /**
     *  get key code
     *  @return
     */
    static int getKeycode();
    /**
     *  检测键是否被按下
     *  @param keycode
     *  @return
     */
    static bool isKeydown(KeyboardEvent::KeyCode keycode);
    /**
     *  检测键是否被松开
     *  @param keycode
     *  @return
     */
    static bool isKeyUp(int keycode);
    /**
     *  @param keycode
     *  @return
     */
    static bool isKeyHit(int keycode);
    /**
     *  是否双击
     *  @return
     */
    static bool isMouseDoubleClick();
    /**
     *  get mouse wheel delta
     *  @return
     */
    static float getDeltaX();
    /**
     *  get mouse wheel delta
     *  @return
     */
    static float getDeltaY();
    /**
     *  get mouse y speed
     *  @return
     */
    static float getMouseYSpeed();
    /**
     *  get mouse x speed
     *  @return
     */
    static float getMouseXSpeed();
    /**
     *  @return
     */
    static bool isMouseHit();
    /**
     *  检测mouse是否松开
     *  @return
     */
    static bool isMouseUP();
    /**
     *  检测mouse是否按下
     *  @return
     */
    static bool isMouseDown();
    /**
     *  检测右键是否点击
     *  @return
     */
    static bool isRightMouseHit();
    /**
     *  检测右键是否按下
     *  @return
     */
    static bool isRightMouseDown();
    /**
     *  检测右键是否松开
     *  @return
     */
    static bool isRightMouseUp();
    /**
     *  检测是否点击中键
     *  @return
     */
    static bool isMiddleMouseHit();
    /**
     *  中键up
     *  @return
     */
    static bool isMiddleMouseUp();
    /**
     *  中键down
     *  @return
     */
    static bool isMiddleMouseDown();
    /**
     *  获取x坐标
     *  @return
     */
    static float getMouseX();
    /**
     *  获取y坐标
     *  @return
     */
    static float getMouseY();
    /**
     *  @return
     */
    static float getMovementX();
    /**
     *  @return
     */
    static float getMovementY();
    /**
     *  clear
     */
    static void clear();
    
    static void update();
    
};


NS_MONKEY_END

#endif
