## CsPlayer

CsPlayer "Client Server Audio Player" is Juce(C++) based Music player for Network teams to play their server hosted music in the network. CsPlayer uses C++ as source language. And use JUCE and DrowAudio libraries.CsPlayer is Server Audio Player and Client player Manager kind of application, using which group of peoples in Network can add music, change music and stop too.

## Platforms
All platforms supported by JUCE are will be also supported by CsPlayer. Currently these platforms include: Current Builds avaialble only for 
- Windows: 		Applications and VST/RTAS/NPAPI/ActiveX plugins can be built using MS Visual Studio. The results are all fully compatible with Windows XP, Vista or Windows 7.
- Mac OS X: 	Applications and VST/AudioUnit/RTAS/NPAPI plugins with Xcode. 
- GNU/Linux: 	Applications and plugins can be built for any kernel 2.6 or later. 
- iOS: 			Native iPhone and iPad apps. 
- Android: 		Supported for 2.0 or above. 

## Prerequisites

This documentation assumes that the reader has a working knowledge of JUCE and DrowAudio.

Documentation for Juce is avaialble at: http://www.rawmaterialsoftware.com/api/classes.html

Documentation for DrowAudio is avaialble at: http://drowaudio.co.uk/docs/classes.html

## External Modules

Currently no other than Juce and DrowAudio I have used inside modules, but if they do require any external libraries or modules we will put here.

## Integration 

Requires recent versions of JUCE. It won't work with versions 2.20 or earlier. To use the library it is necessary to first download JUCE to a location where your development environment can find it. Or, you can use your existing installation of JUCE.

To use the module simply include it, or a symbolic link to it, in your juce/modules folder. Simply them run the Introjucer as normal and tick the dRowAudio module. Config flags are provided to disable some functionality if not required.

Just put your downloaded directory parallel to the Juce directory (It will onbly required when we will remove hard links) Currently all the modules from Juce and DrowAudio are hard put in build files.

#CsTeam

CsTeam is SUM of LoKo(people) willingly developes CsPlayer. CyberCBM Owns most rights (Though GPUV2 Licence) and responsible for work inside CsPlayer. Other helping Members in CsTeam are NREZ, Hammer, ParT, Vrushabh. NREZ around playerComponent to play/pause, stop, next, previous audio files, Hammer around Client player and nework realated work, ParT work to create playList and playList related facilities, Vrushabh's work is to manage Client players that connect to Server Player.

## License Copyright (C) 2012 by CsPlayer Team

Unless otherwise marked, files in CsPlayer are published under the GNU General Public License v2. A copy of the licence is contained within each source file.