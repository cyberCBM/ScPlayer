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


#ifndef hpp_Client_hpp
#define hpp_Client_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"

class Client : public InterprocessConnection              
{

    private:
        /** boolean to know whether client request accepted or not */
        bool serverResponse;
    //Method 
    public:
        // Class Interface
        /** Method for connecting to server */
        void connectToServer();
        // InterprocessConnection Interface */
        /** Called when the connection is first connected. */
        void 	connectionMade ();
        /** Called when the connection is broken. */
        void 	connectionLost ();
        /** Called when a message arrives. */
        void 	messageReceived (const MemoryBlock &message);

    // Constructor & Destructor
    public:
        /** Constructor */
        Client ();
        /** Destructor */
        ~Client ();
};



#endif  // hpp_Client_hpp