#include <string.h>
#include <jni.h>
#include <time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <string>

const char *const ANDROID_OS_BUILD_TAGS = "ro.build.tags";
const char * const MG_SU_PATH[] = {
        "/data/local/",
        "/data/local/bin/",
        "/data/local/xbin/",
        "/sbin/",
        "/system/bin/",
        "/system/bin/.ext/",
        "/system/bin/failsafe/",
        "/system/sd/xbin/",
        "/su/xbin/",
        "/su/bin/",
        "/magisk/.core/bin/",
        "/system/usr/we-need-root/",
        "/system/xbin/",
        0
};


static char *concat2str(const char *pString1, const char *pString2) {
    char *result;
    size_t lengthBuffer = 0;

    lengthBuffer = strlen(pString1) +
                   strlen(pString2) + 1;
    result = static_cast<char *>(malloc(lengthBuffer));
    if (result == NULL) {
        return NULL;
    }
    memset(result, 0, lengthBuffer);
    strcpy(result, pString1);
    strcat(result, pString2);
    return result;
}

extern "C" JNIEXPORT int JNICALL Java_io_github_silva_nativelib_RootUtils_checkRootAccessDirs(
        JNIEnv* env, jobject thiz) {

    int result = -1;

    for(int i = 0; MG_SU_PATH[i]; i++) {
        char *checkedPath = concat2str(MG_SU_PATH[i], "su");
        result = access(checkedPath, F_OK);
    }

    int len;
    char build_tags[PROP_VALUE_MAX];
    len = __system_property_get(ANDROID_OS_BUILD_TAGS, build_tags);
    if(strcmp(build_tags, "test-keys") == 0) {
        result = 0;
    }
    return result;
}

extern "C" JNIEXPORT int JNICALL Java_io_github_silva_nativelib_RootUtils_checkRootAccessSu(
        JNIEnv* env, jobject thiz) {
    FILE* pipe = popen("which su", "r");
    if (!pipe) return -1;
    char buffer[128];
    std::string resultCmd = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            resultCmd += buffer;
    }
    pclose(pipe);

    const char *cstr = resultCmd.c_str();
    int result = -1;
    if(cstr == NULL || (strlen(cstr) == 0)){
        result = -1;
    } else {
        result = 0;
    }
    return result;
}

extern "C" JNIEXPORT int JNICALL Java_io_github_silva_nativelib_RootUtils_checkRootKeys(
        JNIEnv* env, jobject thiz) {

    int len;
    char build_tags[PROP_VALUE_MAX];
    int result = -1;
    len = __system_property_get(ANDROID_OS_BUILD_TAGS, build_tags);
    if (len > 0 && strstr(build_tags,"test-keys") != NULL) {
        result = 0;
    }

    return result;
}

extern "C" JNIEXPORT int JNICALL Java_io_github_silva_nativelib_RootUtils_checkSuperUserApk(JNIEnv* env, jobject thiz) {
    return access("/system/app/Superuser.apk", F_OK);
}

