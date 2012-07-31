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

#ifndef hpp_NetworkConnection_hpp
#define hpp_NetworkConnection_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"
// We need protocol definitions 
#include "../Common/Protocols.hpp"

namespace GUI
{
    class ClientSettingComponent;
    class ClientControlComponent;
}
namespace NetworkConnection
{
    class ClientConnection : public InterprocessConnection
    {
    private:
        /** To create client in clisntList when some data arrives */
        bool                            isFirstCall;
        /** Owner Component to communicate data inside application */
        Component *                     ownerComponent;

        GUI::ClientSettingComponent *   settingComp;

        GUI::ClientControlComponent *   controlComp;

        ScopedPointer<AlertWindow>      alertWin;

    public:
        // InterprocessConnection Interface 
        /** Called when the connection is first connected. */
        void 	connectionMade ();
        /** Called when the connection is broken. */
        void 	connectionLost ();
        /** Called when a message arrives. */
        void 	messageReceived (const MemoryBlock &message);
        /** to create and read message protocols */
        Configurations::Protocols messageProtocols;

        // Class Interface
        /** Method for connecting to server */
        bool connectToServer(bool firstTime);

        void setOwnerComponent(Component * ownerComp);

        // Constructor and Destructor 
    public:
        /** Constructor */
        ClientConnection ();
        /** Destructor */
        ~ClientConnection();
    private:
        ClientConnection (const ClientConnection&);
        const ClientConnection& operator= (const ClientConnection&);
    };
}

#endif // hpp_NetworkConnection_hpp