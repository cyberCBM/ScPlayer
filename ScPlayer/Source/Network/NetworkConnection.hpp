/*                                                                                  
*=====================================================================================
*ScPlayer - Server Client Player                                                                   |
*Music file player that works in Network                                             |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com															 |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
*                                                                                    |
*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
* ScPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the ScPlayer distribution, or can be found     |
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
// ControlBarComponent is required as owner
#include "../Components/PanelComponents/ControlBarComponent.hpp"

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
        /** This method start the server */
        void startServer();
        /** This method stop the server and make all the client disconnect */
        void stopServer();
        /** When particular client is said to disconnect from server 
            @param[in]  clientIpAddress     based on this ipAddress this client is disconnectedd */
        void disconnectConnectedClient(const String & clientIpAddress);
        /** When server realse lock from client by force this is used*/
        void releaseClientLock();
        /** This message is sent to all other clients when some client lock or unlock server 
            @param[in]   serverIsLocked     Either server is locked or unlocked     
            @param[in]   clientName         Send clientName to other clients for information */
        void sendOtherThatServerIslocked(const bool serverIsLocked, const String & clientName = String::empty);
		/** To send add of song/songs in playList */
		void sendAddInPlayList(const String & playList);
        void sendAddInPlayList(const String & playList, const String & clientIpAddress);
		/** To send drop of song/songs in playList */
		void sendDropInPlayList(const String & playList, int insertionIndex);


		/** To send delete of song/songs in playList */
		void sendDeleteInPlayList(const Array<int> & indexList);
        void sendDeleteInPlayList(const Array<int> & indexList, const String & clientIpAddress);
		/** To send current playing index and status of play */
		void sendPlayingIndex(const int index);
		/** To send stop of the song */
		void sendStopSignal();
        /** To send stop of the song */
		void sendPauseSignal();
        /** To send play of the song */
        void sendPlaySignal();
		/** To send drag drop indices of the playlist */
		void sendDragDropIndex(const String & sourceIndexString, const String & insertionIndex);
		/** To send drag drop index of the song in playlist to other clients*/
		void sendDragDropIndex(const String & sourceIndexString, const String & insertionIndex, const String & clientIpAddress);
        /** Constructor and Destructor */
    public:
        /** Constructor 
            @param[in]  ownerComponent      This is the controlling component 
                                            which manage server's most things */
        ServerConnection (Component & ownerComponent);
        /** Destructor */
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
        /** Controller component that do things for networkConnection */
        GUI::ControlBarComponent   * ownerControlBarComponent;
    public:
        // InterprocessConnection interface
        /** When connection is made successfully */
        void connectionMade();
        /** When connection lost from either side (disconnected is called) */
        void connectionLost();
        /** When some message is received */
        void messageReceived (const MemoryBlock & message);

        // Class methods
        /** This method return client Information 
            @return clientInfo  current clientInfo that is for this connection */
        inline Configurations::ClientInfo getClientInfo(){  return clientInfo;  }

		/** When client connect for first time add it into clientList and disconnect it 
            Just simply it is added to clientList*/
        void firstTimeNameHandle();
        /** When client connect first time after it has been added to Server clientList 
            It's connected or Disconnected as per permission 
            If connected send the mediaList */
        void connectTimeNameHandle();
        /** Release lock for this client as server released all locks */
        void releaseClientLock();
        /** This message is sent to all other clients when some client lock or unlock server 
            @param[in]   serverIsLocked     Either server is locked or unlocked     
            @param[in]   clientName         Send Name of locking client to other */
        void sendServerIslocked(const bool serverIsLocked, const String & clientName = String::empty);
		/** To send add of song/songs in playList */
		void sendAddInPlayList(const String & playList);
		/** To send drop of song/songs in playList */
		void sendDropInPlayList(const String & playList, int insertionIndex);
		/** To send delete of song/songs in playList */
		void sendDeleteInPlayList(const Array<int> & indexList);
		/** To send current playing index and status of play */
		void sendPlayingIndex(const int index);
        /** To send stop of the song */
		void sendStopSignal();
        /** To send stop of the song */
		void sendPauseSignal();
        /** To send play of the song */
        void sendPlaySignal();
		/** To send drag drop index of the song in playlist*/
		void sendDragDropIndex(const String & sourceIndexString, const String & insertionIndex);
		
		/** When server is stopped each client will get disconnected */
		void setDisconnection();

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