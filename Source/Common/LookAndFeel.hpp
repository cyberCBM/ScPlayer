#ifndef hpp_LookAndFeel_hpp
#define hpp_LookAndFeel_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"

namespace GUI
{
    namespace CSGraphics
    {
        /** Main Player related Colors */
        extern Colour csPBackGroundColor;
        extern Colour csPFontColour;
        extern Colour csPForGroundColor;
        extern Colour csPForMouseOnColor;
        extern Colour csPForMouseOffColor;

        /** Titlebar related Colors */
        extern Colour titleBarBackGroundColor;
        extern Colour titleBarFontColour;
        extern Colour titleBarForGroundColor;
        extern Colour titleBarThemeColor;

        // Put all custom lookAndfeel for CsPlayer
        inline void useCsPlayerLookAndFeel()
        {
        }



        /** Look And Feel class to change tablel column background */
        class CsPlayerLookAndFeel : public LookAndFeel
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
            CsPlayerLookAndFeel ();
                /** Destructor */
            ~CsPlayerLookAndFeel ();

        };
    }
}

#endif // hpp_LookAndFeel_hpp