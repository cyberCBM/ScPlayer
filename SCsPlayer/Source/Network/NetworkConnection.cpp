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

#include "../Common/Protocols.hpp"

NetworkConnection::ServerConnection::ServerConnection(GUI::ControlBarComponent & ownerControlBarComponent, bool enableClients) : 
serverWaiting(false), ownerControlBarComponent(ownerControlBarComponent), enableClients(enableClients)
{
    portNumber = 7227;
}

NetworkConnection::ServerConnection::~ServerConnection()
{

}

void NetworkConnection::ServerConnection::start()
{
    serverWaiting = beginWaitingForSocket(portNumber);
}

InterprocessConnection * NetworkConnection::ServerConnection::createConnectionObject ()
{
    if(enableClients && serverWaiting)
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
    String clientName = this->getConnectedHostName();
    Logger::outputDebugString(clientName + " is Connected");
}

void NetworkConnection::ClientConnection::connectionLost()
{
    // if connection is lost :(
    Logger::outputDebugString("Client is disconnected");
    // Stop the connected client
    disconnect();
}

void NetworkConnection::ClientConnection::messageReceived (const MemoryBlock & message)
{
    Configurations::Protocols messageProtocols;
    // When some data is received : Do something using Owner
    if(isFirstCall)
    {
        if(messageProtocols.isFirstTimeName(message.toString(), clientInfo.clientName))
        {
            Logger::outputDebugString(clientInfo.clientName + "FirstTimeMessage is name");
            clientInfo.clientIpAddress = getConnectedHostName();
            clientInfo.controlAccess = false;
            clientInfo.isConnected = false;
            clientInfo.hasLock = false;
            // Only add client here - now Disconnect the client
            ownerControlBarComponent.getClientListComponent()->addClient(clientInfo);
            disconnect();
        }
        isFirstCall = false;
    }
}