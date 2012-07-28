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
// ControlBarComponent is required as owner
#include "../Components/PanelComponents/ControlBarComponent.hpp"

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

//=====================================================================================//

NetworkConnection::ClientConnection::ClientConnection(Component & ownerComponent, ServerConnection & ownerServerConnection) : 
ownerComponent(ownerComponent), ownerServer(ownerServer), isFirstCall(true)
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
    clientInfo.clientIpAddress = getConnectedHostName();
    clientInfo.controlAccess = false;
    clientInfo.isConnected = false;
    clientInfo.hasLock = false;
    // Only add client here - now Disconnect the client
    GUI::ControlBarComponent * comp = dynamic_cast<GUI::ControlBarComponent*>(&ownerComponent);
    if(comp)
        comp->getClientListComponent()->addClient(clientInfo);
    disconnect();
}

void NetworkConnection::ClientConnection::connectTimeNameHandle()
{
    Logger::outputDebugString(clientInfo.clientName + "ConnectTimeMessage is name");
    clientInfo.clientIpAddress = getConnectedHostName();
    clientInfo.controlAccess = false;
    clientInfo.isConnected = true;
    clientInfo.hasLock = false;
    // Only add client here - now Disconnect the client
    GUI::ControlBarComponent * comp = dynamic_cast<GUI::ControlBarComponent*>(&ownerComponent);
    if(comp)
    {
        if(!comp->getClientListComponent()->connectClient(clientInfo))
        {
            String dataToSend = messageProtocols.constructNoAccessMessage("No Access Rights granted please try after some time");
            MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
            sendMessage(messageData);
            disconnect();
        }
    }
}
