# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := juce_jni
LOCAL_SRC_FILES := \
  ../../../Source/Common/BufferTransformAudioSource.cpp\
  ../../../Source/Common/LookAndFeel.cpp\
  ../../../Source/Components/PanelComponents/ClientListComponent.cpp\
  ../../../Source/Components/PanelComponents/ControlBarComponent.cpp\
  ../../../Source/Components/PanelComponents/PlayerComponent.cpp\
  ../../../Source/Components/PanelComponents/PlayListComponent.cpp\
  ../../../Source/Components/Dock/DockHolder.cpp\
  ../../../Source/Components/Dock/DockManager.cpp\
  ../../../Source/Components/Dock/DockPanel.cpp\
  ../../../Source/Components/MainComponent.cpp\
  ../../../Source/Components/MainWindow.cpp\
  ../../../Source/Components/Panels/CenterPanel.cpp\
  ../../../Source/Components/Panels/LeftPanel.cpp\
  ../../../Source/Components/Panels/RightPanel.cpp\
  ../../../Source/Components/Panels/TopPanel.cpp\
  ../../../Source/Main.cpp\
  ../../../JuceLibraryCode/BinaryData.cpp\
  ../../../JuceLibraryCode/modules/dRowAudio/dRowAudio.cpp\
  ../../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp\
  ../../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp\
  ../../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp\
  ../../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp\
  ../../../JuceLibraryCode/modules/juce_audio_utils/juce_audio_utils.cpp\
  ../../../JuceLibraryCode/modules/juce_core/juce_core.cpp\
  ../../../JuceLibraryCode/modules/juce_cryptography/juce_cryptography.cpp\
  ../../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp\
  ../../../JuceLibraryCode/modules/juce_events/juce_events.cpp\
  ../../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp\
  ../../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp\
  ../../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp\
  ../../../JuceLibraryCode/modules/juce_opengl/juce_opengl.cpp\
  ../../../JuceLibraryCode/modules/juce_video/juce_video.cpp\

ifeq ($(CONFIG),Debug)
  LOCAL_CPPFLAGS += -fsigned-char -fexceptions -frtti -g -I "../../JuceLibraryCode" -O0 -D "JUCE_ANDROID=1" -D "JUCE_ANDROID_API_VERSION=8" -D "JUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_SCsPlayer" -D JUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/SCsPlayer\" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_ANDROID_7F0E4A25=1"
  LOCAL_LDLIBS := -llog -lGLESv2
else
  LOCAL_CPPFLAGS += -fsigned-char -fexceptions -frtti -I "../../JuceLibraryCode" -Os -D "JUCE_ANDROID=1" -D "JUCE_ANDROID_API_VERSION=8" -D "JUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_SCsPlayer" -D JUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/SCsPlayer\" -D "NDEBUG=1" -D "JUCER_ANDROID_7F0E4A25=1"
  LOCAL_LDLIBS := -llog -lGLESv2
endif

include $(BUILD_SHARED_LIBRARY)
