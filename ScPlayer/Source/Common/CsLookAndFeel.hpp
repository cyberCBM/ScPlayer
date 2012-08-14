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

#ifndef hpp_LookAndFeel_hpp
#define hpp_LookAndFeel_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"

namespace GUI
{
    /** Look And Feel class to change tablel column background */
    class CsLookAndFeel : public LookAndFeel
    {

    public:

        void drawTableHeaderBackground (Graphics & g, TableHeaderComponent & header);

        void drawTableHeaderColumn (Graphics & g, const String & columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags);

        void drawScrollbarButton(Graphics & g, ScrollBar & scrollbar,int width, int height, int buttonDirection, bool /*isScrollbarVertical*/, bool isMouseOverButton, bool isButtonDown);

        void drawScrollbar (Graphics & g, ScrollBar & scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown);

        inline ImageEffectFilter * getScrollbarEffect()
        {
            return 0;
        }
        inline int getMinimumScrollbarThumbSize(ScrollBar & scrollbar)
        {
            return jmin (scrollbar.getWidth(), scrollbar.getHeight());
        }
        inline int getDefaultScrollbarWidth()
        {
            return 15;
        }
        inline int getScrollbarButtonSize (ScrollBar & scrollbar)
        {
            return 2 + (scrollbar.isVertical() ? scrollbar.getWidth(): scrollbar.getHeight());
        }

        /** Constructor */
        CsLookAndFeel ();
        /** Destructor */
        ~CsLookAndFeel ();

    };
}

#endif // hpp_LookAndFeel_hpp