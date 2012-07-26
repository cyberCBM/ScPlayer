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

// Juce related definitions go here
#include "NetworkConnection.hpp"
// We need Configurations 
#include "../Comman/Configurations.hpp"

NetworkConnection::ServerConnection::ServerConnection(GUI::ClientControlComponent & ownerClientControlComponent) : 
serverWaiting(false), ownerClientControlComponent(ownerClientControlComponent)
{
    portNumber = 7227;
}

NetworkConnection::ServerConnection::~ServerConnection()
{

}

void NetworkConnection::ServerConnection::start()
{
    serverWaiting = beginWaitingForSocket(portNumber);
    Logger::outputDebugString("Cs Server is started");
}

InterprocessConnection * NetworkConnection::ServerConnection::createConnectionObject ()
{
    if(serverWaiting)
    {
        ClientConnection * newConnection = new ClientConnection (ownerClientControlComponent);
        activeConnections.add (newConnection);
        return newConnection;
    }
    else
        return 0;
}

//=====================================================================================//

NetworkConnection::ClientConnection::ClientConnection(GUI::ClientControlComponent & ownerClientControlComponent) : 
ownerClientControlComponent(ownerClientControlComponent), isFirstCall(true)
{

}

NetworkConnection::ClientConnection::~ClientConnection()
{

}

void NetworkConnection::ClientConnection::connectionMade()
{
    // When successfully connected :)
    const String clientName("Hammer_Here");
    MemoryBlock messageData (clientName.toUTF8(), clientName.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::connectionLost()
{
    // Stop the connected client
    disconnect();
}

void NetworkConnection::ClientConnection::messageReceived (const MemoryBlock & message)
{
    // When some data is received : Do something using Owner
    if(isFirstCall)
    {
        Configurations::ClientInfo tempClient;
        tempClient.clientIpAddress = getConnectedHostName();
        tempClient.clientName = message.toString();

        isFirstCall = false;
    }
    // To send some data to client do following
    /*String clientName = message.toString();
    Logger::outputDebugString(clientName + " is working here");
    const String name("Server says Hi.....");
    MemoryBlock messageData (name.toUTF8(), clientName.getNumBytesAsUTF8());
    sendMessage(messageData);*/
}

void NetworkConnection::ClientConnection::connectToServer()
{
    // Connect
    bool serverResponse = connectToSocket("127.0.0.1",7227,100000);
    if(!serverResponse)
    {
        // Error in connection
        int error = 0;
    }
}