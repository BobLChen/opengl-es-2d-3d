package monkey.helper;

public class JNIFileUtils {
	
	/**
	 * 设置apk路径
	 * @param path 路径
	 */
	public static native void setApkPath(final String path);
	/**
	 * 设置AssetsManager
	 * @param context		context
	 * @param assetManager	manager
	 */
	public static native void setContext(final Object context, final Object assetManager);
	
}
