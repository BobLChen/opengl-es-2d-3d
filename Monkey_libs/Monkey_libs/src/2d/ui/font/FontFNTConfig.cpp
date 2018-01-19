//
//  FontFNTConfig.cpp
//  Opengl2D
//
//  Created by Neil on 24/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "App.h"
#include "2d/ui/font/FontFNTConfig.h"
#include "platform/FileUtils.h"
#include "core/utils/Log.h"

NS_MONKEY_BEGIN

#define FNT_INFO_FACE           "info face"
#define FNT_COMMON_LINE_HEIGHT  "common lineHeight"
#define FNT_PAGE_ID             "page id"
#define FNT_CHARS               "chars"
#define FNT_CHAR                "char"
#define FNT_KERNINGS            "kernings"
#define FNT_KERNING             "kerning"

FontFNTConfig::FontFNTConfig(std::string filepath) :
Object(),
_top(0),
_bottom(0),
_left(0),
_right(0),
_commonHeight(0),
_scaleW(0),
_scaleH(0),
_pages(0)
{
    parse(filepath);
}

FontFNTConfig::~FontFNTConfig() {
    
}

int FontFNTConfig::getTop() {
    return _top;
}

int FontFNTConfig::getBottom() {
    return _bottom;
}

int FontFNTConfig::getLeft() {
    return _left;
}

int FontFNTConfig::getRight() {
    return _right;
}

int FontFNTConfig::getCommonHeight() {
    return _commonHeight;
}

int FontFNTConfig::getScaleH() {
    return _scaleH;
}

int FontFNTConfig::getScaleW() {
    return _scaleW;
}

int FontFNTConfig::getPages() {
    return _pages;
}

std::string& FontFNTConfig::getImagePath() {
    return _imagePath;
}

std::map<int, FNTChar>& FontFNTConfig::getChars() {
    return _chars;
}

std::map<unsigned int, FNTkerning>& FontFNTConfig::getKernings() {
    return _kernings;
}

/**
 *  @param data
 *  @param size
 */
void FontFNTConfig::parseBinaryFNT(unsigned char *data, unsigned long size) {
    if (data[3] != 3) {
        LOGE("Only Verison 3 is Supported!");
        return;
    }
    
    unsigned long remains = size;
    data    += 4;
    remains += 4;
    
    while (remains > 0) {
        unsigned char blockID = data[0];
        data    += 1;
        remains -= 1;
        
        uint32_t blockSize = 0;
        memcpy(&blockSize, data, 4);
        data    += 4;
        remains -= 4;
        
        if (blockID == 1) {
            _top    = (unsigned char)data[7];
            _right  = (unsigned char)data[8];
            _bottom = (unsigned char)data[9];
            _left   = (unsigned char)data[10];
        } else if (blockID == 2) {
            memcpy(&_commonHeight, data, 2);
            memcpy(&_scaleW, data + 4, 2);
            memcpy(&_scaleH, data + 6, 2);
            memcpy(&_pages,  data + 8, 2);
            if (_pages > 1 || _scaleW > App::getInstance()->getMaxTextureSize() || _scaleH > App::getInstance()->getMaxTextureSize()) {
                LOGE("Not supported Fnt");
            }
        } else if (blockID == 3) {
            const char *value = (const char*)data;
            _imagePath = FileUtils::getInstance()->getFullPath(value);
        } else if (blockID == 4) {
            unsigned long count = blockSize / 20;
            for (unsigned long i = 0; i < count; i++) {
                FNTChar charItem;
                
                unsigned long step = i * 20;
                memcpy(&charItem.id, data + step, 4);
                memcpy(&charItem.x,  data + step + 4, 2);
                memcpy(&charItem.y,  data + step + 6, 2);
                memcpy(&charItem.width,   data + step + 8, 2);
                memcpy(&charItem.height,  data + step + 10, 2);
                memcpy(&charItem.xoffset, data + step + 12, 2);
                memcpy(&charItem.yoffset, data + step + 14, 2);
                memcpy(&charItem.xadvance,data + step + 16, 2);
                
                _chars.insert(std::make_pair(charItem.id, charItem));
            }
        } else if (blockID == 5) {
            unsigned long count = blockSize / 20;
            for (unsigned long i = 0; i < count; i++) {
                unsigned long step = i * 10;
                FNTkerning kerningItem;
                memcpy(&kerningItem.first,  data + step, 4);
                memcpy(&kerningItem.second, data + step + 4, 4);
                memcpy(&kerningItem.amount, data + step + 8, 2);
                int key = (kerningItem.first << 16) | (kerningItem.second & 0xFFFF);
                _kernings.insert(std::make_pair(key, kerningItem));
            }
        }
        data    += blockSize;
        remains -= blockSize;
    }
}

void FontFNTConfig::parse(const std::string &filepath) {
    ByteArray* data = FileUtils::getInstance()->getFileData(filepath);
    
    if (data->isNull()) {
        LOGE("Fnt file not found:%s", filepath.c_str());
        return;
    }
    
    if (memcmp("BMF", data->getBytes(), 3) == 0) {
        // TODO:解析二进制格式
        parseBinaryFNT(data->getBytes(), data->getLength());
        delete data;
        return;
    }
    
    std::string content((const char*)data->getBytes(), data->getLength());
    std::string line;
    
    while (content.length() > 0) {
        
        size_t pos = content.find("\n");
        
        if (pos != std::string::npos) {
            line    = content.substr(0, pos);
            content = content.substr(pos + 1);
        } else {
            line    = content;
            content.erase();
        }
        
        if (line.substr(0, strlen(FNT_INFO_FACE)) == FNT_INFO_FACE) {
            parseInfoArguments(line);
        } else if (line.substr(0, strlen(FNT_COMMON_LINE_HEIGHT)) == FNT_COMMON_LINE_HEIGHT) {
            parseCommonArguments(line);
        } else if (line.substr(0, strlen(FNT_PAGE_ID)) == FNT_PAGE_ID) {
            parseImageName(line);
        } else if (line.substr(0, strlen(FNT_CHARS)) == FNT_CHARS) {
            parseChars(line);
        } else if (line.substr(0, strlen(FNT_CHAR)) == FNT_CHAR) {
            parseChar(line);
        } else if (line.substr(0, strlen(FNT_KERNINGS)) == FNT_KERNINGS) {
            parseKernnings(line);
        } else if (line.substr(0, strlen(FNT_KERNING)) == FNT_KERNING) {
            parseKernning(line);
        }
        
    }
    
    delete data;
}

void FontFNTConfig::parseInfoArguments(std::string line) {
    auto index1 = line.find("padding=");
    auto index2 = line.find(' ', index1);
    auto value  = line.substr(index1, index2 - index1);
    sscanf(value.c_str(), "padding=%d,%d,%d,%d", &_top, &_right, &_bottom, &_left);
}

void FontFNTConfig::parseCommonArguments(std::string line) {
    
    auto index1 = line.find("lineHeight=");
    auto index2 = line.find(' ', index1);
    auto value  = line.substr(index1, index2 - index1);
    sscanf(value.c_str(), "lineHeight=%d", &_commonHeight);
    
    index1 = line.find("scaleW=");
    index2 = line.find(' ', index1);
    value  = line.substr(index1, index2 - index1);
    sscanf(value.c_str(), "scaleW=%d", &_scaleW);
    
    index1 = line.find("scaleH=");
    index2 = line.find(' ', index1);
    value  = line.substr(index1, index2 - index1);
    sscanf(value.c_str(), "scaleH=%d", &_scaleH);
    
    index1 = line.find("pages=");
    index2 = line.find(' ', index1);
    value  = line.substr(index1, index2 - index1);
    sscanf(value.c_str(), "pages=%d", &_pages);
    
    if (_scaleW > App::getInstance()->getMaxTextureSize() || _scaleH > App::getInstance()->getMaxTextureSize()) {
        LOGE("Fnt's Texture Size is %dx%d more than %d", _scaleW, _scaleH, App::getInstance()->getMaxTextureSize());
    }
}

void FontFNTConfig::parseImageName(std::string line) {
    auto index1 = line.find('"')  + 1;
    auto index2 = line.find('"', index1);
    _imagePath = line.substr(index1, index2 - index1);
}

void FontFNTConfig::parseChars(std::string line) {
    // nothing
}

void FontFNTConfig::parseChar(std::string line) {
    FNTChar charItem;
    
    auto index  = line.find("id=");
    auto index2 = line.find(' ', index);
    auto value  = line.substr(index, index2 - index);
    sscanf(value.c_str(), "id=%u", &charItem.id);
    
    // Character x
    index  = line.find("x=");
    index2 = line.find(' ', index);
    value  = line.substr(index, index2 - index);
    sscanf(value.c_str(), "x=%f", &charItem.x);
    // Character y
    index  = line.find("y=");
    index2 = line.find(' ', index);
    value  = line.substr(index, index2 - index);
    sscanf(value.c_str(), "y=%f", &charItem.y);
    // Character width
    index  = line.find("width=");
    index2 = line.find(' ', index);
    value  = line.substr(index, index2 - index);
    sscanf(value.c_str(), "width=%f", &charItem.width);
    // Character height
    index  = line.find("height=");
    index2 = line.find(' ', index);
    value  = line.substr(index, index2 - index);
    sscanf(value.c_str(), "height=%f", &charItem.height);
    // Character xoffset
    index  = line.find("xoffset=");
    index2 = line.find(' ', index);
    value  = line.substr(index, index2 - index);
    sscanf(value.c_str(), "xoffset=%hd", &charItem.xoffset);
    // Character yoffset
    index  = line.find("yoffset=");
    index2 = line.find(' ', index);
    value  = line.substr(index, index2-index);
    sscanf(value.c_str(), "yoffset=%hd", &charItem.yoffset);
    // Character xadvance
    index  = line.find("xadvance=");
    index2 = line.find(' ', index);
    value  = line.substr(index, index2-index);
    sscanf(value.c_str(), "xadvance=%hd", &charItem.xadvance);
    
    _chars.insert(std::make_pair(charItem.id, charItem));
}

void FontFNTConfig::parseKernnings(std::string line) {
    // nothing
}

void FontFNTConfig::parseKernning(std::string line) {
    FNTkerning kerningItem;
    
    auto index  = line.find("first=");
    auto index2 = line.find(' ', index);
    std::string value = line.substr(index, index2 - index);
    sscanf(value.c_str(), "first=%d", &kerningItem.first);
    
    index  = line.find("second=");
    index2 = line.find(' ', index);
    value  = line.substr(index, index2 - index);
    sscanf(value.c_str(), "second=%d", &kerningItem.second);
    
    index  = line.find("amount=");
    index2 = line.find(' ', index);
    value  = line.substr(index, index2 - index);
    sscanf(value.c_str(), "amount=%d", &kerningItem.amount);
    
    unsigned int key = (kerningItem.first << 16) | (kerningItem.second & 0xFFFF);
    _kernings.insert(std::make_pair(key, kerningItem));
}

NS_MONKEY_END