//
//  KeyboardEvent.cpp
//  Monkey_libs
//
//  Created by Neil on 8/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/event/KeyboardEvent.h"

NS_MONKEY_BEGIN

const std::string KeyboardEvent::KEY_DOWN = "KEY_DOWN";
const std::string KeyboardEvent::KEY_UP   = "KEY_UP";

KeyboardEvent::KeyboardEvent(const std::string &type, KeyCode key):
Event(type, false),
keyCode(key)
{}

NS_MONKEY_END