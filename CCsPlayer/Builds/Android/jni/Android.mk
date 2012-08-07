# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := juce_jni
LOCAL_SRC_FILES := \
  ../../../Source/Common/CsLookAndFeel.cpp\
  ../../../Source/Network/NetworkConnection.cpp\
  ../../../Source/Components/Dock/DockHolder.cpp\
  ../../../Source/Components/Dock/DockManager.cpp\
  ../../../Source/Components/Dock/DockPanel.cpp\
  ../../../Source/Components/MainComponent.cpp\
  ../../../Source/Components/MainWindow.cpp\
  ../../../Source/Components/PanelComponent/BusyWheel.cpp\
  ../../../Source/Components/PanelComponent/ClientControlComponent.cpp\
  ../../../Source/Components/PanelComponent/ClientSettingComponent.cpp\
  ../../../Source/Components/PanelComponent/PlayListComponent.cpp\
  ../../../Source/Components/Panels/LeftPanel.cpp\
  ../../../Source/Components/Panels/RightPanel.cpp\
  ../../../Source/Main.cpp\
  ../../../JuceLibraryCode/BinaryData.cpp\
  ../../../../../Juce/modules/dRowAudio/dRowAudio.cpp\
  ../../../../../Juce/modules/juce_audio_basics/juce_audio_basics.cpp\
  ../../../../../Juce/modules/juce_audio_devices/juce_audio_devices.cpp\
  ../../../../../Juce/modules/juce_audio_formats/juce_audio_formats.cpp\
  ../../../../../Juce/modules/juce_audio_processors/juce_audio_processors.cpp\
  ../../../../../Juce/modules/juce_audio_utils/juce_audio_utils.cpp\
  ../../../../../Juce/modules/juce_core/juce_core.cpp\
  ../../../../../Juce/modules/juce_data_structures/juce_data_structures.cpp\
  ../../../../../Juce/modules/juce_events/juce_events.cpp\
  ../../../../../Juce/modules/juce_graphics/juce_graphics.cpp\
  ../../../../../Juce/modules/juce_gui_basics/juce_gui_basics.cpp\
  ../../../../../Juce/modules/juce_gui_extra/juce_gui_extra.cpp\

ifeq ($(CONFIG),Debug)
  LOCAL_CPPFLAGS += -fsigned-char -fexceptions -frtti -g -I "../../JuceLibraryCode" -O0 -D "JUCE_ANDROID=1" -D "JUCE_ANDROID_API_VERSION=8" -D "JUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_CCsPlayer" -D JUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/CCsPlayer\" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_ANDROID_7F0E4A25=1"
  LOCAL_LDLIBS := -llog -lGLESv2
else
  LOCAL_CPPFLAGS += -fsigned-char -fexceptions -frtti -I "../../JuceLibraryCode" -Os -D "JUCE_ANDROID=1" -D "JUCE_ANDROID_API_VERSION=8" -D "JUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_CCsPlayer" -D JUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/CCsPlayer\" -D "NDEBUG=1" -D "JUCER_ANDROID_7F0E4A25=1"
  LOCAL_LDLIBS := -llog -lGLESv2
endif

include $(BUILD_SHARED_LIBRARY)
