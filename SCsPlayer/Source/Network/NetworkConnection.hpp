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
// Configuration structures are read from here
#include "../Common/Configurations.hpp"
// Protocol are definied here
#include "../Common/Protocols.hpp"

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
        /** Boolean waiting for clients request */
        bool serverWaiting;
        /** Boolen for enbling clients to connect */
        bool enableClients;
        /** Port Number on which server listen for client */
        int portNumber;
        //This will hold connections 
        OwnedArray <ClientConnection, CriticalSection> activeConnections;
        /** Owner Component to communicate data inside application */
        Component & ownerComponent;
    public:
        /** InterprocessConnectionServer Mehtod */
        InterprocessConnection * createConnectionObject ();

        void start();

        inline void setEnableClients(bool enable){  enableClients = enable; }

        inline bool getEnableClients(){  return enableClients; }

        /** Constructor and Destructor */
    public:
        ServerConnection (Component & ownerComponent, bool enableClients);
        ~ServerConnection();
    // (prevent copy constructor and operator= being generated..)
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
        Component & ownerComponent;
        /** Owner Server to communicate data to other clients */
        ServerConnection & ownerServer;
        /** to create and read message protocols */
        Configurations::Protocols messageProtocols;
    public:
        // InterprocessConnection interface
        /** When connection is made successfully */
        void connectionMade();
        /** When connection lost from either side (disconnected is called) */
        void connectionLost();
        /** When some message is received */
        void messageReceived (const MemoryBlock& message);

        void firstTimeNameHandle();

        void connectTimeNameHandle();

        /** Constructor and Destructor */
    public:
        ClientConnection (Component & ownerComponent, ServerConnection & ownerServer);
        ~ClientConnection();
    // (prevent copy constructor and operator= being generated..)
    private:
        ClientConnection (const ClientConnection&);
        const ClientConnection& operator= (const ClientConnection&);
    };
}

#endif // hpp_NetworkConnection_hpp