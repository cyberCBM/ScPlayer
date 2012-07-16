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

#ifndef hpp_MainWindow_hpp
#define hpp_MainWindow_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"

namespace GUI
{
    class MainAppWindow;

    // Just add a simple icon to the Window system tray area..
    class TaskbarComponent  : public SystemTrayIconComponent
    {
    public:
        TaskbarComponent(MainAppWindow & );

        //{
        //    // Create an icon which is just a square with a "j" in it..
        //    Image icon (Image::RGB, 32, 32, true);
        //    Graphics g (icon);
        //    g.fillAll (Colours::lightblue);
        //    g.setColour (Colours::black);
        //    g.setFont (Font ((float) icon.getHeight(), Font::bold));
        //    g.drawText ("j", 0, 0, icon.getWidth(), icon.getHeight(), Justification::centred, false);

        //    setIconImage (icon);

        //    setIconTooltip ("Juce Demo App!");
        //}

        void mouseDown (const MouseEvent & e);
        void mouseDoubleClick (const MouseEvent & e);

        /*{
            PopupMenu m;
            m.addItem (1, "Open Player");
            m.addItem (2, "Quit Player");
            const int result = m.show();
            if (result == 1)
                
            else if(result == 2)
                JUCEApplication::getInstance()->systemRequestedQuit();
        }*/
    };

    class MainAppWindow   : public DocumentWindow
    {
        // methods
    public:
        void closeButtonPressed();

        //int getDesktopWindowStyleFlags() const;
        /* Note: Be careful when overriding DocumentWindow methods - the base class
        uses a lot of them, so by overriding you might break its functionality.
        It's best to do all your work in you content component instead, but if
        you really have to override any DocumentWindow methods, make sure your
        implementation calls the superclass's method.
        */
    public:
        MainAppWindow();
        ~MainAppWindow();
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAppWindow)
    };
}

#endif  // hpp_MainWindow_hpp
