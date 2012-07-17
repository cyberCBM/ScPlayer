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

// We need our basic class definitions
#include "MainComponent.hpp"
// We need mainWindow
#include "MainWindow.hpp"

GUI::MainComponent::MainComponent () : 
firstCall(true), bufferTransformAudioSource (&audioFilePlayer)
{
    audioSourcePlayer.setSource (&bufferTransformAudioSource);
    audioDeviceManager.initialise (2, 2, 0, true, String::empty, 0);
    audioDeviceManager.addAudioCallback (this);

    manager = new DockManager();
    addAndMakeVisible (manager);
    // top
    topPanel = new TopPanel(audioDeviceManager, audioFilePlayer);
    manager->setPanelComponent (TOP, topPanel);
    // center
    centerPanel = new CenterPanel(audioDeviceManager, audioFilePlayer);
    manager->setPanelComponent (CENTER, centerPanel);
    // left
    leftPanel = new LeftPanel();
    manager->setPanelComponent (LEFT, leftPanel);
    //right
    rightPanel = new RightPanel();
    manager->setPanelComponent (RIGHT,  rightPanel);
}
GUI::MainComponent::~MainComponent ()
{
    audioSourcePlayer.setSource (nullptr);
    audioDeviceManager.removeAudioCallback (this);
    removeChildComponent(manager);
    removeChildComponent(rightPanel);
    removeChildComponent(leftPanel);
    removeChildComponent(topPanel);
    removeChildComponent(centerPanel);
}
void GUI::MainComponent::resized ()
{
    setSize(600, 300);
    manager->setBounds (0, 0, getWidth(), getHeight());
}

void GUI::MainComponent::audioDeviceIOCallback (const float** inputChannelData,
                                           int numInputChannels,
                                           float** outputChannelData,
                                           int numOutputChannels,
                                           int numSamples)
{
    audioSourcePlayer.audioDeviceIOCallback (inputChannelData,
                                             numInputChannels,
                                             outputChannelData,
                                             numOutputChannels,
                                             numSamples);
    
}

void GUI::MainComponent::audioDeviceAboutToStart (AudioIODevice* device)
{
    audioSourcePlayer.audioDeviceAboutToStart (device);
}

void GUI::MainComponent::audioDeviceStopped()
{
    audioSourcePlayer.audioDeviceStopped();
}

