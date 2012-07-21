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
#include "../JuceLibraryCode/JuceHeader.h"
// ControlBarComponent is required as owner
#include "../Components/PanelComponents/ControlBarComponent.hpp"

#include "../Common/Configurations.hpp"

namespace GUI
{
    class ControlBarComponent;
}
namespace NetworkConnection
{
    class ClientConnection;
    class ServerConnection : public InterprocessConnectionServer
    {
    private:
        // boolean for client request
        bool serverWaiting;
        /** Port Number on which server listen for client */
        int portNumber;
        //This will hold connections 
        OwnedArray <ClientConnection, CriticalSection> activeConnections;
        /** Owner Component to communicate data inside application */
        GUI::ControlBarComponent & ownerControlBarComponent;
    public:
        /** InterprocessConnectionServer Mehtod */
        InterprocessConnection * createConnectionObject ();

        void start();

        /** Constructor and Destructor */
    public:
        ServerConnection (GUI::ControlBarComponent & ownerControlBarComponent);
        ~ServerConnection();

    private:
        ServerConnection (const ServerConnection&);
        const ServerConnection& operator= (const ServerConnection&);
    };

    class ClientConnection : public InterprocessConnection
    {
    private:
        /** Client information sturcture */
        Configurations::ClientInfo clientInfo;
        /** To create client in clisntList when some data arrives */
        bool isFirstCall;
        /** Owner Component to communicate data inside application */
        GUI::ControlBarComponent & ownerControlBarComponent;
        /** Owner Server to communicate data to other clients */
        ServerConnection & ownerServerConnection;
    public:
        void connectionMade();
        void connectionLost();
        void messageReceived (const MemoryBlock& message);
        /** Constructor and Destructor */
    public:
        ClientConnection (GUI::ControlBarComponent & ownerControlBarComponent, ServerConnection & ownerServerConnection);
        ~ClientConnection();

    private:
        ClientConnection (const ClientConnection&);
        const ClientConnection& operator= (const ClientConnection&);
    };
}

#endif // hpp_NetworkConnection_hpp