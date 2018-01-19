//
//  FileUtilsIOS.h
//  Monkey
//
//  Created by Neil on 24/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __FileUtilsAndroid__
#define __FileUtilsAndroid__

#include "platform/PlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/FileUtils.h"
#include "platform/PlatformMacros.h"

#include <android/asset_manager.h>

NS_MONKEY_BEGIN

class FileUtilsAndroid : public FileUtils {
    
public:
	
	FileUtilsAndroid();
	virtual ~FileUtilsAndroid();
	
	/**
	 * 设置AssetManager
	 * @manager 		资源管理器
	 */
	virtual void setAssetManager(AAssetManager *manager);
	/**
	 * 设置APK路径
	 */
	virtual void setAPKPath(const std::string &path);
	
	virtual std::string getStringFromFile(const std::string &fileName) override;
	
	virtual ByteArray* getFileData(const std::string &fileName, const char* model = nullptr) override;
	
	virtual std::string getFullPath(const std::string &filename) override;
	
	virtual bool isFileExist(const std::string &filename) override;
	
private:
    
    std::string 	_apkPath;
    AAssetManager 	*assetmanager;
};

NS_MONKEY_END

#endif

#endif
