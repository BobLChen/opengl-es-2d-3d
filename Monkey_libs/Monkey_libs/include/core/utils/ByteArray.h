//
//  ByteArray.h
//  Monkey
//
//  Created by Neil on 24/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __ByteArray__
#define __ByteArray__

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class ByteArray {
    
public:
    
    ByteArray(unsigned char* datas, unsigned int size):_bytes(datas), _length(size), _position(0){};
    ~ByteArray();
    /**
     *  获取游标位置
     *  @return
     */
    unsigned int getPosition();
    /**
     *  获取数据长度
     *  @return
     */
    unsigned int getLength();
    /**
     *  设置游标位置
     *  @param pos
     */
    void setPosition(unsigned int pos);
    /**
     *  读取int
     *  @return
     */
    int readInt();
    /**
     *  读取float
     *  @return
     */
    float readFloat();
    /**
     *  读取bytes
     *  @param bytes bytes
     *  @param size  长度
     */
    void readBytes(unsigned char *bytes, unsigned size);
    /**
     *  获取bytes
     *  @return
     */
    unsigned char*  getBytes();
    /**
     *  是否为空
     *  @return
     */
    bool            isNull();
    
private:
    unsigned char*  _bytes;
    unsigned int    _position;
    unsigned int    _length;
};

NS_MONKEY_END

#endif
