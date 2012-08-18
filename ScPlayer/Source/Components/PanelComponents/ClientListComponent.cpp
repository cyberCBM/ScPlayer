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

// We need our definitions here
#include "ClientListComponent.hpp"
// We need main component to get controlBar
#include "../MainComponent.hpp"

GUI::ClientListComponent::ClientListComponent() : clientListBox(nullptr), rightsImageButton(nullptr), showImageButton(nullptr)
{
	csplayerxmlFilePath = File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "csPlayer.xml";
	addAndMakeVisible(clientListBox = new ListBox("ClientList", this)); 
    clientListBox->setLookAndFeel(&csLnF);
	clientListBox->setMultipleSelectionEnabled(true);
	clientListBox->setColour(ListBox::backgroundColourId, Colour (0xff292929));
	clientListBox->setRowHeight(20);
    LookAndFeel::getDefaultLookAndFeel().setColour(PopupMenu::backgroundColourId, Colour (0xff292929));
    LookAndFeel::getDefaultLookAndFeel().setColour(PopupMenu::textColourId, Colours::black);
    LookAndFeel::getDefaultLookAndFeel().setColour(PopupMenu::highlightedBackgroundColourId, Colours::grey);
    LookAndFeel::getDefaultLookAndFeel().setColour(PopupMenu::highlightedTextColourId, Colours::white);

    addAndMakeVisible (rightsImageButton	= new ImageButton());
    rightsImageButton->setImages (false, true, true, ImageCache::getFromMemory(BinaryData::unSelect_gif, BinaryData::unSelect_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::unSelect_gif, BinaryData::unSelect_gifSize),
                            0.7f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::select_gif, BinaryData::select_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	rightsImageButton->setTooltip ("No Rights");
	rightsImageButton->addButtonListener(this);

	addAndMakeVisible (showImageButton = new ImageButton());
    showImageButton->setImages (false, true, true, ImageCache::getFromMemory(BinaryData::abc_gif, BinaryData::abc_gifSize), 
        1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::abc_gif, BinaryData::abc_gifSize),
        0.7f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::ip_gif, BinaryData::ip_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	showImageButton->setTooltip ("Show By Name");
	showImageButton->addButtonListener(this);
    readClientDetailsFromXML();
}

GUI::ClientListComponent::~ClientListComponent()
{
	removeChildComponent(clientListBox);
    rightsImageButton->removeButtonListener(this);
    showImageButton->removeButtonListener(this);
	writeClientDetailsToXML();
}

void GUI::ClientListComponent::readClientDetailsFromXML()
{
	if(File(csplayerxmlFilePath).exists())//if File CsPlayer.xml is exist
	{
		File f=File(csplayerxmlFilePath);
		XmlDocument xmlDoc(f);
		// Csplayer to take document of XMLDocument
		ScopedPointer<XmlElement>  Csplayer;
		Csplayer = xmlDoc.getDocumentElement();
	    if(Csplayer) //if CsPlayer.xml file is not blank....
		{   
			XmlElement * clientElement = Csplayer->getChildByName("Clients")->getChildByName("Client");
			while(clientElement)
			{
				Configurations::ClientInfo  tempClientInfo;
				tempClientInfo.fromXML(clientElement);
				// Add clientInformation into Array
				clientInfoArray.add(tempClientInfo);
				clientElement = clientElement->getNextElement();
			}
			clientListBox->updateContent();
		}
	}
}

void GUI::ClientListComponent::writeClientDetailsToXML()
{
	File f=File(csplayerxmlFilePath);
	XmlDocument xmlDoc(f);
	//Csplayer to take document of XMLDocument
	ScopedPointer<XmlElement>  Csplayer;
	Csplayer=xmlDoc.getDocumentElement();
	
	if(File(csplayerxmlFilePath).exists())//if csPlayer.xml is exist.....
		 if(Csplayer)//if CsPlayer.xml is not blank....
			Csplayer->removeChildElement(Csplayer->getChildByName("Clients"), true);

	Csplayer=new XmlElement("CsPlayer");
	XmlElement  * clientElement =new XmlElement("Clients");
	Csplayer->addChildElement(clientElement);
	for(int row = 0; row < clientInfoArray.size(); row++)
	{
		Configurations::ClientInfo  tempClientInfo;
		tempClientInfo = clientInfoArray.getReference (row);
		XmlElement * clientNode = new XmlElement ("Client");
		tempClientInfo.toXML(clientNode);
		Csplayer->getChildByName("Clients")->addChildElement(clientNode);
	}
	Csplayer->writeToFile(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "csPlayer.xml", String::empty);	
}

void GUI::ClientListComponent::resized()
{
	clientListBox->setBounds(4, 37, getWidth() - 8, getHeight() - 40);
    rightsImageButton->setBounds(getWidth() - 30, 4, 28, 28);
    showImageButton->setBounds(getWidth() - 60, 4, 28, 28);
}

void GUI::ClientListComponent::paint(Graphics & g)
{
	// backGround Filling
	g.fillAll (Colour (0xff292929));
	g.setColour (Colours::aquamarine);
	g.drawFittedText("Client List", 6, 14, getWidth(), 10, juce::Justification::bottom, 1);
    //Setting uper rectangle 
	g.setColour (Colours::black);
	g.drawRect(2, 2, getWidth() - 4, 32, 1);
	//Setting Lower rectangle 
	g.drawRect(2, 35, getWidth() - 4, getHeight() - 37, 1);
}

int GUI::ClientListComponent::getNumRows()
{
	return clientInfoArray.size();
}

void GUI::ClientListComponent::paintListBoxItem (int /*rowNumber*/, Graphics & /*g*/, int /*width*/, int /*height*/, bool /*rowIsSelected*/)
{
	// if we have to pint something in this row
	// But now not required because we do most work in refreshComponentForRow
}

void GUI::ClientListComponent::buttonClicked (Button * buttonThatWasClicked)
{
    if (buttonThatWasClicked == rightsImageButton)
    {
        if(rightsImageButton->getToggleState())
        {
            rightsImageButton->setToggleState(false, false);
            rightsImageButton->setTooltip("No Rights");
        }
        else
        {
            rightsImageButton->setToggleState(true, false);
            rightsImageButton->setTooltip("Allow Rights");
        }
    }
    else if(buttonThatWasClicked == showImageButton)
    {
        if(showImageButton->getToggleState())
        {
            showImageButton->setToggleState(false, false);
            showImageButton->setTooltip("Show By Name");
        }
        else
        {
            showImageButton->setToggleState(true, false);
            showImageButton->setTooltip("Show By Ip");
        }

        ListBoxItemComponent * listComp ;
        for(int i = 0; i < getNumRows(); i ++)
		{
            listComp = dynamic_cast<ListBoxItemComponent*>(clientListBox->getComponentForRowNumber(i));
			if(listComp)
			{
                if(!showImageButton->getToggleState())
					listComp->setShowDetail(false);
                else
					listComp->setShowDetail(true);
			}
		}
    }
}

Component * GUI::ClientListComponent::refreshComponentForRow(int row, bool isSelected, Component * existingComponentToUpdate)
{
	//to add toggle button dynamically on list rows.
	if(row < clientInfoArray.size())
	{
		ListBoxItemComponent * comp = dynamic_cast<ListBoxItemComponent*>(existingComponentToUpdate);
		if (comp == 0)
		{
			delete existingComponentToUpdate;
			comp = new ListBoxItemComponent(clientInfoArray.getReference(row), *clientListBox, row);
			comp->setSize(clientListBox->getWidth(), clientListBox->getRowHeight());
            if(showImageButton->getToggleState())
                comp->setShowDetail(true);
			comp->resized();
		}
        // If we plan to delete and change the clientInfoArray we have to apply following things
        /*if(clientInfoArray.getReference(row).clientIpAddress != comp->getClientInfo().clientIpAddress)
            comp->setClientInfo(clientInfoArray.getReference(row));*/

        comp->setSelected(isSelected);
		comp->repaint();
		return comp;
	}// when component is not in use at all
	else if (existingComponentToUpdate != 0)
	{
		delete existingComponentToUpdate;
	}
	return 0;
}

void GUI::ClientListComponent::addClient(Configurations::ClientInfo & clientInfo)
{
	// Check things here weather this client is already exist or not ?
	bool match = false;
	for(int i = 0; i < clientInfoArray.size(); i++)
	{
		if(clientInfoArray.getReference(i).clientIpAddress == clientInfo.clientIpAddress)
        {
			match = true;
            clientInfo = clientInfoArray.getReference(i);
        }
	}       
	if(!match)
	{
		clientInfoArray.add(clientInfo);
		clientListBox->updateContent();
	}
}

bool GUI::ClientListComponent::connectClient(Configurations::ClientInfo clientInfo)
{
	// Check things here weather this client is already exist or not ?
	for(int i = 0; i < clientInfoArray.size(); i++)
	{
		if(clientInfoArray.getReference(i).clientIpAddress == clientInfo.clientIpAddress)
		{
			if(clientInfoArray.getReference(i).controlAccess)
			{
				clientInfoArray.getReference(i) = clientInfo;
				ListBoxItemComponent * itemComp = dynamic_cast<ListBoxItemComponent*>(clientListBox->getComponentForRowNumber(i));
				if(itemComp)
					itemComp->setClientInfo(clientInfo);
				return true;
			}
			else
				return false;
		}
	}
    return false;
}

bool GUI::ClientListComponent::disconnectClient(Configurations::ClientInfo clientInfo)
{
	// Check things here weather this client is already exist or not ?
	for(int i = 0; i < clientInfoArray.size(); i++)
	{
		if(clientInfoArray.getReference(i).clientIpAddress == clientInfo.clientIpAddress)
		{
			if(clientInfoArray.getReference(i).controlAccess)
			{
				clientInfoArray.getReference(i) = clientInfo;
				ListBoxItemComponent * itemComp = dynamic_cast<ListBoxItemComponent*>(clientListBox->getComponentForRowNumber(i));
				if(itemComp)
					itemComp->setClientInfo(clientInfo);
				return true;
			}
			else
				return false;
		}
	}
    return false;
}

void GUI::ClientListComponent::setClientHasLock(Configurations::ClientInfo clientInfo)
{
    // Check things here weather this client is already exist or not ?
    for(int i = 0; i < clientInfoArray.size(); i++)
    {
        if(clientInfoArray.getReference(i).clientIpAddress == clientInfo.clientIpAddress)
        {
            clientInfoArray.getReference(i) = clientInfo;
            ListBoxItemComponent * itemComp = dynamic_cast<ListBoxItemComponent*>(clientListBox->getComponentForRowNumber(i));
            if(itemComp)
                itemComp->setClientInfo(clientInfo);
            return;
        }
    }
}

void GUI::ClientListComponent::setAccess(bool access, int row)
{
    clientInfoArray.getReference(row).controlAccess = access;
    // If connection running close it down.
    if(!access)
    {
        if(clientInfoArray.getReference(row).isConnected)
        {
			bool hadLock = false;
            clientInfoArray.getReference(row).isConnected = false;
			if(clientInfoArray.getReference(row).hasLock)
			{
				hadLock = true;
				clientInfoArray.getReference(row).hasLock = false;
			}
            findParentComponentOfClass<MainComponent>()->getTopPanel()->getControlBarComponent()->disconnectConnectedClient(clientInfoArray.getReference(row).clientIpAddress, hadLock);
        }
    }
}

//////////////////////////////CLIENT CLASS/////////////////////////////////////////////////////////

GUI::ListBoxItemComponent::ListBoxItemComponent(Configurations::ClientInfo clientInfo, ListBox & ownerListBox, const int rowNum) : 
isSelected(false), rowNumber(rowNum), clientInfo(clientInfo), ownerListBox(ownerListBox), showDetail(false), selectRowOnMouseUp(false)
{
	addAndMakeVisible(accessToggleButton=new ToggleButton()); 
	accessToggleButton->addButtonListener(this);
	accessToggleButton->setColour(TextEditor::backgroundColourId, Colour (0xff292929));
	accessToggleButton->setColour(TextEditor::focusedOutlineColourId, Colour (0xff292929));
	accessToggleButton->setColour(TextButton::buttonColourId, Colours::grey);
	accessToggleButton->setToggleState(clientInfo.controlAccess,1);	 
}

GUI::ListBoxItemComponent::~ListBoxItemComponent()
{
    accessToggleButton->removeButtonListener(this);
    removeChildComponent(accessToggleButton);
}
void GUI::ListBoxItemComponent::resized()
{
	// int buttonSize = 20;
	accessToggleButton->setBounds(getWidth() - 20, 0, 20, 20); 
}
void GUI::ListBoxItemComponent ::buttonClicked (Button * buttonThatWasClicked)
{
	if (buttonThatWasClicked == accessToggleButton)
	{
		clientInfo.controlAccess = buttonThatWasClicked->getToggleState();
		if(!clientInfo.controlAccess)
        {
            if(clientInfo.isConnected)
                clientInfo.isConnected = false;
			if(clientInfo.hasLock)
				clientInfo.hasLock = false;
        }
        //To use setAccess() method of clientListComponent in ListBoxItemComponent
		ClientListComponent  * comp = dynamic_cast<ClientListComponent*>(ownerListBox.getParentComponent());
		if(comp)
			comp->setAccess(clientInfo.controlAccess, rowNumber);
		repaint();
	}
}

void GUI::ListBoxItemComponent::paint(Graphics & g)
{
	if(isSelected)
	{
		g.fillAll(Colours::lightgrey);
		if(!clientInfo.controlAccess)
			g.setColour(Colours::darkgrey);
		else
        {
			g.setColour(Colours::black);
            if(clientInfo.isConnected)
            {
                g.setColour(Colours::green);
                if(clientInfo.hasLock)
                    g.setColour(Colours::red);
            }
        }
	}
	else
	{
		if(!clientInfo.controlAccess)
			g.setColour(Colours::grey);
		else
        {
            g.setColour(Colours::white);
            if(clientInfo.isConnected)
            {
                g.setColour(Colours::green);
                if(clientInfo.hasLock)
                    g.setColour(Colours::red);
            }
        }
	}
	int stringWidth ;
	if(!showDetail)
	{
		stringWidth = g.getCurrentFont().getStringWidth(clientInfo.clientName);
		g.drawText(clientInfo.clientName, 0, 0, stringWidth, getHeight(), Justification::left, false);
	}
	else
	{
		stringWidth = g.getCurrentFont().getStringWidth(clientInfo.clientIpAddress);
		g.drawText(clientInfo.clientIpAddress, 0, 0, stringWidth, getHeight(), Justification::left, false);
	}
}

void GUI::ListBoxItemComponent::mouseDown(const GUI::ListBoxItemComponent::MouseEvent & e)
{
	// you should check here that your current mouseEvent point are inside your image bound
    if(e.mods.isLeftButtonDown())
    {
	    selectRowOnMouseUp = false;
		if(!isSelected)
			ownerListBox.selectRowsBasedOnModifierKeys (rowNumber, e.mods, false);
		else
			selectRowOnMouseUp = true;
    }
  //  else if(e.mods.isRightButtonDown())
  //  {
		//PopupMenu clientMenu;
		//clientMenu.addItem(1,"Show Name");
		//clientMenu.addItem(2,"Show IpAddress");
		//int result = clientMenu.show();//show clientMenu and returns which item is selected
  //      ListBoxItemComponent * listComp ;
  //      for(int i = 0; i < ownerListBox.getModel()->getNumRows(); i ++)
		//{
  //          listComp = dynamic_cast<ListBoxItemComponent*>(ownerListBox.getComponentForRowNumber(i));
		//	if(listComp)
		//	{
		//		if(result == 1)
		//			listComp->setShowDetail(true);
		//		else if(result == 2)
		//			listComp->setShowDetail(false);
		//	}
		//}
  //  }
}

void GUI::ListBoxItemComponent::mouseUp(const GUI::ListBoxItemComponent::MouseEvent & e)
{
	if (selectRowOnMouseUp)
	{
		ownerListBox.selectRowsBasedOnModifierKeys (rowNumber, e.mods, true);
	}
}

void GUI::ListBoxItemComponent::setClientInfo(Configurations::ClientInfo clInfo)
{
	clientInfo = clInfo;
	repaint();
}

void GUI::ListBoxItemComponent::setSelected(bool selected)
{
	isSelected = selected;
	repaint();
}