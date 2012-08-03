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
        // Members 
    private:
        /** string for message separator */
        String messageSeparator;
    
    // Connection related
        /** Name of client when it connect to server first time */
        String firstTimeNameID;
        /**  Name of client when it try to connect to server */
        String connectTimeNameID;
        /** no access error message */
        String noAccessMessageID;
        
    // Getting and Giving lock related
        /** Get lock on server by this ID */
        String acquireLockID;
        /** Allow lock on server by this ID */
        String allowLockID;
        /** Release lock on server by this ID */
        String releaseLockID;
        /** Deny lock on server by this ID */
        String denyLockID;
        /** Server is locked by some client so inform other */
        String serverIsLockedID;
        /** Server is Unlocked by some client/Or Server so inform other */
        String serverIsUnLockedID;

    // Audio Player related messages
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

    // PlayList related data sending
        /** Send whole playList for first time */
        String playListMessageID;

    public:
        /** Constructor */
        Protocols() : messageSeparator("__"), firstTimeNameID("firstTimeName" + messageSeparator), connectTimeNameID("connectTimeName" + messageSeparator), 
            noAccessMessageID("noAccess" + messageSeparator), pauseMessageID("pause" + messageSeparator), stopMessageID("stop" + messageSeparator),
            nextMessageID("next" + messageSeparator), backMessageID("back" + messageSeparator), playAfterPauseMessageID("playAfterPause" + messageSeparator),
            playAfterStopMessageID("playAfterStop"+ messageSeparator), acquireLockID("acquireLock" + messageSeparator), allowLockID("allowLock" + messageSeparator),
            releaseLockID("releaseLock" + messageSeparator), denyLockID("denyLock" + messageSeparator), playListMessageID("playListString"+ messageSeparator),
            serverIsLockedID("serverisLocked" + messageSeparator), serverIsUnLockedID("serverisUnLocked"+ messageSeparator)
        {
        }

    public:
        // All String read methods
        /** This will return name of client when it connect to server first time
            @return firstTimeNameID     Name of client when it connect to server first time */
        inline String getFirstTimeNameID(){ return firstTimeNameID; }
        /** This will return name of client when it connect to server
            @return connectTimeNameID     Name of client when it try to connect to server */
        inline String getConnectTimeNameID(){ return connectTimeNameID; }
        /** This will return error message no access to client 
            @return noAccessMessageID     no access error message */
        inline String getMoAccessMessageID(){ return noAccessMessageID; }
        /** This will return pause message when pause button clicked on player
            @return pauseMessageID      pause message string  */
        inline String getpauseMessageID(){ return pauseMessageID; }
        /** This will return stop message when stop button clicked on player
            @return stopMessageID     stop message  string */
        inline String getstopMessageID(){ return stopMessageID; }
        /** This will return next message when next button clicked on player
            @return nextMessageID     next message string */
        inline String getnextMessageID(){ return nextMessageID; }
        /** This will return back message when back button clicked on player
            @return backMessageID     back message string */
        inline String getbackMessageID(){ return backMessageID; }
        /** This will return playafterpause message when play button clicked after paused button clicked
            @return playAfterPauseMessageID     playafter pause message string  */
        inline String getplayAfterPauseMessageID(){ return playAfterPauseMessageID; }
        /** This will return playafterstop message when play button clicked after stop button clicked
            @return playAfterStopMessageID     playafterstop message string  */
        inline String getplayAfterStopMessageID(){ return playAfterStopMessageID; }
        
        /** This will return deny lock message - Server denied client for lock
            @return denyLockID     denyLockID string  */
        inline String getPlayListMessageID(){  return playListMessageID;  }

        // All String Message Constructions 
        /** This will construct First time client name 
            @param[in]  name        string
            @return     message     First time client name  */
        String constructFirstTimeName(const String & name)
        {
            String message = firstTimeNameID + name ;
            return message;
        }
        /** This will construct connection time client name 
            @param[in]  name        string
            @return     message     connection time client name  */
        String constructConnectTimeName(const String & name)
        {
            String message = connectTimeNameID + name ;
            return message;
        }
        /** This will construct error message no access
            @param[in]  errorMessage        string
            @return     message             error message no access  */
        String constructNoAccessMessage(const String & errorMessage)
        {
            String message = noAccessMessageID + errorMessage ;
            return message;
        }
        /** This will construct pause message for pause button clicked in player
            @param[in]  pauseMsg        string
            @return     message         pause message string  */
        String constructPauseMessage(const String & pauseMsg)
        {
            String message = pauseMessageID + pauseMsg ;
            return message;
        }
        /** This will construct stop message for stop button clicked in player
            @param[in]  stopMsg         string
            @return     message         stop message string  */
        String constructStopMessage(const String & stopMsg)
        {
            String message = stopMessageID + stopMsg ;
            return message;
        }
        /** This will construct back message for back button clicked in player
            @param[in]  backMsge        string
            @return     message         stop message string  */
        String constructBackMessage(const String & backMsg)
        {
            String message = backMessageID + backMsg ;
            return message;
        }
        /** This will construct back message for next button clicked in player
            @param[in]  nextMsg         string
            @return     message         next message string  */
        String constructNextMessage(const String & nextMsg)
        {
            String message = nextMessageID + nextMsg ;
            return message;
        }
        /** This will construct playafterpause message 
            @param[in]  playAfterPauseMsg           string
            @return     message                     playafterpause message string  */
        String constructPlayAfterPauseMessage(const String & playAfterPauseMsg)
        {
            String message = playAfterStopMessageID + playAfterPauseMsg ;
            return message;
        }
        /** This will construct playAfterStop message 
            @param[in]  playAfterStopMsg            string
            @return     message                     playafterstop message string  */
        String constructPlayAfterStopMessage(const String & playAfterStopMsg)
        {
            String message = playAfterPauseMessageID + playAfterStopMsg ;
            return message;
        }
        /** This will construct lock acquring message for server
            @return     acquireLockID               acquireLockID message string  */
        String constructAcquireLock()
        {
            return acquireLockID  ;
        }
        /** This will construct allow lock acquring message for server
            @return     message                     allowLockID message string  */
        String constructAllowLock()
        {
            return allowLockID;
        }
        /** This will construct release lock message for server
            @return     releaseLockID               releaseLockID message string  */
        String constructReleaseLock()
        {
            return releaseLockID;
        }
        /** This will construct deny lock message for server
            @return     denyLockID                  denyLockID message string  */
        String constructDenyLock()
        {
            return denyLockID;
        }

        /** This will construct deny lock message for server
            @return     denyLockID                  denyLockID message string  */
        String constructServerIsLocked()
        {
            return serverIsLockedID;
        }
        /** This will construct deny lock message for server
            @return     denyLockID                  denyLockID message string  */
        String constructServerIsUnLocked()
        {
            return serverIsUnLockedID;
        }

        /** This will construct playlist message for client 
            @param[in]  playListInString            string
            @return     message                     playListIn message string */
        String constructPlayListMessage(const String & playListInString)
        {
            String message = playListMessageID + playListInString;
            return message;
        }

        // All validation and read and check methods
        /** this will validate First time client name 
            @param[in]  message     message string
            @param[in]  name        name string
            @return     bool        true if First time name is valid */
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
        /** this will validate connection time client name 
            @param[in]  message     message string
            @param[in]  name        name string
            @return     bool        true if connection time client name is valid */
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
        /** this will validate client's no access message  
            @param[in]  message         message string
            @param[in]  errorMessage    errorMessage string
            @return     bool            true if client has no access message*/
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
        /** this will validate pause message
            @param[in]  message         message string
            @param[in]  pauseMessage    pauseMessage string
            @return     bool            true if client is puase */
        bool isPauseMessage(const String & message, String & pauseMessage)
        {
            String tempMessage = message;
            if(tempMessage.contains(pauseMessageID))
            {
                pauseMessage = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }
        /** this will validate stop message
            @param[in]  message         message string
            @param[in]  stopMessage     stopMessage string
            @return     bool            true if client is stop */
        bool isStopMessage(const String & message, String & stopMessage)
        {
            String tempMessage = message;
            if(tempMessage.contains(stopMessageID))
            {
                stopMessage = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }
        /** this will validate back message
            @param[in]  message         message string
            @param[in]  backMessage     backMessage string
            @return     bool            true if back message */
        bool isBackMessage(const String & message, String & backMessage)
        {
            String tempMessage = message;
            if(tempMessage.contains(backMessageID))
            {
                backMessage = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }
        /** this will validate next message
            @param[in]  message         message string
            @param[in]  nextMessage     nextMessage string
            @return     bool            true if next message */
        bool isNextMessage(const String & message, String & nextMessage)
        {
            String tempMessage = message;
            if(tempMessage.contains(nextMessageID))
            {
                nextMessage = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }
        /** this will validate playAfterStop message
            @param[in]  message                 message string
            @param[in]  playAfterStopMessage    playAfterStopMessage string
            @return     bool                    true if playAfterStop message */
        bool isPlayAfterStopMessage(const String & message, String & playAfterStopMessage)
        {
            String tempMessage = message;
            if(tempMessage.contains(playAfterStopMessageID))
            {
                playAfterStopMessage = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }
        /** this will validate playAfterPause message
            @param[in]  message                 message string
            @param[in]  playAfterPauseMessage   playAfterPauseMessage string
            @return     bool                    true if playAfterPause message */
        bool isPlayAfterPauseMessage(const String & message, String & playAfterPauseMessage)
        {
            String tempMessage = message;
            if(tempMessage.contains(playAfterPauseMessageID))
            {
                playAfterPauseMessage = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }
        /** this will validate acquireLock message for server
            @param[in]  message                 message string
            @return     bool                    true if acquireLock message */
        bool isAcquireLockMessage(const String & message)
        {
            String tempMessage = message;
            if(tempMessage.contains(acquireLockID))
                return true;
            else
                return false;
        }
        /** this will validate acquireLock message for server
            @param[in]  message                 message string
            @return     bool                    true if allowLock message */
        bool isAllowLockMessage(const String & message)
        {
            String tempMessage = message;
            if(tempMessage.contains(allowLockID))
                return true;
            else
                return false;
        }
        /** this will validate releaseLock message for server
            @param[in]  message                 message string
            @return     bool                    true if releaseLock message */
        bool isReleaseLockMessage(const String & message)
        {
            String tempMessage = message;
            if(tempMessage.contains(releaseLockID))
                return true;
            else
                return false;
        }
        /** this will validate denyLock message for server
            @param[in]  message                 message string
            @return     bool                    true if denyLock message */
        bool isDenyLockMessage(const String & message)
        {
            String tempMessage = message;
            if(tempMessage.contains(denyLockID))
                return true;
            else
                return false;
        }
        /** this will validate denyLock message for server
            @param[in]  message                 message string
            @return     bool                    true if denyLock message */
        bool isServerIsLockedMessage(const String & message)
        {
            String tempMessage = message;
            if(tempMessage.contains(serverIsLockedID))
                return true;
            else
                return false;
        }
        /** this will validate denyLock message for server
            @param[in]  message                 message string
            @return     bool                    true if denyLock message */
        bool isServerIsUnLockedMessage(const String & message)
        {
            String tempMessage = message;
            if(tempMessage.contains(serverIsUnLockedID))
                return true;
            else
                return false;
        }

        /** this will validate playlist message for server
            @param[in]  message                 message string
            @param[in]  playListInString        playListInString string
            @return     bool                    true if playList message is valid */
        bool isPlayListMessage(const String & message, String & playListInString)
        {
            String tempMessage = message;
            if(tempMessage.contains(playListMessageID))
            {
                playListInString = tempMessage = tempMessage.fromFirstOccurrenceOf(messageSeparator, false, false);
                return true;
            }
            else
                return false;
        }
        
    };
}

#endif // hpp_cpp_Protocols_cpp_hpp