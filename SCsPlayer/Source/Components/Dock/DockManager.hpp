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
#ifndef hpp_DockManager_hpp
#define hpp_DockManager_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
//We need Dock holder 
#include "DockHolder.hpp"
//We need Dock panel
#include "DockPanel.hpp"

namespace GUI 
{
    class DockManager : public Component,
        public ButtonListener,
        public ComponentListener,
        public DragAndDropContainer, 
        private Timer
    {

        // Members
    private:
        /** Dock Holders in which stack and ultimately component is managed */
        DockHolder * top,* center, * left, * right;
        /** Drawable button to dock panels */
        DrawableButton * leftButton, * rightButton;
        ComponentAnimator animator;
        MouseEvent * lastMouseEvent;
        
        // Members
    protected:
        friend class DockHolder;

        //Methods
    protected:

        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);
        void mouseEnter (const MouseEvent & e);
        void mouseExit (const MouseEvent & e);
        
        // ComponentListener interface
        void componentMovedOrResized (Component & component, bool wasMoved, bool wasResized);
        void mousePropagation (const MouseEvent & e, const int position);

        // ButtonListener interface
        void buttonClicked (Button * button);
        
        // Timer interface
        void timerCallback ();
        
    public:
        // Class Methods
        void setOpenWithoutAnimation (const int position, bool open);
        void setOpenWithAnimation (const int positionPanel, bool lockAutomaticAnimation = false);
        void forceCloseWithAnimation (const int positionPanel, bool lockAutomaticAnimation = false);
        bool isDocked (const int position);
        void setPanelComponent (const int position, Component * component);
        void lockAutomaticAnimationForPanel (const int positionPanel, bool lockAutomaticAnimation);
        bool isLockedAutomaticAnimationForPanel(const int positionPanel);
        bool getToggleState(const int positionPanel);
        /** used to check memory leaks */
        juce_UseDebuggingNewOperator

        //Constructor & Destructor
    public:
        /** Constructor */
        DockManager ();
        /** Destructor */
        ~DockManager ();
    };
}
#endif // hpp_DockManager_hpp
