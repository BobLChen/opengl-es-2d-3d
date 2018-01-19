//
//  ByteArray.cpp
//  Monkey
//
//  Created by Neil on 24/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include <string>

#include "core/utils/Log.h"
#include "core/utils/ByteArray.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

ByteArray:: ~ByteArray() {
    _bytes -= _position;
    delete _bytes;
}

bool ByteArray::isNull() {
    return _bytes == nullptr;
}

unsigned int ByteArray::getPosition() {
    return _position;
}

unsigned int ByteArray::getLength() {
    return _length;
}

void ByteArray::setPosition(unsigned int pos) {
    _bytes -= _position;
    if (pos > _length) {
        _position = _length;
    } else {
        _position = pos;
    }
    _bytes += _position;
}

int ByteArray::readInt() {
    int result = *(int*)_bytes;
    _bytes += 4;
    _position += 4;
    return result;
}

float ByteArray::readFloat() {
    float result = *(float*)_bytes;
    _bytes += 4;
    _position += 4;
    return result;
}

unsigned char* ByteArray::getBytes() {
    return _bytes;
}

void ByteArray::readBytes(unsigned char *bytes, unsigned int size) {
    memcpy(bytes, _bytes, size);
    _bytes    += size;
    _position += size;
}

NS_MONKEY_END
