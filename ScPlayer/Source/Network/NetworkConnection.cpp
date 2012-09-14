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
    if(activeConnections.size() && ownerControlBarComponent )
        for(int i = 0; i < activeConnections.size(); i++)
        {
			activeConnections.getUnchecked(i)->setDisconnection();
			ownerControlBarComponent->getClientListComponent()->disconnectClient(activeConnections.getUnchecked(i)->getClientInfo());
            activeConnections.getUnchecked(i)->disconnect();
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
        for(int i = 0; i < activeConnections.size(); i++)
		{
			if(activeConnections.getUnchecked(i)->getClientInfo().clientIpAddress == clientIpAddress)
            {
				if(activeConnections.getUnchecked(i)->getClientInfo().hasLock)
					sendOtherThatServerIslocked(false);
                activeConnections.getUnchecked(i)->disconnect();
                activeConnections.remove(i);
                return;
            }
		}
}

void NetworkConnection::ServerConnection::releaseClientLock()
{
    if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
            if(activeConnections.getUnchecked(i)->getClientInfo().hasLock)
                activeConnections.getUnchecked(i)->releaseClientLock();
			else
				activeConnections.getUnchecked(i)->sendServerIslocked(false);
}

void NetworkConnection::ServerConnection::sendOtherThatServerIslocked(const bool serverIsLocked, const String & clientName)
{
    if(activeConnections.size()>1)
        for(int i = 0; i < activeConnections.size(); i++)
            activeConnections.getUnchecked(i)->sendServerIslocked(serverIsLocked, clientName);
}

void NetworkConnection::ServerConnection::sendAddInPlayList(const String & playList)
{
	if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
			activeConnections.getUnchecked(i)->sendAddInPlayList(playList);
}

void NetworkConnection::ServerConnection::sendAddInPlayList(const String & playList, const String & clientIpAddress)
{
	if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(activeConnections.getUnchecked(i)->getClientInfo().clientIpAddress != clientIpAddress)
			    activeConnections.getUnchecked(i)->sendAddInPlayList(playList);
        }
}

void NetworkConnection::ServerConnection::sendDropInPlayList(const String & playList, int insertionIndex)
{
	if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
			activeConnections.getUnchecked(i)->sendDropInPlayList(playList, insertionIndex);
}

void NetworkConnection::ServerConnection::sendDropInPlayList(const String & playList, int insertionIndex, const String & clientIpAddress)
{
	if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(activeConnections.getUnchecked(i)->getClientInfo().clientIpAddress != clientIpAddress)
			    activeConnections.getUnchecked(i)->sendDropInPlayList(playList, insertionIndex);
        }
}

void NetworkConnection::ServerConnection::sendDeleteInPlayList(const Array<int> & indexList)
{
	if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
			activeConnections.getUnchecked(i)->sendDeleteInPlayList(indexList);
}

void NetworkConnection::ServerConnection::sendDeleteInPlayList(const Array<int> & indexList, const String & clientIpAddress)
{
	if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(activeConnections.getUnchecked(i)->getClientInfo().clientIpAddress != clientIpAddress)
			    activeConnections.getUnchecked(i)->sendDeleteInPlayList(indexList);
        }
}

void NetworkConnection::ServerConnection::sendPlayingIndex(const int index)
{
	if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
        {
            //if(activeConnections.getUnchecked(i)->getClientInfo().hasLock)
			activeConnections.getUnchecked(i)->sendPlayingIndex(index);
        }
}

void NetworkConnection::ServerConnection::sendStopSignal()
{
    if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(activeConnections.getUnchecked(i)->getClientInfo().hasLock)
                activeConnections.getUnchecked(i)->sendStopSignal();
        }
}

void NetworkConnection::ServerConnection::sendPauseSignal()
{
    if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(activeConnections.getUnchecked(i)->getClientInfo().hasLock)
			    activeConnections.getUnchecked(i)->sendPauseSignal();
        }
}

void NetworkConnection::ServerConnection::sendPlaySignal()
{
    if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(activeConnections.getUnchecked(i)->getClientInfo().hasLock)
			    activeConnections.getUnchecked(i)->sendPlaySignal();
        }
}

void NetworkConnection::ServerConnection::sendDragDropIndex(const String & sourceIndexString, const String & insertionIndex)
{
	if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
        {
            //if(activeConnections.getUnchecked(i)->getClientInfo().hasLock)
			activeConnections.getUnchecked(i)->sendDragDropIndex(sourceIndexString, insertionIndex);
        }
}

void NetworkConnection::ServerConnection::sendDragDropIndex(const String & sourceIndexString, const String & insertionIndex, const String & clientIpAddress)
{
	if(activeConnections.size())
        for(int i = 0; i < activeConnections.size(); i++)
        {
            if(activeConnections.getUnchecked(i)->getClientInfo().clientIpAddress != clientIpAddress)
				activeConnections.getUnchecked(i)->sendDragDropIndex(sourceIndexString, insertionIndex);
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
    if(ownerControlBarComponent)
    {
        if(clientInfo.hasLock)
        {
            ownerControlBarComponent->manageServerLock(false);
            ownerServer.sendOtherThatServerIslocked(false);
        }
        clientInfo.isConnected = false;
        clientInfo.hasLock = false;
        ownerControlBarComponent->getClientListComponent()->disconnectClient(clientInfo);
        
    }
    //disconnect();
	ownerServer.disconnectConnectedClient(clientInfo.clientIpAddress);
}

void NetworkConnection::ClientConnection::setDisconnection()
{
	clientInfo.isConnected = false;
	clientInfo.hasLock = false;
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
    String dataToSend, otherdataToSend;
    // Now it has to be normal connection and communicate after first connection time
    if(messageProtocols.isAcquireLockMessage(message.toString()))
    {
        if(ownerControlBarComponent->manageServerLock(true))
        {
            clientInfo.hasLock = true;
            dataToSend = messageProtocols.constructAllowLock();
            ownerControlBarComponent->getClientListComponent()->setClientHasLock(clientInfo);
            ownerServer.sendOtherThatServerIslocked(true, clientInfo.clientName);
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
        if(clientInfo.hasLock)
        {
            int index;
            if(ownerControlBarComponent->getPlayerComponent()->isCurrentlyPlaying(index))
            {
                dataToSend = messageProtocols.constructPlayingIndex(String(index));
                MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
                sendMessage(messageData);
            }
        }
    }
    else if(messageProtocols.isReleaseLockMessage(message.toString()))
    {
        ownerControlBarComponent->manageServerLock(false);
        clientInfo.hasLock = false;
        ownerControlBarComponent->getClientListComponent()->setClientHasLock(clientInfo);
        ownerServer.sendOtherThatServerIslocked(false);
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
        else if(messageProtocols.isAddInPlayList(message.toString(), dataToSend))
        {
            ownerControlBarComponent->getPlayListComponent()->addInPlayListFromClient(dataToSend);
            ownerServer.sendAddInPlayList(dataToSend, clientInfo.clientIpAddress);
        }
		else if(messageProtocols.isDropInPlayList(message.toString(), dataToSend, otherdataToSend))
        {
			ownerControlBarComponent->getPlayListComponent()->dropInPlayListFromClient(dataToSend, otherdataToSend.getIntValue());
            ownerServer.sendDropInPlayList(dataToSend, otherdataToSend.getIntValue(), clientInfo.clientIpAddress);
        }
		else if(messageProtocols.isdragDropPlayListMessage (message.toString(), dataToSend, otherdataToSend))
        {
            ownerControlBarComponent->getPlayListComponent()->itemDroppedFromClient(dataToSend, otherdataToSend);
			ownerServer.sendDragDropIndex (dataToSend, otherdataToSend, clientInfo.clientIpAddress);
        }
        else if(message.toString().contains(messageProtocols.getDeleteInPlayListID()))
        {
            Array<int> tempIndexList;
		    messageProtocols.isDeleteInPlayList(message.toString(), tempIndexList);
            ownerControlBarComponent->getPlayListComponent()->deleteInPlayListFromClient(tempIndexList);
            ownerServer.sendDeleteInPlayList(tempIndexList, clientInfo.clientIpAddress);
        }
    }
}

void NetworkConnection::ClientConnection::firstTimeNameHandle()
{
    Logger::outputDebugString(clientInfo.clientName + "FirstTimeMessage is name");
    if(ownerControlBarComponent)
    {
        if(ownerControlBarComponent->getClientListComponent()->getRightStatus())
            clientInfo.controlAccess = true;
        else
            clientInfo.controlAccess = false;
    }
    else
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
            if(ownerControlBarComponent->IsServerLocked())
                sendServerIslocked(true, clientInfo.clientName);
			else
				sendServerIslocked(false);
            
			String playList = messageProtocols.constructPlayListMessage(ownerControlBarComponent->getPlayListComponent()->getPlayListFromMediaArray());
            
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

void NetworkConnection::ClientConnection::releaseClientLock()
{
    clientInfo.hasLock = false;
    ownerControlBarComponent->getClientListComponent()->setClientHasLock(clientInfo);
    String dataToSend = messageProtocols.constructReleaseLock();
    MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::sendServerIslocked(const bool serverIsLocked, const String & clientName)
{
    String dataToSend ;
    if(serverIsLocked)
        dataToSend= messageProtocols.constructServerIsLocked(clientName);
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

void NetworkConnection::ClientConnection::sendDropInPlayList(const String & playList, int insertionIndex)
{
	String dataToSend = messageProtocols.constructDropInPlayList(playList, insertionIndex);
	MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::sendDeleteInPlayList(const Array<int> & indexList)
{
	String dataToSend = messageProtocols.constructDeleteInPlayList(indexList);
	MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::sendPlayingIndex(const int index)
{
    String dataToSend = messageProtocols.constructPlayingIndex(String(index));
	MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::sendStopSignal()
{
    String dataToSend = messageProtocols.constructStopMessage();
	MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::sendPauseSignal()
{
    String dataToSend = messageProtocols.constructPauseMessage();
	MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::sendPlaySignal()
{
    String dataToSend = messageProtocols.constructPlayMessage();
	MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::sendDragDropIndex(const String & sourceIndexString, const String & insertionIndex)
{
	String dataToSend = messageProtocols.constructDragDropPlayListMessage(sourceIndexString, insertionIndex);
	MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

