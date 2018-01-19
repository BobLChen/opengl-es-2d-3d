//
//  BitmapData.h
//  Monkey
//
//  Created by Neil on 1/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __BitmapData__H_
#define __BitmapData__H_

#include "core/texture/Texture2D.h"
#include "platform/PlatformMacros.h"

#include <string>

NS_MONKEY_BEGIN

class BitmapData {
    
public:
    /**
     *  图片格式、暂只支持PNG，JPG
     */
    enum Format {
        JPG,
        PNG,
        UNKOWN
    };
    
    BitmapData();
    virtual ~BitmapData();
    
    /**
     *  通过文件名称初始化
     *  @param path         文件名称
     *  @return
     */
    bool initWithFile(const std::string &path);
    /**
     *  通过bytes初始化
     *  @param data 数据
     *  @param size 长度
     *  @return
     */
    bool initWithData(const unsigned char *data, ssize_t size);
    /**
     *  通过png数据初始化
     *  @param data png数据
     *  @param size 长度
     *  @return
     */
    bool initWithPNGData(const unsigned char *data, ssize_t size);
    /**
     *  通过jpg数据初始化
     *  @param data 数据
     *  @param size 长度
     *  @return
     */
    bool initWithJPGData(const unsigned char *data, ssize_t size);
    /**
     *  是否含有透明通道
     *  @return
     */
    bool hasAlpha();
    /**
     *  图片格式
     *  @return
     */
    Texture2D::PixelFormat& getPixcelFormat();
    /**
     *  图片宽度
     *  @return
     */
    int getWidth();
    /**
     *  图片高度
     *  @return
     */
    int getHeight();
    /**
     *  图片数据大小
     *  @return
     */
    ssize_t getSize();
    /**
     *  图片数据
     *  @return
     */
    unsigned char* getData();
    
protected:
    
    /**
     *  检测文件类型
     *  @param data 数据
     *  @param size 长度
     *  @return 图片类型
     */
    Format checkImageFormat(const unsigned char *data, ssize_t size);
    /**
     *  判断是否为PNG
     *  @param data 头信息
     *  @param size 头长度
     *  @return
     */
    bool   isPNG(const unsigned char *data, ssize_t size);
    /**
     *  判断是否为JPG
     *  @param data 头数据
     *  @param size 长度
     *  @return
     */
    bool   isJPG(const unsigned char *data, ssize_t size);
    
    std::string     _filePath;
    unsigned char   *_data;
    ssize_t         _dataSize;
    int             _width;
    int             _height;
    bool            _alpha;
    Texture2D::PixelFormat _renderFormat;
};

NS_MONKEY_END

#endif
