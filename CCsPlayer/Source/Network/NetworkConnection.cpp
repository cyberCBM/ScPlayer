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

#include "../Components/PanelComponent/ClientSettingComponent.hpp"

NetworkConnection::ClientConnection::ClientConnection(Component & ownerComponent) : 
ownerComponent(ownerComponent), isFirstCall(true)
{

}

NetworkConnection::ClientConnection::~ClientConnection()
{

}

void NetworkConnection::ClientConnection::connectionMade()
{
    // When successfully connected :)
    Configurations::Protocols messengerProtocol;
    MemoryBlock messageData (messengerProtocol.constructFirstTimeName("Hitesh").toUTF8(), messengerProtocol.constructFirstTimeName("Hitesh").getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::connectionLost()
{
    disconnect();
    // Stop the connected client
    GUI::ClientSettingComponent * tempClientSettingComp = dynamic_cast<GUI::ClientSettingComponent*> (&ownerComponent);
    if(tempClientSettingComp)
    {
       tempClientSettingComp->setClientAdded(true);
       if(tempClientSettingComp->isClientConnected())
       {
           XmlElement saveConnection ("Configuration");
           XmlElement * serverIP = new XmlElement ("ServerIP");
           XmlElement * portNumber = new XmlElement("PortNumber");
           XmlElement * clientName = new XmlElement("ClientName");
           
           serverIP->addTextElement(tempClientSettingComp->getServerIPAddress());
           saveConnection.addChildElement(serverIP);
           portNumber->addTextElement(String(tempClientSettingComp->getPort()));
           saveConnection.addChildElement(portNumber);
           clientName->addTextElement(tempClientSettingComp->getClientName());
           saveConnection.addChildElement(clientName);

           saveConnection.writeToFile(File::getCurrentWorkingDirectory().getChildFile("csProp.xml"), String::empty);
           
           
           tempClientSettingComp->getParentComponent()->setVisible(false);
           tempClientSettingComp->getParentComponent()->exitModalState(1);
       }
    }
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

    /*String clientName = message.toString();
    Logger::outputDebugString(clientName + " is working here");
    const String name("Server says Hi.....");
    MemoryBlock messageData (name.toUTF8(), clientName.getNumBytesAsUTF8());
    sendMessage(messageData);*/
}

bool NetworkConnection::ClientConnection::connectToServer(bool firstTime)
{
    // Connect
   /* bool serverResponse = connectToSocket("127.0.0.1",7227,100000);
    return serverResponse;*/
    GUI::ClientSettingComponent * tempClientSettingComp = dynamic_cast<GUI::ClientSettingComponent*> (&ownerComponent);
    if(tempClientSettingComp)
    {
       /* String nm = tempClientSettingComp->getServerIPAddress();
        int pt = tempClientSettingComp->getPort();*/
        bool serverResponse = connectToSocket(tempClientSettingComp->getServerIPAddress(), tempClientSettingComp->getPort(), 100000);
        if(serverResponse)
            return true;
        else
            return false;
    }
    else
        return false;
}