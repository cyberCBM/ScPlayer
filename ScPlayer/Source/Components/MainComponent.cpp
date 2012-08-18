/*                                                                                  
*=====================================================================================
*ScPlayer - Server Client Player                                                                   |
*Music file player that works in Network                                             |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com															 |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
*                                                                                    |
*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
* ScPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the ScPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

// We need our basic class definitions
#include "MainComponent.hpp"
// We need mainWindow
#include "MainWindow.hpp"

GUI::MainComponent::MainComponent () : 
firstCall(true), bufferTransformAudioSource (&audioFilePlayer), manager(nullptr),
    topPanel(nullptr), centerPanel(nullptr), rightPanel(nullptr), leftPanel(nullptr)
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
    setSize(600, 400);
    manager->setBounds (0, 0, getWidth(), getHeight());
}

void GUI::MainComponent::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels, float** outputChannelData, int numOutputChannels, int numSamples)
{
    audioSourcePlayer.audioDeviceIOCallback (inputChannelData, numInputChannels, outputChannelData, numOutputChannels, numSamples);

    // Add samples to segment meter to show some hilchal 
    if(centerPanel)
    {
        if(centerPanel->getPlayerComponent())
        {
            getCenterPanel()->getPlayerComponent()->getMeterL()->copySamples (outputChannelData[0], numSamples);
            if (numOutputChannels > 1)
                getCenterPanel()->getPlayerComponent()->getMeterR()->copySamples (outputChannelData[1], numSamples);
        }
    }

}

void GUI::MainComponent::audioDeviceAboutToStart (AudioIODevice* device)
{
    audioSourcePlayer.audioDeviceAboutToStart (device);
}

void GUI::MainComponent::audioDeviceStopped()
{
    audioSourcePlayer.audioDeviceStopped();
}

GUI::LeftPanel * GUI::MainComponent::getLeftPanel()
{
    if(leftPanel)
        return leftPanel;
    else
        return 0;
}

GUI::RightPanel * GUI::MainComponent::getRightPanel()
{
    if(rightPanel)
        return rightPanel;
    else
        return 0;
}

GUI::CenterPanel * GUI::MainComponent::getCenterPanel()
{
    if(centerPanel)
        return centerPanel;
    else
        return 0;
}

GUI::TopPanel * GUI::MainComponent::getTopPanel()
{
    if(topPanel)
        return topPanel;
    else
        return 0;
}