#include "GLJNI.h"
#include "JNIHelper.h"
#include "MainDelegate.h"

#include "App.h"

#include "platform/android/GLViewAndroid.h"

#include "core/utils/Log.h"
#include "core/material/GLSLProgram.h"
#include "core/geom/Vector2D.h"
#include "core/event/TouchEvent.h"
#include "core/utils/Input3D.h"

#include "2d/scene/Scene2D.h"
#include "2d/entities/Quad.h"

USING_NS_MONKEY

static MainDelegate* delegate = NULL;

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIHelper::setJavaVM(vm);
    return JNI_VERSION_1_4;
}

/*
 * Class:     monkey_helper_GLJNI
 * Method:    onDrawFrame
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_monkey_helper_GLJNI_onDrawFrame(JNIEnv *, jclass) {
	App::getInstance()->update();
}

/*
 * Class:     monkey_helper_GLJNI
 * Method:    onSurfaceChanged
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_monkey_helper_GLJNI_onSurfaceChanged(JNIEnv *env, jclass jc, jint width, jint height) {
	App::getInstance()->setViewport(0, 0, width, height);
}

/*
 * Class:     monkey_helper_GLJNI
 * Method:    onSurfaceCreated
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_monkey_helper_GLJNI_onSurfaceCreated(JNIEnv *env, jclass jc, jint w, jint h) {
	GLViewAndroid *glview = new GLViewAndroid();
	App::getInstance()->setOpenGLView(glview);
	App::getInstance()->setBackcolor(0xFF00FF);
	App::getInstance()->setVisiableStats(true);
	App::getInstance()->setViewport(0, 0, w, h);
	
	delegate = new MainDelegate();
	delegate->didFinishLaunching();
}

JNIEXPORT void JNICALL Java_monkey_helper_GLJNI_touchesBegin(JNIEnv *, jclass, jint id, jfloat x, jfloat y) {
	Point2D *point = new Point2D(x, y);
	MouseEvent event(MouseEvent::TOUCH_BEGAN, true, point, 1);
	App::getInstance()->handleTouchesBegan(event);
	Input3D::mouseDown(point, 1);
	delete point;
}

/*
 * Class:     monkey_helper_GLJNI
 * Method:    touchesEnd
 * Signature: (IFF)V
 */
JNIEXPORT void JNICALL Java_monkey_helper_GLJNI_touchesEnd(JNIEnv *, jclass, jint, jfloat x, jfloat y) {
	Point2D *point = new Point2D(x, y);
	MouseEvent event(MouseEvent::TOUCH_END, true, point, 1);
	App::getInstance()->handleTouchesBegan(event);
	Input3D::mouseUP(point, 1);
	delete point;
}

/*
 * Class:     monkey_helper_GLJNI
 * Method:    touchesMove
 * Signature: ([I[F[F)V
 */
JNIEXPORT void JNICALL Java_monkey_helper_GLJNI_touchesMove(JNIEnv *env, jclass, jintArray ids, jfloatArray xs, jfloatArray ys) {
	int size = env->GetArrayLength(ids);
	jint   id[size];
	jfloat x[size];
	jfloat y[size];
	
	env->GetIntArrayRegion( ids, 0, size, id);
	env->GetFloatArrayRegion(xs, 0, size, x);
	env->GetFloatArrayRegion(ys, 0, size, y);
	
	Point2D *points = new Point2D[size];
	for (int i = 0; i < size; i++) {
		points[i].x = x[i];
		points[i].y = y[i];
	}
	
	MouseEvent event(MouseEvent::TOUCH_MOVE, true, points, size);
	App::getInstance()->handleTouchesBegan(event);
	Input3D::mouseMove(points, size);
	
	delete [] points;
}

/*
 * Class:     monkey_helper_GLJNI
 * Method:    touchesCancel
 * Signature: ([I[F[F)V
 */
JNIEXPORT void JNICALL Java_monkey_helper_GLJNI_touchesCancel(JNIEnv *, jclass, jintArray, jfloatArray, jfloatArray) {
	
}

/*
 * Class:     monkey_helper_GLJNI
 * Method:    onPause
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_monkey_helper_GLJNI_onPause(JNIEnv *, jclass) {
	App::getInstance()->pause();
}

/*
 * Class:     monkey_helper_GLJNI
 * Method:    onResume
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_monkey_helper_GLJNI_onResume(JNIEnv *, jclass) {
	App::getInstance()->resume();
}

