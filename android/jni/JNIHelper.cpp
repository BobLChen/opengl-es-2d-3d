#include "JNIHelper.h"
#include "core/utils/Log.h"
#include <pthread.h>

static pthread_key_t _key;

NS_MONKEY_BEGIN

JavaVM* 	JNIHelper::_vm 				= NULL;
jobject 	JNIHelper::classloader 		= NULL;
jmethodID 	JNIHelper::loadclassMethodID = NULL;

jclass JNIHelper::getClassID(const char* className) {
	if (!className) {
		return NULL;
	}
	JNIEnv *env = JNIHelper::getEnv();
	jstring jclassName = env->NewStringUTF(className);
	jclass  clazz 	   = (jclass)env->CallObjectMethod(JNIHelper::classloader, JNIHelper::loadclassMethodID, jclassName);
	
	if (clazz == NULL) {
		LOGE("ClassLoader can't find Class of %s", className);
		env->ExceptionClear();
	}
	
	env->DeleteLocalRef(jclassName);
	return clazz;
}

bool JNIHelper::setClassLoaderFrom(jobject activityinstance) {
	
	// 获取contextloader方法
	JniMethodInfo _getclassloaderMethod;
	if (!getMethodInfoDefaultClassLoader(_getclassloaderMethod, "android/content/Context", "getClassLoader", "()Ljava/lang/ClassLoader;")) {
		return false;
	}
	// 调用getClassLoader方法
	jobject _c = getEnv()->CallObjectMethod(activityinstance, _getclassloaderMethod.methodID);
	if (_c == NULL) {
		return false;
	}
	// 获取ClassLoader方法
	JniMethodInfo _m;
	if (!getMethodInfoDefaultClassLoader(_m, "java/lang/ClassLoader", "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;")) {
		return false;
	}
	// 全局引用
	classloader = getEnv()->NewGlobalRef(_c);
	loadclassMethodID = _m.methodID;
	
	return true;
}

bool JNIHelper::getMethodInfoDefaultClassLoader(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode) {
	
	if (!className || !methodName || !paramCode) {
		return false;
	}
	
	JNIEnv *env = getEnv();
	if (!env) {
		return false;
	}
	
	jclass classID = env->FindClass(className);
	if (!classID) {
		LOGE("Failed to find class %s", className);
		env->ExceptionClear();
		return false;
	}
	
	jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
	if (!methodID) {
		LOGE("Failed to find method id of %s", methodName);
		env->ExceptionClear();
		return false;
	}

	methodinfo.classID = classID;
	methodinfo.env = env;
	methodinfo.methodID = methodID;
	
	return true;
}


JavaVM* JNIHelper::getJavaVM() {
	return _vm;
}

void JNIHelper::setJavaVM(JavaVM *vm) {
	pthread_t thisthread = pthread_self();
	_vm = vm;
	pthread_key_create(&_key, NULL);
}

JNIEnv* JNIHelper::getEnv() {
	JNIEnv *_env = (JNIEnv *)pthread_getspecific(_key);
	if (_env == NULL) {
		_env = JNIHelper::cacheEnv(_vm);
	}
	return _env;
}

JNIEnv* JNIHelper::cacheEnv(JavaVM* jvm) {
	JNIEnv* _env = NULL;
	jint ret = jvm->GetEnv((void**)&_env, JNI_VERSION_1_4);
	switch (ret) {
		case JNI_OK:
			pthread_setspecific(_key, _env);
			return _env;
			break;
		case JNI_EDETACHED:
			if (jvm->AttachCurrentThread(&_env, NULL) < 0) {
				LOGE("Failed to get the environment using AttachCurrentThread()");
				return NULL;
			} else {
				pthread_setspecific(_key, _env);
				return _env;
			}
			break;
		case JNI_EVERSION:
			LOGE("JNI interface version 1.4 not supported");
			break;
		default:
			LOGE("Failed to get the environment using GetEnv()");
			return NULL;
			break;
	}
	return NULL;
}

std::string JNIHelper::jstring2string(jstring jstr) {
	if (jstr == NULL) {
		return "";
	}
	JNIEnv *env = JNIHelper::getEnv();
	if (!env) {
		return "";
	}
	const char* chars = env->GetStringUTFChars(jstr, NULL);
	std::string result(chars);
	env->ReleaseStringUTFChars(jstr, chars);
	return result;
}

bool JNIHelper::getStaticMethodInfo(JniMethodInfo &methodInfo, const char* className, const char* methodName, const char* paramCode) {
	
	if (!className || !methodName || !paramCode) {
		return false;
	}
	
	JNIEnv *env = JNIHelper::getEnv();
	if (!env) {
		LOGE("JNIEnv is null");
		return false;
	}
	
	jclass classID = getClassID(className);
	if (!classID) {
		LOGE("Can't find Class of %s", className);
		env->ExceptionClear();
		return false;
	}
	
	jmethodID methodID = env->GetStaticMethodID(classID, methodName, paramCode);
	if (!methodID) {
		LOGE("Can't find static method id of %s", methodName);
		env->ExceptionClear();
		return false;
	}
	
	methodInfo.classID = classID;
	methodInfo.env	   = env;
	methodInfo.methodID= methodID;
	
	return true;
}

NS_MONKEY_END
