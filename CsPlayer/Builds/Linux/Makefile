# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  TARGET := ScPlayer-Client
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  TARGET := ScPlayer-Client
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/CsLookAndFeel_432d5433.o \
  $(OBJDIR)/DockHolder_98f7feab.o \
  $(OBJDIR)/DockManager_5aa3e8d8.o \
  $(OBJDIR)/DockPanel_aedaa52f.o \
  $(OBJDIR)/MainComponent_ec7554f4.o \
  $(OBJDIR)/MainWindow_8f66a223.o \
  $(OBJDIR)/ClockComponent_e43a7955.o \
  $(OBJDIR)/ClientControlComponent_2ee1fbd1.o \
  $(OBJDIR)/ClientSettingComponent_8a71b5be.o \
  $(OBJDIR)/PlayListComponent_57cda12f.o \
  $(OBJDIR)/LeftPanel_6e958c57.o \
  $(OBJDIR)/RightPanel_8524eab8.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/NetworkConnection_9cc051cc.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_49fc64dc.o \
  $(OBJDIR)/juce_audio_devices_4221f29a.o \
  $(OBJDIR)/juce_audio_formats_70a33c3a.o \
  $(OBJDIR)/juce_core_62c225be.o \
  $(OBJDIR)/juce_data_structures_2dd916fa.o \
  $(OBJDIR)/juce_events_632f8332.o \
  $(OBJDIR)/juce_graphics_3c1b7996.o \
  $(OBJDIR)/juce_gui_basics_657c2612.o \
  $(OBJDIR)/juce_gui_extra_c674b41a.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking CCsPlayer
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning CCsPlayer
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

$(OBJDIR)/CsLookAndFeel_432d5433.o: ../../Source/Common/CsLookAndFeel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CsLookAndFeel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DockHolder_98f7feab.o: ../../Source/Components/Dock/DockHolder.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DockHolder.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DockManager_5aa3e8d8.o: ../../Source/Components/Dock/DockManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DockManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DockPanel_aedaa52f.o: ../../Source/Components/Dock/DockPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DockPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainComponent_ec7554f4.o: ../../Source/Components/MainComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainWindow_8f66a223.o: ../../Source/Components/MainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ClockComponent_e43a7955.o: ../../Source/Components/PanelComponent/ClockComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ClockComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ClientControlComponent_2ee1fbd1.o: ../../Source/Components/PanelComponent/ClientControlComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ClientControlComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ClientSettingComponent_8a71b5be.o: ../../Source/Components/PanelComponent/ClientSettingComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ClientSettingComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PlayListComponent_57cda12f.o: ../../Source/Components/PanelComponent/PlayListComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PlayListComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LeftPanel_6e958c57.o: ../../Source/Components/Panels/LeftPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LeftPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RightPanel_8524eab8.o: ../../Source/Components/Panels/RightPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling RightPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NetworkConnection_9cc051cc.o: ../../Source/Network/NetworkConnection.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NetworkConnection.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_49fc64dc.o: ../../../../Juce/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_4221f29a.o: ../../../../Juce/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_70a33c3a.o: ../../../../Juce/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_62c225be.o: ../../../../Juce/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_2dd916fa.o: ../../../../Juce/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_632f8332.o: ../../../../Juce/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_3c1b7996.o: ../../../../Juce/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_657c2612.o: ../../../../Juce/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_c674b41a.o: ../../../../Juce/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
