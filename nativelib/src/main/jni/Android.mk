LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := rootutils
LOCAL_SRC_FILES := rootutils.cpp
LOCAL_LDLIBS := -llog
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_CPPFLAGS := -std=c++11

include $(BUILD_SHARED_LIBRARY)