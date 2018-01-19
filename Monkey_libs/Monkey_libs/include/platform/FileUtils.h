//
//  FileUtils.h
//  Monkey
//
//  Created by Neil on 24/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __FileUtils__
#define __FileUtils__

#include "core/utils/ByteArray.h"
#include "core/utils/Value.h"
#include "platform/PlatformMacros.h"

#include <string>
#include <vector>

NS_MONKEY_BEGIN

class FileUtils {
    
public:
    /**
     *  获取FileUtils实例
     *  @return
     */
    static FileUtils* getInstance();
    /**
     *  获取文本
     *  @param filename 文件名
     *  @return
     */
    virtual std::string getStringFromFile(const std::string &filename);
    /**
     *  获取文件数据
     *  @param filename 文件名
     *  @param mode     打开模式
     *  @return
     */
    virtual ByteArray*  getFileData(const std::string &filename, const char* mode = nullptr);
    /**
     *  获取全路径
     *  @param filename 文件名
     *  @return
     */
    virtual std::string getFullPath(const std::string &filename);
    /**
     *  检测文件是否存在
     *  @param filename 文件名
     *  @return
     */
    virtual bool isFileExist(const std::string &filename);
    /**
     *  判断是否为绝对路径
     *  @param path 路径
     *  @return
     */
    virtual bool isAbsolutePath(const std::string &path) const;
    /**
     *  销毁
     *  @return
     */
    virtual void dispose();
    
private:
    
protected:
    
    FileUtils();
    virtual ~FileUtils();
    
    /**
     * 初始化
     */
    virtual bool init();
    
    static FileUtils* _instance;
    
};

NS_MONKEY_END;

#endif
