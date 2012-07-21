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


#ifndef hpp_BusyWheel_hpp
#define hpp_BusyWheel_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"

namespace GUI
{
    class BusyWheel :   public juce::Component, 
                            public juce::Timer
    {
            // Type definition and enumeration
        public:
            typedef juce::Path              Path;
            typedef juce::Colour            Colour;
            typedef juce::Colours           Colours;
            typedef juce::AffineTransform   AffineTransform;
            typedef juce::Graphics          Graphics;
            /** The busy wheel style */
            enum Style
            {
                UZIGradient     = 0,    //!< Draw a nicely colored gradient with lovely petal
                PointStyle      = 1,    //!< Point based circle
            };

            // Members
        public:
            /** A petal bounding box */
            float           x, y, petalWidth, petalHeight;
            /** A petal path */
            Path            petalPath;
            /** The petal number */
            int             petalNumber;
            /** The wheel style */
            const Style     petalStyle;
            /** The current petal iterator */
            int             petalIterator;
            /** The base color used */
            const Colour    petalColour;

            // Helpers
        private:
            /** Get the transform for the given petal index */
            const AffineTransform getTransform(int index) const;
            // Methods
        public:
            // Component interface
            /** Paint this component */
            void paint(Graphics & g);
            /** Called when this component has been resized */
            void resized();
            /** Called when this component's visibility is changed */
            void visibilityChanged();
            // Timer interface
            /** The user-defined callback routine that actually gets called periodically. */
            void timerCallback();

            // Construction and destruction
        public:
            /** Constructor : We need to know what to draw while waiting 
                @param[in]  Style   Style to draw busy wheel
                @param[in]  number  Number of patel or circles to draw
                @param[in]  Colour  Color to show for patel or circles */
            BusyWheel(const Style wheelStyle = UZIGradient, const int number = 12, const Colour colour = Colours::red);
            /** Destructor */ 
            ~BusyWheel();
    };
}
#endif // hpp_BusyWheel_hpp