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
    if(serverWaiting)
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
    if(activeConnections.size())
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
}

void NetworkConnection::ServerConnection::releaseClientLock()
{
    if(activeConnections.size())
    {
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(activeConnections.getUnchecked(i)->getClientInfo().hasLock)
            {
                activeConnections.getUnchecked(i)->releaseClientLock();
            }
        }
    }
}

//=====================================================================================//

NetworkConnection::ClientConnection::ClientConnection(Component & ownerComponent, ServerConnection & ownerServerConnection) : 
ownerComponent(ownerComponent), ownerServer(ownerServerConnection), isFirstCall(true), ownerControlBarComponent(nullptr)
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
    clientInfo.isConnected = false;
    clientInfo.hasLock = false;
    if(ownerControlBarComponent)
        ownerControlBarComponent->getClientListComponent()->disconnectClient(clientInfo);
    disconnect();
    ownerServer.disconnectConnectedClient(clientInfo.clientIpAddress);
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
        return;
    }
    String dataToSend;
    // Now it has to be normal connection and communicate after first connection time
    if(messageProtocols.isAcquireLockMessage(message.toString()))
    {
        if(ownerControlBarComponent->manageServerLock(true))
        {
            clientInfo.hasLock = true;
            dataToSend = messageProtocols.constructAllowLock();
            ownerControlBarComponent->getClientListComponent()->setClientHasLock(clientInfo);
            // Send info to clientListComponent also...
        }
        else
        {
            clientInfo.hasLock = false;
            dataToSend = messageProtocols.constructDenyLock();
            // No need to send data to clientListComp...
        }
        MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
        sendMessage(messageData);
    }
    else if(messageProtocols.isReleaseLockMessage(message.toString()))
    {
        ownerControlBarComponent->manageServerLock(false);
        clientInfo.hasLock = false;
        ownerControlBarComponent->getClientListComponent()->setClientHasLock(clientInfo);
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
        else
        {
            String playList = messageProtocols.constructPlayListMessage(ownerControlBarComponent->getPlayListComponent()->getPlayListFromMediaArray());
            if(playList.length())
            {
                MemoryBlock messageData(playList.toUTF8(), playList.getNumBytesAsUTF8());
                sendMessage(messageData);
            }
        }
    }
}

void NetworkConnection::ClientConnection::releaseClientLock()
{
    clientInfo.hasLock = false;
    ownerControlBarComponent->getClientListComponent()->setClientHasLock(clientInfo);
    String dataToSend = messageProtocols.constructReleaseLock();
    MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}
