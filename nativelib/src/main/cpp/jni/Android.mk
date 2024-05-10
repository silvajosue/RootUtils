LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := rootutils
LOCAL_SRC_FILES := rootutils.cpp
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)