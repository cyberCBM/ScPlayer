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


NetworkConnection::ServerConnection::ServerConnection(Component & ownerComponent, bool enableClients) : 
serverWaiting(false), ownerComponent(ownerComponent), enableClients(enableClients)
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
        ClientConnection * newConnection = new ClientConnection (ownerComponent, *this);
        activeConnections.add (newConnection);
        return newConnection;
    }
    else
        return 0;
}

void NetworkConnection::ServerConnection::disconnectConnectedClient(const String & clientIpAddress)
{
    for(int i = 0; i < activeConnections.size(); i++)
    {
        if(activeConnections.getUnchecked(i)->getConnectedHostName() == clientIpAddress)
        {
            activeConnections.getUnchecked(i)->disconnect();
            activeConnections.remove(i);
            return;
        }
    }
}

//=====================================================================================//

NetworkConnection::ClientConnection::ClientConnection(Component & ownerComponent, ServerConnection & ownerServerConnection) : 
ownerComponent(ownerComponent), ownerServer(ownerServer), isFirstCall(true), ownerControlBarComponent(nullptr)
{
    ownerControlBarComponent = dynamic_cast<GUI::ControlBarComponent*>(&ownerComponent);
}

NetworkConnection::ClientConnection::~ClientConnection()
{

}

void NetworkConnection::ClientConnection::connectionMade()
{
    // When successfully connected :)
    clientInfo.clientIpAddress = getConnectedHostName();
    Logger::outputDebugString(clientInfo.clientIpAddress + " is Connected");
}

void NetworkConnection::ClientConnection::connectionLost()
{
    clientInfo.controlAccess = true;
    clientInfo.isConnected = false;
    clientInfo.hasLock = false;
    if(ownerControlBarComponent)
        ownerControlBarComponent->getClientListComponent()->disconnectClient(clientInfo);
    disconnect();
}

void NetworkConnection::ClientConnection::messageReceived (const MemoryBlock & message)
{
    // When some data is received : Do something using Owner
    if(isFirstCall)
    {
        if(messageProtocols.isFirstTimeName(message.toString(), clientInfo.clientName))
        {
            firstTimeNameHandle();
        }
        else if(messageProtocols.isConnectTimeName(message.toString(), clientInfo.clientName))
        {
            connectTimeNameHandle();
        }
        isFirstCall = false;
    }
}

void NetworkConnection::ClientConnection::firstTimeNameHandle()
{
    Logger::outputDebugString(clientInfo.clientName + "FirstTimeMessage is name");
    clientInfo.controlAccess = false;
    clientInfo.isConnected = false;
    clientInfo.hasLock = false;
    // Only add client here - now Disconnect the client
    if(ownerControlBarComponent)
        ownerControlBarComponent->getClientListComponent()->addClient(clientInfo);
    disconnect();
}

void NetworkConnection::ClientConnection::connectTimeNameHandle()
{
    Logger::outputDebugString(clientInfo.clientName + "ConnectTimeMessage is name");
    clientInfo.controlAccess = true;
    clientInfo.isConnected = true;
    clientInfo.hasLock = false;
    // Only add client here - now Disconnect the client
    if(ownerControlBarComponent)
    {
        if(!ownerControlBarComponent->getClientListComponent()->connectClient(clientInfo))
        {
            String dataToSend = messageProtocols.constructNoAccessMessage("No Access Rights granted");
            MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
            sendMessage(messageData);
            disconnect();
        }
    }
}
