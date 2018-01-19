#include "platform/android/FileUtilsAndroid.h"
#include "core/utils/Log.h"

NS_MONKEY_BEGIN

FileUtilsAndroid::FileUtilsAndroid() : FileUtils(), _apkPath(""), assetmanager(NULL) {
	
}

FileUtilsAndroid::~FileUtilsAndroid() {
	
}

void FileUtilsAndroid::setAPKPath(const std::string &path) {
	_apkPath = path;
}

void FileUtilsAndroid::setAssetManager(AAssetManager *manager) {
	assetmanager = manager;
}

std::string FileUtilsAndroid::getStringFromFile(const std::string &fileName) {
	if (fileName.empty()) {
		return nullptr;
	}
	
	AAsset* asset 	= AAssetManager_open(FileUtilsAndroid::assetmanager, fileName.c_str(), AASSET_MODE_UNKNOWN);
	off_t  fileSize = AAsset_getLength(asset);
	unsigned char* data = (unsigned char*) malloc(fileSize + 1);
	AAsset_read(asset, (void*)data, fileSize);
	AAsset_close(asset);
	
	data[fileSize] = '\0';
	std::string ret((const char*)data);
	
	return ret;
}

ByteArray* FileUtilsAndroid::getFileData(const std::string &fileName, const char*model) {
	if (fileName.empty()) {
		return nullptr;
	}
	
	AAsset* asset 	= AAssetManager_open(FileUtilsAndroid::assetmanager, fileName.c_str(), AASSET_MODE_UNKNOWN);
	off_t  fileSize = AAsset_getLength(asset);
	unsigned char* data = (unsigned char*) malloc(fileSize);
	AAsset_read(asset, (void*)data, fileSize);
	AAsset_close(asset);
	
	ByteArray *bytes = new ByteArray(data, fileSize);
	return bytes;
}

std::string FileUtilsAndroid::getFullPath(const std::string &filename) {
	return filename;
}

bool FileUtilsAndroid::isFileExist(const std::string &fileName) {
	if (fileName.empty()) {
		return false;
	}
	bool result = false;
	if (fileName[0] != '/') {
		AAsset* asset = AAssetManager_open(assetmanager, fileName.c_str(), AASSET_MODE_UNKNOWN);
		if (asset) {
			result = true;
			AAsset_close(asset);
		}
	} else {
		FILE *fp = fopen(fileName.c_str(), "r");
		if (fp) {
			fclose(fp);
			result = true;
		}
	}
	return result;
}

FileUtils* FileUtils::getInstance() {
    if (!_instance) {
        _instance = new FileUtilsAndroid();
    }
    return _instance;
}

NS_MONKEY_END
