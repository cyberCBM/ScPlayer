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
*A copy of the license is included in the CsPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

#ifndef hpp_ClockComponent_hpp
#define hpp_ClockComponent_hpp

#include "../JuceLibraryCode/JuceHeader.h"

/**	A handy digital graphical clock. Just add one of these to your component and it will display the time,
continually updating itself. Set the look and feel of it as you would a normal label. */
namespace GUI
{
    class ClockComponent : public Label, public Timer
    {
    public:
        /**	A number of flags to set what sort of clock is displayed */
        enum TimeDisplayFormat
        {
            showDate = 1,
            showTime = 2,
            showSeconds = 4,
            show24Hr = 8,
            showDayShort = 16,
            showDayLong = 32,
        };
    

        /**	Sets the display format of the clock.
            To specify what sort of clock to display pass in a number of the
            TimeDisplayFormat flags. This is semi-inteligent so may choose to
            ignore certain flags such as the short day name if you have also
            specified the long day name.        */
        void setTimeDisplayFormat (const int newFormat);

        /**	Returns the width required to display all of the clock's information. */
        int getRequiredWidth();

        //==============================================================================
        /** @internal */
        void timerCallback();

    private:
        int displayFormat;
        String timeAsString;

    public:
        /**	Constructor.
        Just add and make visible one of these to your component and it
        will display the current time and continually update itself. */
        ClockComponent();

        /**	Destructor. */
        ~ClockComponent();
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClockComponent);
    };
}
#endif  // hpp_ClockComponent_hpp