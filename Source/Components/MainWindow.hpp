/*
This file was auto-generated!
It contains the basic outline for a simple desktop window.
*/

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"
// custom LoolAndFeel
#include "../Common/LookAndFeel.hpp"

namespace GUI
{
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

#endif  // _MAINWINDOW_H
