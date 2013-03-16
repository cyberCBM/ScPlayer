/*                                                                                  
*=====================================================================================
*ScPlayer - Server-Client Player ()													 |
*Music file player that plays Network stored songs                                   |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com                                                          |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
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
// We need Configurations 
#include "../Common/Configurations.hpp"
// Ww need ClientSettingComponent
#include "../Components/PanelComponent/ClientSettingComponent.hpp"
// Ww need ClientSettingComponent
#include "../Components/PanelComponent/ClientControlComponent.hpp"

NetworkConnection::ClientConnection::ClientConnection() : 
ownerComponent(nullptr), settingComp(nullptr), controlComp(nullptr), alertWin(nullptr)
{
    LookAndFeel::getDefaultLookAndFeel().setColour (AlertWindow::backgroundColourId, Colours::darkgrey);
    LookAndFeel::getDefaultLookAndFeel().setColour (AlertWindow::textColourId,  Colours::white);
    LookAndFeel::getDefaultLookAndFeel().setColour (AlertWindow::outlineColourId, Colours::black);
    LookAndFeel::getDefaultLookAndFeel().setColour (TextButton::buttonColourId, Colours::black);
    LookAndFeel::getDefaultLookAndFeel().setColour (TextButton::textColourOnId, Colours::lightgrey);
    LookAndFeel::getDefaultLookAndFeel().setColour (TextButton::textColourOffId, Colours::white);
    alertWin = new AlertWindow("alert", "", AlertWindow::WarningIcon);
}

NetworkConnection::ClientConnection::~ClientConnection()
{
}

void NetworkConnection::ClientConnection::setOwnerComponent(Component * ownerComp)
{
    ownerComponent = ownerComp;
    settingComp = dynamic_cast<GUI::ClientSettingComponent*> (ownerComponent);
    if(!settingComp)
    {
        controlComp = dynamic_cast<GUI::ClientControlComponent*> (ownerComponent);
        if(!controlComp)
            return;
    }
}

void NetworkConnection::ClientConnection::connectionMade()
{
    // When successfully connected :)
    String dataToSend;
    if(settingComp)
        dataToSend = messengerProtocol.constructFirstTimeName(settingComp->getClientName());
    else
    {
        if(controlComp)
            dataToSend = messengerProtocol.constructConnectTimeName(controlComp->getClientName());
    }
    MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::connectionLost()
{
    // Stop the connected client
    if(settingComp)
    {
        settingComp->setClientAdded(true);
        settingComp->writeToXML();
        settingComp->getParentComponent()->setVisible(false);
        settingComp->getParentComponent()->exitModalState(1);
    }
    if(controlComp)
    {
        controlComp->setClientDisconnected();
    }
    disconnect();
}

bool NetworkConnection::ClientConnection::connectToServer(bool firstTime)
{
    if(firstTime)
    {
        if(settingComp)
        {
            bool serverResponse = connectToSocket(settingComp->getServerIPAddress(), settingComp->getPortNumber(), 1000);
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
        if(controlComp)
        {
            bool serverResponse = connectToSocket(controlComp->getServerIPAddress(), controlComp->getPortNumber(), 1000);
            if(serverResponse)
                return true;
            else
            {
                alertWin->showMessageBox(AlertWindow::WarningIcon, "Error", "Server not running / Incorrect details", "Ok", controlComp);
                return false;
            }
        }
        else
            return false;
    }
}

void NetworkConnection::ClientConnection::messageReceived (const MemoryBlock & message)
{
    String dataString, otherdataString;
    if(messageProtocols.isNoAccessMessage(message.toString(), dataString))
    {
        alertWin->showMessageBox(AlertWindow::WarningIcon, "Error", dataString, "Ok", controlComp);
    }
    else if(messageProtocols.isPlayListMessage(message.toString(), dataString))
    {
        controlComp->getPlayListComponent()->updatePlayListFromServer(dataString);
    }
    else if(messageProtocols.isPlayingIndex(message.toString(), dataString))
    {
        controlComp->getPlayListComponent()->setPlayingSongIndex(dataString.getIntValue());
        controlComp->serverSentPlay();
    }
    else if(messageProtocols.isAllowLockMessage(message.toString()))
    {
        controlComp->manageLock(true);
    }
    else if(messageProtocols.isDenyLockMessage(message.toString()) || messageProtocols.isReleaseLockMessage(message.toString()))
    {
        controlComp->manageLock(false);
    }
    else if(messageProtocols.isServerIsLockedMessage(message.toString(), dataString))
    {
        controlComp->serverIsLocked(true, dataString);
    }
    else if(messageProtocols.isServerIsUnLockedMessage(message.toString()))
    {
        controlComp->serverIsLocked(false, "");
    }
	else if(messageProtocols.isAddInPlayList(message.toString(), dataString))
    {
        // add these songs in playList
        controlComp->getPlayListComponent()->addInPlayListFromServer(dataString);
    }
	else if(messageProtocols.isDropInPlayList(message.toString(), dataString, otherdataString))
    {
        // drop these songs in playList
		controlComp->getPlayListComponent()->dropInPlayListFromServer(dataString, otherdataString.getIntValue());
    }
	else if(message.toString().contains(messageProtocols.getDeleteInPlayListID()))
    {
        Array<int> tempIndexList;
		messageProtocols.isDeleteInPlayList(message.toString(), tempIndexList);
		// delete these songs from playList
        controlComp->getPlayListComponent()->deleteInPlayListFromServer(tempIndexList);
    }
    else if(messageProtocols.isPlayMessage(message.toString()))
    {
        controlComp->serverSentPlay();
    }
    else if(messageProtocols.isStopMessage(message.toString()))
    {
        controlComp->serverSentStop();
    }
    else if(messageProtocols.isPauseMessage(message.toString()))
    {
        controlComp->serverSentPause();
    }
	else if(messageProtocols.isdragDropPlayListMessage (message.toString(), dataString, otherdataString))
    {
		controlComp->getPlayListComponent()->itemDroppedFromServer(dataString, otherdataString);
    }
	else if(message.toString().contains("FileExist")) //if client's local drive file Exist at server side which is dropped in playlist 
	{
		String filePath=message.toString().upToFirstOccurrenceOf(",",false,false);
		String fileName=filePath.fromLastOccurrenceOf(File::separatorString,false,false);
		String fileNameMessageForNonExistAtServer="localFileNonExistAtServer,"  + fileName;
		MemoryBlock messageFileName(fileNameMessageForNonExistAtServer.toUTF8(),fileNameMessageForNonExistAtServer.getNumBytesAsUTF8());
		String exist=message.toString().fromLastOccurrenceOf(",",false,false);
		if(exist=="false") //if doesnt exist need to send it to server
		{
			sendMessage(messageFileName);	  //sendig file name to save as.
			sendLocalFileToServer(filePath);  //sending file  data to server
		}
		else //if exist then just add to the playlist
		{
			String localFileExistAtServer="localFileExistAtServer," + fileName;
			MemoryBlock message(localFileExistAtServer.toUTF8(),localFileExistAtServer.getNumBytesAsUTF8());
			sendMessage(message);   // sending message to server about existance of client's file at server so no need to re transfer it just add it into playlist.
		}
	}
}

void NetworkConnection::ClientConnection::acquireLockOnServer()
{
    String dataToSend = messengerProtocol.constructAcquireLock();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::releaseLockOnServer()
{
    String dataToSend = messengerProtocol.constructReleaseLock();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendPlayAfterPauseToServer()
{
    /*Configurations::Protocols messengerProtocol;
    String dataToSend = messengerProtocol.constructReleaseLock();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);*/
}

void NetworkConnection::ClientConnection::sendPlayToServer()
{
    String dataToSend = messengerProtocol.constructPlayMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendPauseToServer()
{
    String dataToSend = messengerProtocol.constructPauseMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendStopToServer()
{
    String dataToSend = messengerProtocol.constructStopMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendBackToServer()
{
    String dataToSend = messengerProtocol.constructBackMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendNextToServer()
{
    String dataToSend = messengerProtocol.constructNextMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::songDoubleClickedPlay(const int index)
{
    String dataToSend = messengerProtocol.constructPlayAfterStopMessage(String(index));
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendDragDropIndex(const String & sourceIndexString, const String & insertionIndex)
{
    String dataToSend = messengerProtocol.constructDragDropPlayListMessage(sourceIndexString, insertionIndex);
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}


void NetworkConnection::ClientConnection::sendFileName(const String & fileName)
{
	String fileNameMessage=fileName;
	MemoryBlock message(fileNameMessage.toUTF8(),fileName.getNumBytesAsUTF8());
	sendMessage(message);
	
}

void NetworkConnection::ClientConnection::sendLocalFileToServer(const String & filePath)
{
  File fileToSend(filePath);
 // MemoryBlock message(fileToSend., fileToSend.getSize());
  MemoryBlock message;

  if(fileToSend.loadFileAsData(message))
  {
	 
 // File tempSong(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "tempsong.mp3");
 // message.copyTo(&tempSong,0,message.getSize());
  //tempSong.appendData(message.getData(),message.getSize());
	sendMessage(message);  
  }

}

void NetworkConnection::ClientConnection::sendAddInPlayList(const String & playList)
{
    String dataToSend = messengerProtocol.constructAddInPlayList(playList);
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendDropInPlayList(const String & playList, int insertionIndex)
{
    String dataToSend = messengerProtocol.constructDropInPlayList(playList, insertionIndex);
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendDeleteInPlayList(const Array<int> & indexList)
{
    String dataToSend = messengerProtocol.constructDeleteInPlayList(indexList);
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}
