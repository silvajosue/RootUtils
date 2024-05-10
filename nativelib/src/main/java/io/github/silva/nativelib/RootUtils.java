package io.github.silva.nativelib;

public class RootUtils {

    // Carregar a biblioteca nativa
    static {
        System.loadLibrary("rootutils");
    }

    public static native int checkRootAccessDirs();

    public static native int checkRootAccessSu();

    public static native int checkRootKeys();

    public static native int checkSuperUserApk();
}