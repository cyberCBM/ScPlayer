#include "ClientListComponent.hpp"

GUI::ClientListComponent::ClientListComponent() : clientListBox(nullptr), firstCall(true), mainElement(nullptr)
{
	XmlDocument xmlDoc(File(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "csPlayer.xml"));
	mainElement = xmlDoc.getDocumentElement();

	addAndMakeVisible(clientListBox = new ListBox("ClientList", this)); 
    clientListBox->setLookAndFeel(&csLnF);
	clientListBox->setMultipleSelectionEnabled(true);		
	clientListBox->setColour(ListBox::backgroundColourId, Colour (0xff292929));
	clientListBox->setRowHeight(20);
}

GUI::ClientListComponent::~ClientListComponent()
{
	removeChildComponent(clientListBox);
	writeClientDetailsToXML();
}

void GUI::ClientListComponent::readClientDetailsFromXML()
{
	if(File::getCurrentWorkingDirectory().getChildFile ("csPlayer.xml").exists())
	{
		XmlElement * clientsElement = mainElement->getFirstChildElement();
		XmlElement * clientElement = clientsElement->getFirstChildElement();
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

void GUI::ClientListComponent::writeClientDetailsToXML()
{
	XmlElement clientList ("CsPlayer");
	XmlElement  * clientElement =new XmlElement("Clients");
	clientList.addChildElement(clientElement);
	for(int row = 0; row < clientInfoArray.size(); row++)
	{
		Configurations::ClientInfo  tempClientInfo;
		tempClientInfo = clientInfoArray.getReference (row);
		XmlElement * clientNode = new XmlElement ("Client");
		tempClientInfo.toXML(clientNode);
		clientList.getChildByName("Clients")->addChildElement(clientNode);
	}

	clientList.writeToFile (File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "csPlayer.xml", String::empty);	
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
	g.drawImage (clientImg,0, 0, 30, 30,0, 0,clientImg.getWidth(), clientImg.getHeight());
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
	Rectangle<int> imgRect(3, 3, 30, 30);
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
		else
			return false;
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
	accessToggleButton->setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
	accessToggleButton->setToggleState(clientInfo.controlAccess,1);	 
}

GUI::ListBoxItemComponent::~ListBoxItemComponent()
{

}
void GUI::ListBoxItemComponent::resized()
{
	int buttonSize = 20;
	accessToggleButton->setBounds(getWidth() - buttonSize, 0, buttonSize, buttonSize); 
}
void GUI::ListBoxItemComponent ::buttonClicked (Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == accessToggleButton)
	{
		clientInfo.controlAccess = buttonThatWasClicked->getToggleState();
		//To use setAccess() method of clientListComponent in ListBoxItemComponent
		ClientListComponent  * comp = dynamic_cast<ClientListComponent*>(ownerListBox.getParentComponent());
		if(comp)
			comp->setAccess(clientInfo.controlAccess, rowNumber);
		repaint();
	}
}

void GUI::ListBoxItemComponent::setClientInfo(Configurations::ClientInfo clInfo)
{
	clientInfo = clInfo;
	repaint();
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

void GUI::ListBoxItemComponent::setSelected(bool selected)
{
	isSelected = selected;
	repaint();
}