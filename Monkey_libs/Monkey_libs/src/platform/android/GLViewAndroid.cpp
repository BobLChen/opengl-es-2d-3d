#include "platform/android/GLViewAndroid.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

GLViewAndroid::GLViewAndroid() : GLView() {
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_STENCIL_TEST);
	
	_eaglview = this;
}

GLViewAndroid::~GLViewAndroid() {
	
}

bool GLViewAndroid::isOpenGLReady() {
	return true;
}

void GLViewAndroid::swapBuffers() {
	
}

void GLViewAndroid::setIMEKeyboardState(bool open) {
	
}

NS_MONKEY_END
