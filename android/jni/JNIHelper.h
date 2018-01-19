#ifndef __ANDROID_JNI_HELPER_H__
#define __ANDROID_JNI_HELPER_H__

#include <jni.h>
#include <string>
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

typedef struct JniMethodInfo_ {
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;

class JNIHelper {
	
public:
	
	/**
	 * 设置jvm
	 * @param vm    jvm
	 */
	static void 	setJavaVM(JavaVM *vm);
	/**
	 * 获取jvm
	 * @return
	 */
	static JavaVM* 	getJavaVM();
	/**
	 * 获取JNIEnv
	 */
	static JNIEnv*	getEnv();
	/**
	 * java字符串转string
	 * @param str	字符串
	 */
	static std::string jstring2string(jstring str);
	/**
	 * 设置classloader
	 * @param activityinstance
	 */
	static bool setClassLoaderFrom(jobject activityinstance);
	
	static bool getMethodInfoDefaultClassLoader(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);
	
	static bool getStaticMethodInfo(JniMethodInfo &methodInfo, const char* className, const char* methodName, const char* paramCode);
	
	static jclass getClassID(const char* className);
	
	static jmethodID 	loadclassMethodID;
	static jobject 		classloader;
		
private:
	
	static JNIEnv* cacheEnv(JavaVM* jvm);
	
	static JavaVM* 		_vm;
	
};

NS_MONKEY_END

#endif
