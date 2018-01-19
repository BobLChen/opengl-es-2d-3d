//
//  FontFNTConfig.h
//  Monkey
//
//  Created by Neil on 24/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _FontFNTConfig_h
#define _FontFNTConfig_h

#include "core/base/Object.h"

#include <string>
#include <map>
#include <vector>

NS_MONKEY_BEGIN

typedef struct {
    int     id;
    float   x;
    float   y;
    float   width;
    float   height;
    short   xoffset;
    short   yoffset;
    short   xadvance;
    int     pages;
    int chnl;
} FNTChar;

typedef struct {
    int first;
    int second;
    int amount;
} FNTkerning;

class FontFNTConfig : public Object {
    
public:
    
    FontFNTConfig(std::string filepath);
    virtual ~FontFNTConfig();
    
    /**
     *  padding.top
     *  @return
     */
    int getTop();
    /**
     *  padding.bottom
     *  @return
     */
    int getBottom();
    /**
     *  padding.left
     *  @return
     */
    int getLeft();
    /**
     *  padding.right
     *  @return
     */
    int getRight();
    /**
     *  行高
     *  @return
     */
    int getCommonHeight();
    /**
     *  贴图高度
     *  @return
     */
    int getScaleH();
    /**
     *  贴图宽度
     *  @return
     */
    int getScaleW();
    /**
     *  页数
     *  @return
     */
    int getPages();
    /**
     *  贴图路径
     *  @return
     */
    std::string                 &getImagePath();
    /**
     *  字符集
     *  @return
     */
    std::map<int, FNTChar>      &getChars();
    /**
     *  字距
     *  @return
     */
    std::map<unsigned int, FNTkerning>   &getKernings();
    
protected:
    /**
     *  解析fnt文件
     *  @param filepath
     */
    void parse(const std::string &filepath);
    /**
     *  解析二进制的fnt
     *  @param data
     *  @param size
     */
    void parseBinaryFNT(unsigned char* data, unsigned long size);
    /**
     *  解析fnt文件参数
     *  @param line
     */
    void parseInfoArguments(std::string line);
    /**
     *  解析commom
     *  @param line
     */
    void parseCommonArguments(std::string line);
    /**
     *  解析page相关信息
     *  @param line
     */
    void parseImageName(std::string line);
    /**
     *  解析chars
     *  @param line
     */
    void parseChars(std::string line);
    /**
     *  解析char
     *  @param line
     */
    void parseChar(std::string line);
    /**
     *  解析kernnings
     *  @param line
     */
    void parseKernnings(std::string line);
    /**
     *  解析kernning
     *  @param line
     */
    void parseKernning(std::string line);
    
    // padding
    int _top;
    int _bottom;
    int _left;
    int _right;
    // common
    int _commonHeight;
    int _scaleW;
    int _scaleH;
    int _pages;
    std::string _imagePath;
    // char
    std::map<int, FNTChar>              _chars;
    std::map<unsigned int, FNTkerning>  _kernings;
};

NS_MONKEY_END

#endif
