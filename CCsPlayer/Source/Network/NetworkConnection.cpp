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
#include "../Common/Configurations.hpp"
// We need Configurations 
#include "../Common/Protocols.hpp"
//// Ww need ClientSettingComponent
#include "../Components/PanelComponent/ClientSettingComponent.hpp"
//// Ww need ClientSettingComponent
#include "../Components/PanelComponent/ClientControlComponent.hpp"

NetworkConnection::ClientConnection::ClientConnection() : ownerComponent(nullptr), isFirstCall(true)
{
}
NetworkConnection::ClientConnection::~ClientConnection()
{
}

void NetworkConnection::ClientConnection::setOwnerComponent(Component * ownerComp)
{
    ownerComponent = ownerComp;
}

void NetworkConnection::ClientConnection::connectionMade()
{
    // When successfully connected :)
    Configurations::Protocols messengerProtocol;
    String dataToSend;
    GUI::ClientSettingComponent * ownerClientSettingComp = dynamic_cast<GUI::ClientSettingComponent*> (ownerComponent);
    if(ownerClientSettingComp)
        dataToSend = messengerProtocol.constructFirstTimeName(ownerClientSettingComp->getClientName());
    else
    {
        GUI::ClientControlComponent * ownerClientControlComp = dynamic_cast<GUI::ClientControlComponent*> (ownerComponent);
        if(ownerClientControlComp)
            dataToSend = messengerProtocol.constructConnectTimeName(ownerClientControlComp->getClientName());
    }
    MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::connectionLost()
{
    // Stop the connected client
    //GUI::ClientSettingComponent * tempClientSettingComp = dynamic_cast<GUI::ClientSettingComponent*> (&ownerComponent);
    GUI::ClientSettingComponent * ownerClientSettingComp = dynamic_cast<GUI::ClientSettingComponent*> (ownerComponent);
    if(ownerClientSettingComp)
    {
        ownerClientSettingComp->setClientAdded(true);
        ownerClientSettingComp->writeToXML();
        ownerClientSettingComp->getParentComponent()->setVisible(false);
        ownerClientSettingComp->getParentComponent()->exitModalState(1);
    }
    disconnect();
}

void NetworkConnection::ClientConnection::messageReceived (const MemoryBlock & message)
{
    // When some data is received : Do something using Owner
    Configurations::ClientInfo tempClient;
    tempClient.clientIpAddress = getConnectedHostName();
    tempClient.clientName = message.toString();
}

bool NetworkConnection::ClientConnection::connectToServer(bool firstTime)
{
    if(firstTime)
    {
        GUI::ClientSettingComponent * ownerClientSettingComp = dynamic_cast<GUI::ClientSettingComponent*> (ownerComponent);
        if(ownerClientSettingComp)
        {
            bool serverResponse = connectToSocket(ownerClientSettingComp->getServerIPAddress(), ownerClientSettingComp->getPortNumber(), 1000);
            if(serverResponse)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
    {
        GUI::ClientControlComponent * ownerClientControlComp = dynamic_cast<GUI::ClientControlComponent*> (ownerComponent);
        if(ownerClientControlComp)
        {
            bool serverResponse = connectToSocket(ownerClientControlComp->getServerIPAddress(), ownerClientControlComp->getPortNumber(), 1000);
            if(serverResponse)
                return true;
            else
                return false;
        }
        else
            return false;

    }
}