package monkey.activity;

import monkey.helper.GLJNI;
import monkey.helper.JNIFileUtils;
import monkey.helper.MonkeyGLSurfaceView;
import monkey.helper.RenderWrapper;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.os.Build;
import android.os.Bundle;
import android.view.MotionEvent;
import android.widget.Toast;

public class MonkeyActivity extends Activity {

	private MonkeyGLSurfaceView glSurfaceView;
	private boolean		  		glInited;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		initGL();
		initFileUtils();
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		if (glInited) {
			glSurfaceView.onPause();
		}
	}

	@Override
	protected void onResume() {
		super.onResume();
		if (glInited) {
			glSurfaceView.onResume();
		}
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		
		final int size = event.getPointerCount();
		final int[] ids = new int[size];
		final float[] xs= new float[size];
		final float[] ys= new float[size];
		
		for (int i = 0; i < size; i++) {
			ids[i] 	= event.getPointerId(i);
			xs[i]	= event.getX(i);
			ys[i] 	= event.getY(i);
		}
		
		switch (event.getAction() & MotionEvent.ACTION_MASK) {
		case MotionEvent.ACTION_POINTER_DOWN:
			final int indexPointerDown 	= event.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
			final int idPointerDown 	= event.getPointerId(indexPointerDown);
			final float xPointerDown	= event.getX(indexPointerDown);
			final float yPointerDown	= event.getY(indexPointerDown);
			GLJNI.touchesBegin(idPointerDown, xPointerDown, yPointerDown);
			break;
		case MotionEvent.ACTION_DOWN:
			final int idDown  = event.getPointerId(0);
			final float xDown = xs[0];
			final float yDown = ys[0];
			GLJNI.touchesBegin(idDown, xDown, yDown);
			break;
		case MotionEvent.ACTION_MOVE:
			GLJNI.touchesMove(ids, xs, ys);
			break;
		case MotionEvent.ACTION_POINTER_UP:
			final int indexPointUp = event.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
			final int idPointerUp  = event.getPointerId(indexPointUp);
			final float xPointerUp = event.getX(indexPointUp);
			final float yPointerUp = event.getY(indexPointUp);
			GLJNI.touchesEnd(idPointerUp, xPointerUp, yPointerUp);
			break;
		case MotionEvent.ACTION_UP:
			final int idUp  = event.getPointerId(0);
			final float xUp = xs[0];
			final float yUp = ys[0];
			GLJNI.touchesEnd(idUp, xUp, yUp);
			break;
		case MotionEvent.ACTION_CANCEL:
			GLJNI.touchesCancel(ids, xs, ys);
			break;
		default:
			break;
		}
		
		return true;
	}

	/**
	 * 初始化FileUtils
	 */
	private void initFileUtils() {
		JNIFileUtils.setApkPath(getApplicationInfo().sourceDir);
		JNIFileUtils.setContext((Context)this, getAssets());
	}
	
	/**
	 * 初始化OpenglES、加载引起库
	 */
	private void initGL() {
		// 加载库
		GLJNI.loadLibrary();
		// 初始化opengl es
		ActivityManager manager	  = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
		ConfigurationInfo config  = manager.getDeviceConfigurationInfo();
		final boolean supportsES2 = config.reqGlEsVersion >= 0x20000 || isProbablyEmulator();
		if (supportsES2) {
			glSurfaceView = new MonkeyGLSurfaceView(this);
			if (isProbablyEmulator()) {
				glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
			}
			glSurfaceView.setRendererWrapper(new RenderWrapper());
			setContentView(glSurfaceView);
			glInited = true;
		} else {
			glInited = false;
			Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
		                Toast.LENGTH_LONG).show();
		}
	}
	
	/**
	 * 检测是否为模拟器
	 * @return
	 */
	private boolean isProbablyEmulator() {
		return Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
        && (Build.FINGERPRINT.startsWith("generic")
        		|| Build.FINGERPRINT.startsWith("unknown")
                || Build.MODEL.contains("google_sdk")
                || Build.MODEL.contains("Emulator")
                || Build.MODEL.contains("Android SDK built for x86"));
	}
	
}
