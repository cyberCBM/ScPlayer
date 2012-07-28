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

#ifndef hpp_cpp_Protocols_cpp_hpp
#define hpp_cpp_Protocols_cpp_hpp

// Juce related definitions go here
#include "../JuceLibraryCode/JuceHeader.h"

namespace Configurations
{
    /** The class to store the communication definitions between Client and Server CSP */
    class Protocols
    {
    private:
        /** string for message separator */
        String messageSeparator;
        /** Name of client when it connect to server first time */
        String firstTimeNameID;
        /**  Name of client when it try to connect to server */
        String connectTimeNameID;
        /** no access error message */
        String noAccessMessageID;
        
        /** pause message string */
        String pauseMessageID;
        /** stop message string */
        String stopMessageID;
        /** next message string */
        String nextMessageID;
        /** back message string */
        String backMessageID;

        /** playafterpause message string */
        String playAfterPauseMessageID;
        /** playafterstop message string */
        String playAfterStopMessageID;
    
    public:
        // All String read methods
        /** This will return name of client when it connect to server first time
            @param[out] firstTimeNameID     Name of client when it connect to server first time */
        inline String getFirstTimeNameID(){ return firstTimeNameID; }
        /** This will return name of client when it connect to server
            @param[out] connectTimeNameID     Name of client when it try to connect to server */
        inline String getConnectTimeNameID(){ return connectTimeNameID; }
        /** This will return error message no access to client 
            @param[out] noAccessMessageID     no access error message */
        inline String getMoAccessMessageID(){ return noAccessMessageID; }
        /** This will return pause message when pause button clicked on player
            @param[out] pauseMessageID      pause message string  */
        inline String getpauseMessageID(){ return pauseMessageID; }
        /** This will return stop message when stop button clicked on player
            @param[out] stopMessageID     stop message  string */
        inline String getstopMessageID(){ return stopMessageID; }
        /** This will return next message when next button clicked on player
            @param[out] nextMessageID     next message string */
        inline String getnextMessageID(){ return nextMessageID; }
        /** This will return back message when back button clicked on player
            @param[out] backMessageID     back message string */
        inline String getbackMessageID(){ return backMessageID; }
        /** This will return playafterpause message when play button clicked after paused button clicked
            @param[out] playAfterPauseMessageID     playafter pause message string  */
        inline String getplayAfterPauseMessageID(){ return playAfterPauseMessageID; }
        /** This will return playafterstop message when play button clicked after stop button clicked
            @param[out] playAfterStopMessageID     playafterstop message string  */
        inline String getplayAfterStopMessageID(){ return playAfterStopMessageID; }
        // All String Message Constructions 
        
        /** This will construct First time client name 
            @param[in]  name        string
            @param[out] message     First time client name  */
        String constructFirstTimeName(const String & name)
        {
            String message = firstTimeNameID + name ;
            return message;
        }
        /** This will construct connection time client name 
            @param[in]  name        string
            @param[out] message     connection time client name  */
        String constructConnectTimeName(const String & name)
        {
            String message = connectTimeNameID + name ;
            return message;
        }
        /** This will construct error message no access
            @param[in]  errorMessage        string
            @param[out] message             error message no access  */
        String constructNoAccessMessage(const String & errorMessage)
        {
            String message = noAccessMessageID + errorMessage ;
            return message;
        }
        /** This will construct pause message for pause button clicked in player
            @param[in]  pauseMsg        string
            @param[out] message         pause message string  */
        String constructPauseMessage(const String & pauseMsg)
        {
            String message = pauseMessageID + pauseMsg ;
            return message;
        }
        /** This will construct stop message for stop button clicked in player
            @param[in]  stopMsg         string
            @param[out] message         stop message string  */
        String constructStopMessage(const String & stopMsg)
        {
            String message = stopMessageID + stopMsg ;
            return message;
        }
        /** This will construct back message for back button clicked in player
            @param[in]  backMsge         string
            @param[out] message             stop message string  */
        String constructBackMessage(const String & backMsg)
        {
            String message = backMessageID + backMsg ;
            return message;
        }
        /** This will construct back message for next button clicked in player
            @param[in]  nextMsg         string
            @param[out] message         next message string  */
        String constructNextMessage(const String & nextMsg)
        {
            String message = nextMessageID + nextMsg ;
            return message;
        }
        /** This will construct playafterpause message 
            @param[in]  playAfterPauseMsg           string
            @param[out] message                     playafterpause message string  */
        String constructPlayAfterPauseMessage(const String & playAfterPauseMsg)
        {
            String message = playAfterStopMessageID + playAfterPauseMsg ;
            return message;
        }
        /** This will construct playafterstop message 
            @param[in]  playAfterStopMsg            string
            @param[out] message                     playafterstop message string  */
        String constructPlayAfterStopMessage(const String & playAfterStopMsg)
        {
            String message = playAfterPauseMessageID + playAfterStopMsg ;
            return message;
        }
        // All validation and read and check methods
        /** this will validate First time client name 
            @param[in]  message     message string
            @param[in]  name        name string
            @param[out] bool        true if First time name is valid */
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
        bool isConnectTimeName(const String & message, String & name)
        {
            String tempMessage = message;
            if(tempMessage.contains(connectTimeNameID))
            {
                name = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }

        bool isNoAccessMessage(const String & message, String & errorMessage)
        {
            String tempMessage = message;
            if(tempMessage.contains(noAccessMessageID))
            {
                errorMessage = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }

    public:
        /** Constructor */
        Protocols() : messageSeparator("__"), firstTimeNameID("firstTimeName" + messageSeparator), connectTimeNameID("connectTimeName" + messageSeparator), 
            noAccessMessageID("noAccess" + messageSeparator), pauseMessageID("pause" + messageSeparator), stopMessageID("stop" + messageSeparator),
            nextMessageID("next" + messageSeparator), backMessageID("back" + messageSeparator), playAfterPauseMessageID("playAfterPause" + messageSeparator),
            playAfterStopMessageID("playAfterStop"+ messageSeparator)
        {
        }
    };
}

#endif // hpp_cpp_Protocols_cpp_hpp