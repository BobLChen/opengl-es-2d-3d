LOCAL_PATH := $(call my-dir)

# monkey模块
include $(CLEAR_VARS)
# 添加模块搜寻路径
$(call import-add-path, $(LOCAL_PATH)/../../Monkey_libs)

MODULE_PATHS := $(LOCAL_PATH)/../../Monkey_libs
# 模块名称
LOCAL_MODULE := monkeyandroid
# class路径
CLASSES_SRC := ../../classes
# 源文件
JNI_SOURCES := GLJNI.cpp \
JNIFileUtils.cpp \
JNIHelper.cpp \
TextureUtilsAndroid.cpp \
$(CLASSES_SRC)/MainDelegate.cpp \
$(CLASSES_SRC)/HelloWorld.cpp


# 源文件
LOCAL_SRC_FILES += $(JNI_SOURCES)
# 头文件
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../classes
# lib
LOCAL_LDLIBS := -lGLESv1_CM \
                -lGLESv2 \
                -lEGL \
                -llog \
                -lz \
                -landroid
                
# 关联静态库
LOCAL_WHOLE_STATIC_LIBRARIES := monkey_static
# 编译成共享库
include $(BUILD_SHARED_LIBRARY)
# 引入模块
$(call import-module, Monkey_libs)