package monkey.helper;

import java.util.HashMap;
import android.content.Context;
import android.graphics.Typeface;

public class MonkeyTypefaces {
	
	private static final HashMap<String, Typeface> TypefaceCache = new HashMap<String, Typeface>();
	
	public static synchronized Typeface get(final Context pContext, final String pAssetName) {
		if (!TypefaceCache.containsKey(pAssetName)) {
			Typeface typeface = null;
			if (pAssetName.startsWith("/")) {
				typeface = Typeface.createFromFile(pAssetName);
			} else {
				typeface = Typeface.createFromAsset(pContext.getAssets(), pAssetName);
			}
			TypefaceCache.put(pAssetName, typeface);
		}
		return TypefaceCache.get(pAssetName);
	}
	
}
