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

// We need our definitions here
#include "ClientListComponent.hpp"
// We need main component to get controlBar
#include "../MainComponent.hpp"

GUI::ClientListComponent::ClientListComponent() : clientListBox(nullptr), firstCall(true)
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
}

GUI::ClientListComponent::~ClientListComponent()
{
	removeChildComponent(clientListBox);
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
	clientListBox->setBounds(4,37,getWidth()-10, getHeight()-45);
	if(firstCall)
	{
		readClientDetailsFromXML();
		firstCall = false;
	}
}

void GUI::ClientListComponent::paint(Graphics & g)
{
	// backGround Filling
	g.fillAll (Colour (0xff292929));
	//Setting uper rectangle 
	g.setColour (Colours::black);
	g.drawRect(2, 2, getWidth()-3, 32, 1);
	//Setting Lower rectangle 
	g.drawRect(2, 35, getWidth()-3, getBottom()-37, 1);
    Image clientImg = ImageCache::getFromMemory (BinaryData::clients_gif , BinaryData::clients_gifSize);
	g.drawImage (clientImg,2, 2, 30, 30,0, 0,clientImg.getWidth(), clientImg.getHeight());
	g.setColour (Colours::white);
	g.drawFittedText("Client List", 34, 14, getWidth(), 10, juce::Justification::bottom, 1.0f);
}

int GUI::ClientListComponent::getNumRows()
{
	return clientInfoArray.size();
}

void GUI::ClientListComponent::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	// if we have to pint something in this row
	// But now not required because we do most work in refreshComponentForRow
}

void GUI::ClientListComponent::mouseDown(const MouseEvent & e)
{
	// you should check here that your current mouseEvent point are inside your image bound
    if(e.mods.isRightButtonDown())
    {
        Rectangle<int> imgRect(2, 2, 30, 30);
	    if(imgRect.contains(e.x, e.y))
	    {
		    if(e.mods.isLeftButtonDown())
		    {
			    PopupMenu clientMenu;
			    clientMenu.addItem(1,"Show Name");
			    clientMenu.addItem(2,"Show IpAddress");
			    int result = clientMenu.show();//show clientMenu and returns which item is selected
                ListBoxItemComponent * listComp ;
			    for(int i = 0; i < clientInfoArray.size(); i ++)
			    {
				    listComp = dynamic_cast<ListBoxItemComponent*>(clientListBox->getComponentForRowNumber(i));
				    if(listComp)
				    {
					    if(result == 1)
						    listComp->setShowDetail(true);
					    else if(result == 2)
						    listComp->setShowDetail(false);
				    }
			    }
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
			comp->resized();
		}
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

void GUI::ClientListComponent::addClient(Configurations::ClientInfo clientInfo)
{
	// Check things here weather this client is already exist or not ?
	bool match = false;
	for(int i = 0; i < clientInfoArray.size(); i++)
	{
		if(clientInfoArray.getReference(i).clientIpAddress == clientInfo.clientIpAddress)
			match = true;
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
            clientInfoArray.getReference(row).isConnected = false;
            findParentComponentOfClass<MainComponent>()->getTopPanel()->getControlBarComponent()->disconnectConnectedClient(clientInfoArray.getReference(row).clientIpAddress);
        }
    }
}

//////////////////////////////CLIENT CLASS/////////////////////////////////////////////////////////

GUI::ListBoxItemComponent::ListBoxItemComponent(Configurations::ClientInfo clientInfo, ListBox & ownerListBox, const int rowNum) : 
isSelected(false), rowNumber(rowNum), clientInfo(clientInfo), ownerListBox(ownerListBox), showDetail(true)
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
void GUI::ListBoxItemComponent ::buttonClicked (Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == accessToggleButton)
	{
		clientInfo.controlAccess = buttonThatWasClicked->getToggleState();
		if(!clientInfo.controlAccess)
        {
            if(clientInfo.isConnected)
                clientInfo.isConnected = false;
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
	if(showDetail)
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
	isDragging = false;
	selectRowOnMouseUp = false;
	if(&ownerListBox)
	{
		if(!isSelected)
		{    
			ownerListBox.selectRowsBasedOnModifierKeys (rowNumber, e.mods, false);
			if (ownerListBox.getModel() != 0)
				ownerListBox.getModel()->listBoxItemClicked (rowNumber, e);
		}
		else
			selectRowOnMouseUp = true;
		return;
	}
}

void GUI::ListBoxItemComponent::mouseUp(const GUI::ListBoxItemComponent::MouseEvent & e)
{
	if(&ownerListBox)
	{
		if (selectRowOnMouseUp && !isDragging)
		{
			ownerListBox.selectRowsBasedOnModifierKeys (rowNumber, e.mods, true);
			if (ownerListBox.getModel() != 0)
				ownerListBox.getModel()->listBoxItemClicked (rowNumber, e);
		}
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