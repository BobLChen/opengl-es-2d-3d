//
//  FileUtils.cpp
//  Monkey
//
//  Created by Neil on 24/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "platform/FileUtils.h"
#include "core/utils/Log.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

FileUtils* FileUtils::_instance = nullptr;

FileUtils::FileUtils() {
    
}

FileUtils::~FileUtils() {
    
}

/**
 *  读取文件
 *  @param filename 文件名
 *  @param mode     模式
 *  @param size     文件大小
 *  @return
 */
static unsigned char* readFile(const std::string &filename, const char *mode, unsigned int &size) {
    
    if (filename.empty()) {
        LOGI("File:%s is null.\n", filename.c_str());
        return NULL;
    }
    
    unsigned char* buffer = nullptr;
    
    std::string fullPath = FileUtils::getInstance()->getFullPath(filename);
    // 打开文件
    FILE *fp = fopen(fullPath.c_str(), mode);
    
    if (!fp) {
        LOGI("Open File:%s Faild.\n", fullPath.c_str());
        return nullptr;
    }
    // 获取文件长度
    fseek(fp, 0, SEEK_END);
    size = (unsigned int)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    // 读取文本文件
    if (strcmp(mode, "rt") == 0) {
        buffer = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
    } else {
        buffer = (unsigned char*)malloc(sizeof(unsigned char) * size);
    }
    
    fread(buffer, size, 1, fp);
    // 读取文件文件
    if (strcmp(mode, "rt") == 0) {
        buffer[size] = '\0';
    }
    
    // 关闭文件
    fclose(fp);
    
    return buffer;
}

std::string FileUtils::getStringFromFile(const std::string &filename) {
    unsigned int size = 0;
    unsigned char* buf = readFile(filename, "rt", size);
    std::string result((const char*)buf);
    delete [] buf;
    return result;
}

ByteArray* FileUtils::getFileData(const std::string &filename, const char *mode) {
    std::string path = getFullPath(filename);
    unsigned int size = 0;
    unsigned char* data = nullptr;
    if (mode == nullptr) {
        data = readFile(path, "rb", size);
    } else {
        data = readFile(path, mode, size);
    }
    ByteArray *bytes = new ByteArray(data, size);
    return bytes;
}

std::string FileUtils::getFullPath(const std::string &filename) {
    return nullptr;
}

bool FileUtils::isFileExist(const std::string &filename) {
    return true;
}

bool FileUtils::isAbsolutePath(const std::string &path) const {
    return  true;
}

bool FileUtils::init() {
    return true;
}

void FileUtils::dispose() {
    if (_instance) {
        delete _instance;
    }
}

NS_MONKEY_END