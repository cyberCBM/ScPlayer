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


NetworkConnection::ServerConnection::ServerConnection(Component & ownerComponent) : 
serverWaiting(false), ownerComponent(ownerComponent), enableClients(enableClients)
{
	// Just fixing the port number as from Teams ....
    portNumber = 7227;
}

NetworkConnection::ServerConnection::~ServerConnection()
{
	// If Any thing has to distructed before server goes down ?
}

void NetworkConnection::ServerConnection::startServer()
{
    serverWaiting = beginWaitingForSocket(portNumber);
}

void NetworkConnection::ServerConnection::stopServer()
{
    GUI::ControlBarComponent * ownerControlBarComponent = dynamic_cast<GUI::ControlBarComponent*>(&ownerComponent);
    if(activeConnections.size())
    {
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(ownerControlBarComponent)
                ownerControlBarComponent->getClientListComponent()->disconnectClient(activeConnections.getUnchecked(i)->getClientInfo());
            activeConnections.getUnchecked(i)->disconnect();
        }
    }
    activeConnections.clear();
    stop();
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

void NetworkConnection::ServerConnection::sendOtherThatServerIslocked(const bool serverIsLocked, const String & clientIpAddress)
{
    if(activeConnections.size() > 1)
    {
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(activeConnections.getUnchecked(i)->getConnectedHostName() != clientIpAddress)
            {
                activeConnections.getUnchecked(i)->sendOtherThatServerIslocked(serverIsLocked);
            }
        }
    }
}

void NetworkConnection::ServerConnection::sendAddInPlayList(const String & playList)
{
	if(activeConnections.size())
    {
        for(int i = 0; i < activeConnections.size(); i++)
        {
			activeConnections.getUnchecked(i)->sendAddInPlayList(playList);
        }
    }
}

void NetworkConnection::ServerConnection::sendDeleteInPlayList(const Array<int> & indexList)
{
	if(activeConnections.size())
    {
        for(int i = 0; i < activeConnections.size(); i++)
        {
			activeConnections.getUnchecked(i)->sendDeleteInPlayList(indexList);
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
    {
        ownerServer.sendOtherThatServerIslocked(false, clientInfo.clientIpAddress);
        ownerControlBarComponent->getClientListComponent()->disconnectClient(clientInfo);
        ownerControlBarComponent->manageServerLock(false);
    }
    ownerServer.disconnectConnectedClient(clientInfo.clientIpAddress);
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
            ownerServer.sendOtherThatServerIslocked(true, clientInfo.clientIpAddress);
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
        ownerServer.sendOtherThatServerIslocked(false, clientInfo.clientIpAddress);
    }
    // Only check for these messages when client has lock
    if(clientInfo.hasLock)
    {
        if(messageProtocols.isPlayMessage(message.toString()))
        {
            ownerControlBarComponent->getPlayerComponent()->playPauseButtonClicked();
        }
        else if(messageProtocols.isPlayAfterStopMessage(message.toString(), dataToSend))
        {
            ownerControlBarComponent->getPlayListComponent()->songPlayedByClick(dataToSend.getIntValue());
        }
        else if(messageProtocols.isPauseMessage(message.toString()))
        {
            ownerControlBarComponent->getPlayerComponent()->playPauseButtonClicked();
        }
        else if(messageProtocols.isStopMessage(message.toString()))
        {
            ownerControlBarComponent->getPlayerComponent()->signalThreadShouldExit();
            ownerControlBarComponent->getPlayerComponent()->stopButtonClicked();
        }
        else if(messageProtocols.isBackMessage(message.toString()))
        {
            ownerControlBarComponent->getPlayerComponent()->backButtonClicked();
        }
        else if(messageProtocols.isNextMessage(message.toString()))
        {
            ownerControlBarComponent->getPlayerComponent()->nextButtonClicked();
        }
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
    // @ To Do : Don't forget to send back current status like : does any one have lock ? / What is current playing Song ?
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
                int index;
                if(ownerControlBarComponent->getPlayerComponent()->isCurrentlyPlaying(index))
                {
                    playList = messageProtocols.constructPlayingIndex(String(index));
                    MemoryBlock messageData(playList.toUTF8(), playList.getNumBytesAsUTF8());
                    sendMessage(messageData);
                }
                
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

void NetworkConnection::ClientConnection::sendOtherThatServerIslocked(const bool serverIsLocked)
{
    String dataToSend ;
    if(serverIsLocked)
        dataToSend= messageProtocols.constructServerIsLocked();
    else
        dataToSend= messageProtocols.constructServerIsUnLocked();
    
    MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::sendAddInPlayList(const String & playList)
{
	String dataToSend = messageProtocols.constructAddInPlayList(playList);
	MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::sendDeleteInPlayList(const Array<int> & indexList)
{
	String dataToSend = messageProtocols.constructDeleteInPlayList(indexList);
	MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}
