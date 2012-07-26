#include "ClientListComponent.hpp"

GUI::ClientListComponent::ClientListComponent() : clientListBox(nullptr), firstCall(true), mainElement(nullptr)
{
    //this function read the data from xml....
    XmlDocument xmlDoc(File(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "csPlayer.xml"));
    mainElement = xmlDoc.getDocumentElement();
    addAndMakeVisible(clientListBox = new ListBox("ClientList", this));   
    clientListBox->setMultipleSelectionEnabled(true);		
    clientListBox->setColour(ListBox::backgroundColourId, Colour (0xff292929));
    clientListBox->setRowHeight(25);
	clientImage=ImageCache::getFromMemory (BinaryData::clients_gif , BinaryData::clients_gifSize);
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

GUI::ClientListComponent::~ClientListComponent()
{
    removeChildComponent(clientListBox);
	writeClientDetailsToXML();
}

void GUI::ClientListComponent::resized()
{
    clientListBox->setBounds(4,37,getWidth()-10, getHeight()-45);
	clientListBox->setSize(getWidth()-10, getHeight()-45);
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
	/**Setting uper rectangle */
	g.setColour (Colours::black);
	g.drawRect(2,2,getWidth()-3,32,1);
	g.drawImage (clientImage,3, 3, 30, 30,0, 0,clientImage.getWidth(), clientImage.getHeight());
	g.setColour (Colours::white);
	g.drawFittedText("Client List",34,14,getWidth(),10,juce::Justification::bottom,1);
	/**Setting Lower rectangle */
	g.setColour (Colours::black);
	g.drawRect(2,35,getWidth()-3,getBottom()-37,1); 
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

//to add toggle button dynamically on list rows.
Component * GUI::ClientListComponent::refreshComponentForRow(int row, bool isSelected, Component * existingComponentToUpdate)
{
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
    clientInfoArray.add(clientInfo);
    clientListBox->updateContent();
    // Now update your listbox content
}

//////////////////////////////CLIENT CLASS/////////////////////////////////////////////////////////

GUI::ListBoxItemComponent::ListBoxItemComponent(Configurations::ClientInfo clientInfo, ListBox & ownerListBox, const int rowNum) : 
isSelected(false), rowNumber(rowNum), clientInfo(clientInfo), ownerListBox(ownerListBox)
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
    accessToggleButton->setBounds(getRight()-30,2,20,20); 
	repaint();
}
void GUI::ListBoxItemComponent ::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
	  if (buttonThatWasClicked == accessToggleButton)
		{
		  isSelected=buttonThatWasClicked->getToggleState();
		  	 
		  repaint();
		}
    //[/UserbuttonClicked_Pre]

  
}



void GUI::ListBoxItemComponent::paint(Graphics & g)
{
   int stringWidth = g.getCurrentFont().getStringWidth(clientInfo.clientName);
   g.setColour(Colours::grey);
   g.drawText(clientInfo.clientName, 0, 0, stringWidth, getHeight(), Justification::centred, false);

    /**Client List Text Colours changing according to client's stats...*/
   if(isSelected)
	{
		/**only clients which have access rights selected can connect to the server*/
		if(clientInfo.isConnected)  /**if client is connected*/
		{
			g.setColour(Colours::green);
			g.drawText(clientInfo.clientName, 0, 0, stringWidth, getHeight(), Justification::centred, false);
			accessToggleButton->setTooltip("Client is connected");

		}
		else
		{		
			g.setColour(Colours::white);
			g.drawText(clientInfo.clientName, 0, 0, stringWidth, getHeight(), Justification::centred, false);
			accessToggleButton->setTooltip("Client can connect to server");
			
		}
	}
   else
	{
		g.setColour(Colours::grey);
		g.drawText(clientInfo.clientName, 0, 0, stringWidth, getHeight(), Justification::centred, false);
		accessToggleButton->setTooltip("Client has no access to server");
	}
}

void GUI::ListBoxItemComponent::setSelected(bool selected)
{
    isSelected = selected;
    repaint();
}