## ScPlayer

ScPlayer "Server-Client Audio Player" is Juce(C++) based Music player for Network teams to play their network hosted music. ScPlayer uses C++ as programming language, And use JUCE and DrowAudio libraries. ScPlayer is Server Audio Player that can create playlist of music files and poses server which allows CsPlayer to connect to it. ScPlayer(Server) and CsPlayer(Client) are Manager kind of application, using which group of peoples in Network can play/pause Network hosted music ( Network hosted music means your music files should be stored on some network places that is accessible to both client and server player, i.e Samba server), change music and communicate to server.

## Platforms
All platforms supported by JUCE are will be also supported by ScPlayer. Currently these platform's Builds are avaialble.
- Windows: 		Applications can be built using MS Visual Studio. The results are all fully compatible with Windows XP, Vista or Windows 7.
- Mac OS X: 	Applications can be built with with Xcode. 
- GNU/Linux: 	Applications can be built for any kernel 2.6 or later using GCC libraries. 

## Prerequisites

This documentation assumes that the reader has a working knowledge of C++.

Documentation for Juce is avaialble at: http://www.rawmaterialsoftware.com/api/classes.html, which is used to create user interface and network interface

Documentation for DrowAudio is avaialble at: http://drowaudio.co.uk/docs/classes.html, which is used to create music playing.

## How to build

Requires latest versions of JUCE(https://github.com/julianstorer/JUCE.git). It will work with versions 2.22 or later. To use the library it is necessary to first download JUCE to a location where your development environment can find it. Get the drowAudio(https://github.com/drowaudio/drowaudio) and put this module into Juce's modules directory.

To use the module simply include it, or a symbolic link to it, in your juce/modules folder. Simply them run the Introjucer as normal and tick the dRowAudio module. Config flags are provided to disable some functionality if not required (For ScPlayer you must disable curl module if your are reconfiguring using IntroJucer).

Just put your downloaded directory parallel to the Juce directory. And you are ready to go now. You can change the part of code and build your own copy of ScPlayer(Server) and CsPlayer(Client).

#ScTeam

CsTeam is SUM of LoKo(people) willingly developes ScPlayer. CyberCBM Owns most rights[;-)] (Though GPUV2 Licence) and responsible for work inside ScPlayer. Other helping Members in ScTeam are NREZ, Hammer, ParT, Vrushabh. 

## License Copyright (C) 2012 by ScPlayer Team

Unless otherwise marked, files in ScPlayer are published under the GNU General Public License v2. A copy of the licence is contained within each source file.