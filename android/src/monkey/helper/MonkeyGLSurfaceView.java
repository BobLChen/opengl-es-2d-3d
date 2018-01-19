package monkey.helper;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class MonkeyGLSurfaceView extends GLSurfaceView {

	private RenderWrapper wrapper;
	
	public MonkeyGLSurfaceView(Context context) {
		super(context);
		setEGLContextClientVersion(2);
	}
	
	@Override
	protected void onSizeChanged(int w, int h, int oldw, int oldh) {
		wrapper.setSize(w, h);
	}
	
	public void setRendererWrapper(RenderWrapper wrapper) {
		this.wrapper = wrapper;
		this.setRenderer(wrapper);
	}
	
}
