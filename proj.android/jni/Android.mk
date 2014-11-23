LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Helpers.cpp \
				   ../../Classes/airplane/Airplane.cpp \
				   ../../Classes/airplane/Character.cpp \
				   ../../Classes/airplane/Toilet.cpp \
				   ../../Classes/scenes/SceneFinish.cpp \
				   ../../Classes/scenes/SceneMenu.cpp \
				   ../../Classes/scenes/SceneGame.cpp \
				   ../../Classes/passenger/Passenger.cpp \
				   ../../Classes/passenger/Man.cpp \
				   ../../Classes/passenger/Steward.cpp \
				   ../../Classes/passenger/Trolley.cpp \
				   ../../Classes/UserGameData.cpp \
				   ../../Classes/SoundManager/SoundManager.cpp \
				   ../../Classes/sky/Sky.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
