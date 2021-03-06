/*                                                                                  
*=====================================================================================
*ScPlayer - Server-Client Player ()													 |
*Music file player that plays Network stored songs                                   |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com                                                          |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
* ScPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the ScPlayer distribution, or can be found     |
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

namespace GUI 
{

// Used to sync (minimize,restore,close) Window
class MainAppWindow;

class MainComponent : public juce::Component
{
    //Members
private:
    /** Boolean to initialise the class only once in resized method */
    bool                            firstCall;
    /** Manager of panels : the smart component */
    ScopedPointer<DockManager>      manager;
    /** Right sided popup like panel might be having client lists and client related setting button */
    ScopedPointer<RightPanel>       rightPanel;
    /** Left sided popup like panel will have playList */
    ScopedPointer<LeftPanel>        leftPanel;

    //Methods
    public:
    // Component interface
    /** This resize and set components on screen */
    void resized ();

    RightPanel * getRightPanel();

    LeftPanel * getLeftPanel();

        // Constructor &  Destructor
    public:
        /** The constructor */
        MainComponent ();
        /** Destructor */
        ~MainComponent ();

    };
}
#endif //hpp_MainComponent_hpp