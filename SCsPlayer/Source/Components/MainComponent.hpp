/*                                                                                  
*=====================================================================================
*CsPlayer - Simple Player (later It will be Server Player)                           |
*Music file player that works in Network                                             |
*Author: CsTeam                                                                      |
*Email: chaitanya.modi@gmail.com                                                     |
*Github: https://github.com/cyberCBM/CsPlayer.git                                    |
*                                                                                    |
*License: GNU2 License, Copyright (c) 2012 by CsTeam                                 |
* CsPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the CsPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

#ifndef hpp_MainComponent_hpp
#define hpp_MainComponent_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"
// ----- Docks -----
//We need Manager of panels : the smart component
#include "Dock/DockManager.hpp"
//We need Dock Panel 
#include "Dock/DockPanel.hpp"
//We need Dock Button 
#include "Dock/DockButtons.hpp"
// ----- Panels -----
//We need Right Panel
#include "Panels/RightPanel.hpp"
//We need Left Panel
#include "Panels/LeftPanel.hpp"
//We need Center Panel
#include "Panels/CenterPanel.hpp"
//We need Center Panel
#include "Panels/TopPanel.hpp"
// ----- AudioBuffer -----
#include "../Common/BufferTransformAudioSource.hpp"

namespace GUI 
{

// Used to sync (minimize,restore,close) Window
class MainAppWindow;

class MainComponent : public Component, public AudioIODeviceCallback, public DragAndDropContainer
{
    // Members
private:
    /** Boolean to initialise the class only once in resized method */
    bool                            firstCall;
    /** Manager of panels : the smart component */
    ScopedPointer<DockManager>      manager;
    /** Right sided popup like panel might be having client lists and client related setting button */
    ScopedPointer<RightPanel>       rightPanel;
    /** Left sided popup like panel will have playList */
    ScopedPointer<LeftPanel>        leftPanel;
    /** Center showing compontnes goes here (must be resizable - controls for player) */
    ScopedPointer<TopPanel>         topPanel;
    /** Center showing compontnes goes here (must be resizable - controls for player) */
    ScopedPointer<CenterPanel>      centerPanel;

    /** Audio Playing Helper members */
    AudioDeviceManager                              audioDeviceManager;
    AudioSourcePlayer                               audioSourcePlayer;
    drow::AudioFilePlayerExt                        audioFilePlayer;
    Configurations::BufferTransformAudioSource      bufferTransformAudioSource;

    //Methods
    public:
    // Component interface
    /** This resize and set components on screen */
    void resized ();
    /** Panel returning methods which give Panel through 
        MainComponent which are set in DockManager */
    LeftPanel   *   getLeftPanel();
    RightPanel  *   getRightPanel();
    CenterPanel *   getCenterPanel();
    TopPanel    *   getTopPanel();
    // AudioIODeviceCallback interface 
    void audioDeviceIOCallback (const float ** inputChannelData, int numInputChannels, float ** outputChannelData, int numOutputChannels, int numSamples);
    void audioDeviceAboutToStart (AudioIODevice * device);
    void audioDeviceStopped();

        // Constructor &  Destructor
    public:
        /** The constructor */
        MainComponent ();
        /** Destructor */
        ~MainComponent ();
        // (prevent copy constructor and operator= being generated..)
    private:
        MainComponent (const MainComponent&);
        const MainComponent& operator= (const MainComponent&);
    };
}
#endif //hpp_MainComponent_hpp