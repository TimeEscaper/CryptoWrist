LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := curl-prebuild
LOCAL_SRC_FILES := libcurl.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := jansson-prebuild
LOCAL_SRC_FILES := libjansson.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := mainactivitylib
LOCAL_SRC_FILES += com_cryptowrist_MainActivity.cpp webclient.cpp utils.cpp btcaddress.cpp blockcypherapi.cpp
#LOCAL_LDLIBS := -ljansson
LOCAL_SHARED_LIBRARIES := curl-prebuild 
LOCAL_STATIC_LIBRARIES := jansson-prebuild

include $(BUILD_SHARED_LIBRARY)
