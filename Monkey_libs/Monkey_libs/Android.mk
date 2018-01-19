LOCAL_PATH := $(call my-dir)

$(info "---> Make Monkey_libs/Android.mk")

include $(CLEAR_VARS)
# 添加模块搜寻路径
$(call import-add-path, $(LOCAL_PATH)/../external)

# 模块名称
LOCAL_MODULE := monkey_static

# lib名称
LOCAL_MODULE_FILENAME := monkey

# 源文件
LOCAL_SRC_FILES := \
src/App.cpp \
src/2d/entities/BatchDisplayObject.cpp \
src/2d/entities/DisplayObject.cpp \
src/2d/entities/Image.cpp \
src/2d/entities/MovieClip.cpp \
src/2d/entities/Quad.cpp \
src/2d/material/ColorMaterial2D.cpp \
src/2d/material/Shaders2D.cpp \
src/2d/material/TextureMaterial2D.cpp \
src/2d/scene/Scene2D.cpp \
src/2d/ui/ProgressBar.cpp \
src/2d/ui/Slider.cpp \
src/2d/ui/Widget.cpp \
src/2d/ui/button/Button.cpp \
src/2d/ui/button/ButtonImage.cpp \
src/2d/ui/button/CheckBox.cpp \
src/2d/ui/font/Font.cpp \
src/2d/ui/font/FontCache.cpp \
src/2d/ui/font/FontFNT.cpp \
src/2d/ui/font/FontFNTConfig.cpp \
src/2d/ui/label/Label.cpp \
src/2d/ui/label/LabelFNT.cpp \
src/core/base/Object.cpp \
src/core/base/Pivot3D.cpp \
src/core/camera/Camera3D.cpp \
src/core/camera/lens/LensBase.cpp \
src/core/camera/lens/OrthographicLens.cpp \
src/core/camera/lens/OrthographicLens2D.cpp \
src/core/camera/lens/PerspectiveLens.cpp \
src/core/event/Event.cpp \
src/core/event/EventDispatcher.cpp \
src/core/event/KeyboardEvent.cpp \
src/core/event/TouchEvent.cpp \
src/core/geom/Matrix3D.cpp \
src/core/geom/Matrix3DUtils.cpp \
src/core/geom/Rectangle.cpp \
src/core/geom/Vector2D.cpp \
src/core/geom/Vector3D.cpp \
src/core/material/Geometry3D.cpp \
src/core/material/GLSLProgram.cpp \
src/core/material/Material3D.cpp \
src/core/scene/Scene.cpp \
src/core/texture/FrameTexture.cpp \
src/core/texture/Texture2D.cpp \
src/core/texture/TextureAtlas.cpp \
src/core/utils/BitmapData.cpp \
src/core/utils/ByteArray.cpp \
src/core/utils/Input3D.cpp \
src/core/utils/TextureCache.cpp \
src/core/utils/Value.cpp \
src/platform/FileUtils.cpp \
src/platform/GLView.cpp \
src/platform/TextureUtils.cpp \
src/platform/android/FileUtilsAndroid.cpp \
src/platform/android/GLViewAndroid.cpp \
../external/ConvertUTF/ConvertUTFWrapper.cpp \
../external/ConvertUTF/ConvertUTF.c \
../external/tinyxml2/tinyxml2.cpp \
../external/unzip/ioapi.cpp \
../external/unzip/unzip.cpp \
../external/edtaa3func/edtaa3func.cpp \
../external/xxhash/xxhash.c

# 头文件搜索路径
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include/
$(info "---> EXPORT_C_INCLUDES:", $(LOCAL_EXPORT_C_INCLUDES))

# 头文件搜索路径
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/ \
$(LOCAL_PATH)/../external/ConvertUTF \
$(LOCAL_PATH)/../external/tinyxml2 \
$(LOCAL_PATH)/../external/chipmunk/include/chipmunk \
$(LOCAL_PATH)/../external/json \

$(info "---> LOCAL_C_INCLUDES:", $(LOCAL_C_INCLUDES))

# libs
LOCAL_LDLIBS := -lGLESv2 \
-llog \
-lz \
-landroid

# libs
LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz \
                       -landroid
                       
LOCAL_WHOLE_STATIC_LIBRARIES := png_static jpeg_static tiff_static webp_static
# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   := -Wno-psabi  -DUSE_FILE32API
LOCAL_CPPFLAGS := -Wno-literal-suffix -Wno-deprecated-declarations
LOCAL_EXPORT_CFLAGS   := -Wno-psabi -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-literal-suffix -Wno-deprecated-declarations

# 编译成静态库
include $(BUILD_STATIC_LIBRARY)

$(call import-module, jpeg/prebuilt/android)
$(call import-module, png/prebuilt/android)
$(call import-module, tiff/prebuilt/android)
$(call import-module, webp/prebuilt/android)