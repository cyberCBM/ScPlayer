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

#ifndef hpp_Protocols_hpp
#define hpp_Protocols_hpp

// Juce related definitions go here
#include "../JuceLibraryCode/JuceHeader.h"

namespace Configurations
{
    /** The class to store the communication definitions between Client and Server CSP */
    class Protocols
    {
    private:
        String messageSeparator;
        String firstTimeNameID;
    
    public:
        inline String getFirstTimeName(){ return firstTimeNameID; }

        String constructFirstTimeName(const String & name)
        {
            String message = firstTimeNameID + name ;
            return message;
        }

        bool isFirstTimeName(const String & message, String & name)
        {
            String tempMessage = message;
            if(tempMessage.contains(firstTimeNameID))
            {
                name = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }

    public:
        /** Constructor */
        Protocols() : messageSeparator("__"), firstTimeNameID("firstTimeName" + messageSeparator)
        {
        }
    };

    
}

#endif // hpp_Protocols_hpp