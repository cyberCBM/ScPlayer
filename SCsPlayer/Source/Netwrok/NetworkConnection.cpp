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

NetworkConnection::ServerConnection::ServerConnection(GUI::ControlBarComponent & ownerControlBarComponent) : 
serverWaiting(false), ownerControlBarComponent(ownerControlBarComponent)
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
        ClientConnection * newConnection = new ClientConnection (ownerControlBarComponent, *this);
        activeConnections.add (newConnection);
        return newConnection;
    }
    else
        return 0;
}

//=====================================================================================//

NetworkConnection::ClientConnection::ClientConnection(GUI::ControlBarComponent & ownerControlBarComponent, ServerConnection & ownerServerConnection) : 
ownerControlBarComponent(ownerControlBarComponent), ownerServerConnection(ownerServerConnection), isFirstCall(true)
{

}

NetworkConnection::ClientConnection::~ClientConnection()
{

}

void NetworkConnection::ClientConnection::connectionMade()
{
    // When successfully connected :)
    int k = 0;
    String clientName = this->getConnectedHostName();
    Logger::outputDebugString(clientName + " is Connected");
}

void NetworkConnection::ClientConnection::connectionLost()
{
    // if connection is lost :(
    int k = 0;
    String clientName = this->getConnectedHostName();
    Logger::outputDebugString(clientName + " is disconnected");
    // Stop the connected client
    disconnect();
}

void NetworkConnection::ClientConnection::messageReceived (const MemoryBlock & message)
{
    // When some data is received : Do something using Owner
    if(isFirstCall)
    {
        clientInfo.clientIpAddress = getConnectedHostName();
        clientInfo.clientName = message.toString();
        clientInfo.controlAccess = true;
        clientInfo.isConnected = true;
        clientInfo.hasLock = false;
        ownerControlBarComponent.getClientListComponent()->addClientInfo(clientInfo);
        isFirstCall = false;
    }

    /*String clientName = message.toString();
    Logger::outputDebugString(clientName + " is working here");
    const String name("Server says Hi.....");
    MemoryBlock messageData (name.toUTF8(), clientName.getNumBytesAsUTF8());
    sendMessage(messageData);*/
}