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

#include "ClockComponent.hpp"

GUI::ClockComponent::ClockComponent()
{
    setTimeDisplayFormat (showTime + show24Hr + showSeconds);
    //setColour(backgroundColourId, Colour (91, 91, 91));
    setColour(textColourId, Colours::grey);
}

GUI::ClockComponent::~ClockComponent()
{
	stopTimer();
}

int GUI::ClockComponent::getRequiredWidth()
{
	return getFont().getStringWidth (timeAsString) + 10;
}

void GUI::ClockComponent::setTimeDisplayFormat(const int newFormat)
{	
	displayFormat = newFormat;
	
	if ((displayFormat & showDayShort) && (displayFormat & showDayLong))
		displayFormat -= showDayShort;
	if ((displayFormat & showTime))
		startTimer (5900);
	if ((displayFormat & showSeconds))
		startTimer (950);
//	if ((displayFormat & showTenthSeconds))
//		startTimer(99);
	
	timerCallback();
}

void GUI::ClockComponent::timerCallback()
{
	Time currentTime = Time::getCurrentTime();	
	timeAsString = String::empty;
	
	String formatString;
	formatString    << ((displayFormat & showDayShort)  ? "%a " : "")
                    << ((displayFormat & showDayLong)   ? "%A " : "")
                    << ((displayFormat & showDate)      ? "%x " : "")
                    << ((displayFormat & showTime)      ? ((displayFormat & show24Hr) ? "%H:%M" : "%I:%M") : "")
                    << ((displayFormat & showSeconds)   ? ":%S " : "");
	
	if (formatString != String::empty)
		timeAsString << currentTime.formatted (formatString);
	
	setText (timeAsString, false);
}

