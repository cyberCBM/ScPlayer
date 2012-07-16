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
firstCall(true), manager(nullptr)
{
    addAndMakeVisible (manager = new DockManager());
    // top
    topPanel = new TopPanel();
    manager->setPanelComponent (TOP, topPanel);
    // center
    centerPanel = new CenterPanel();
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
    removeChildComponent(manager);
    removeChildComponent(topPanel);
    removeChildComponent(centerPanel);
    removeChildComponent(rightPanel);
    removeChildComponent(leftPanel);
    deleteAllChildren ();
}
void GUI::MainComponent::resized ()
{
    setSize(600, 300);
    if(manager)
        manager->setBounds (0, 0, getWidth(), getHeight());
}
void GUI::MainComponent::applyTranslation(const String & language)
{
    String filePath;
    if(language == "English")
    {
        filePath =  juce::File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + String("Translation") + File::separatorString + String("en.txt"); 
    }
    else if(language == "Hindi")
    {
        filePath = juce::File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + String("Translation") + File::separatorString + String("hn.txt"); 
    }
    else
    {
        filePath = juce::File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + String("Translation") + File::separatorString + String("en.txt");
    }
    LocalisedStrings * localisedStr;
    Logger::writeToLog(filePath);
    File languageFile(filePath);
    localisedStr = new LocalisedStrings(languageFile);
    LocalisedStrings::setCurrentMappings(localisedStr);
}

