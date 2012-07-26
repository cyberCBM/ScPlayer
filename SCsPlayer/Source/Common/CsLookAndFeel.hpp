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

#ifndef hpp_LookAndFeel_hpp
#define hpp_LookAndFeel_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"

namespace GUI
{
    // Put all custom lookAndfeel for CsPlayer
    inline void useCsPlayerLookAndFeel()
    {
    }

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