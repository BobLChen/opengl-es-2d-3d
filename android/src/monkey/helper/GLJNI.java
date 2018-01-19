package monkey.helper;

/**
 * glview jni接口.
 * 通知c++渲染.
 * @author Neil
 *
 */
public class GLJNI {
	/**
	 * 加载渲染引擎
	 */
	public static void loadLibrary() {
		System.loadLibrary("monkeyandroid");
	}
	
	/**
	 * draw
	 */
	public static native void onDrawFrame();
	/**
	 * view change
	 * @param width		宽度
	 * @param height	高度
	 */
	public static native void onSurfaceChanged(int width, int height);
	/**
	 * create
	 * @param width		宽度
	 * @param height	高度
	 */
	public static native void onSurfaceCreated(int width, int height);
	// Touch事件
	/**
	 * TouchBegin
	 * @param id
	 * @param x
	 * @param y
	 */
	public static native void touchesBegin(final int id, final float x, final float y);
	
	/**
	 * TouchEnd
	 * @param id
	 * @param x
	 * @param y
	 */
	public static native void touchesEnd(final int id, final float x, final float y);
	
	/**
	 * TouchMove
	 * @param ids
	 * @param xs
	 * @param ys
	 */
	public static native void touchesMove(final int[] ids, final float[] xs, final float[] ys);

	/**
	 * 
	 * @param ids
	 * @param sx
	 * @param ys
	 */
	public static native void touchesCancel(final int[] ids, final float[] sx, final float[] ys);
	
	/**
	 * 暂停
	 */
	public static native void onPause();
	
	/**
	 * 恢复
	 */
	public static native void onResume();
	
}
