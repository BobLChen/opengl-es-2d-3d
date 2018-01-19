#include "TextureUtilsAndroid.h"
#include "JNIHelper.h"
#include <jni.h>

#include "core/utils/Log.h"

NS_MONKEY_BEGIN

TextureInfo* TextureUtilsAndroid::sharedInfo = NULL;

static bool initWithString(const char* text, TextAlign align, const char *fontName, int size, TextureInfo *info) {
	
	JniMethodInfo methodInfo;
	if (!JNIHelper::getStaticMethodInfo(methodInfo, "monkey/helper/TextureUtils", "createTextBitmapShadowStroke",
		   "(Ljava/lang/String;Ljava/lang/String;IFFFIIIZFFFFZFFFF)Z")) {
		   LOGE("%s %d: error to get methodInfo", __FILE__, __LINE__);
		   return false;
	}
	
	jstring jstrText = JNIHelper::getEnv()->NewStringUTF(text);
	jstring jstrFont = JNIHelper::getEnv()->NewStringUTF(fontName);
	
	if (!info->hasShadow) {
		info->offsetX = 0.0f;
		info->offsetY = 0.0f;
		info->shadowBlur 	= 0.0f;
		info->shadowOpacity = 0.0f;
	}
	if (!info->hasStroke) {
		info->strokeR = 0.0f;
		info->strokeG = 0.0f;
		info->strokeB = 0.0f;
		info->strokeSize = 0.0f;
	}
	
	if (!methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, 
			jstrText, jstrFont, (int)size, 
			info->tintR, 	info->tintG, 	info->tintB,  	align, info->width, info->height, 
			info->hasShadow, info->offsetX, -info->offsetY, info->shadowBlur, 	info->shadowOpacity, 
			info->hasStroke, info->strokeR, info->strokeG, 	info->strokeB, 		info->strokeSize
	)) {
		return false;
	}
	
	methodInfo.env->DeleteLocalRef(jstrText);
	methodInfo.env->DeleteLocalRef(jstrFont);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
	
	return true;
}

ByteArray* TextureUtilsAndroid::getTextureDataWithText(const char* text, const TextFormatter &format, int &width, int &height, bool &hasAlpha) {
	
	TextureInfo info;
    info.width  = format.width;
    info.height = format.height;
    info.hasShadow = format.shadow.enabled;
    info.offsetX   = format.shadow.offsetX;
    info.offsetY   = format.shadow.offsetY;
    info.shadowBlur= format.shadow.shadowBlur;
    info.shadowOpacity = format.shadow.shadowOpacity;
    info.hasStroke = format.stroke.enabled;
    info.strokeR   = format.stroke.red;
    info.strokeG   = format.stroke.green;
    info.strokeB   = format.stroke.blue;
    info.strokeSize= format.stroke.size;
    info.tintR     = format.fontFillColorR;
    info.tintG     = format.fontFillColorG;
    info.tintB     = format.fontFillColorB;
    
    // 共享info
    TextureUtilsAndroid::sharedInfo = &info;
    
    if (!initWithString(text, format.align, format.fontName.c_str(), format.fontSize, &info)) {
    	return NULL;
    }
    
    height	= info.height;
    width	= info.width;
    hasAlpha= info.isPremultipliedAlpha;
    
    ByteArray *bytes = new ByteArray(info.data, width * height * 4);
    
	return bytes;
}

TextureUtils* TextureUtils::getInstance() {
    if (_instance == nullptr) {
        _instance = new TextureUtilsAndroid();
    }
    return _instance;
}

NS_MONKEY_END

extern "C"
{
    /**
    * this method is called by java code to init width, height and pixels data
    */
    JNIEXPORT void JNICALL Java_monkey_helper_TextureUtils_nativeInitBitmapDC(JNIEnv*  env, jobject thiz, int width, int height, jbyteArray pixels) {
        int size = width * height * 4;
        monkey::TextureUtilsAndroid::sharedInfo->width  = width;
        monkey::TextureUtilsAndroid::sharedInfo->height = height;
        monkey::TextureUtilsAndroid::sharedInfo->data   = (unsigned char*)malloc(sizeof(unsigned char) * size);
        monkey::TextureUtilsAndroid::sharedInfo->isPremultipliedAlpha = true;
        env->GetByteArrayRegion(pixels, 0, size, (jbyte*)monkey::TextureUtilsAndroid::sharedInfo->data);
    }
};
