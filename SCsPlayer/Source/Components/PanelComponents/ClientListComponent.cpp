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
}

void GUI::ClientListComponent::readClientDetailsFromXML()
{
    XmlElement * clientsElement = mainElement->getFirstChildElement();
    XmlElement * clientElement = clientsElement->getFirstChildElement();
    while(clientElement)
    {
        Configurations::ClientInfo  tempClientInfo;
        tempClientInfo.clientIpAddress = clientElement->getStringAttribute("ip");
        tempClientInfo.controlAccess = clientElement->getBoolAttribute("access");
        tempClientInfo.clientName = clientElement->getStringAttribute("name");
        tempClientInfo.hasLock = false;
        tempClientInfo.isConnected = false;
        // Add clientInformation into Array
        clientInfoArray.add(tempClientInfo);
        clientElement = clientElement->getNextElement();
    }
    /*deleteAndZero(mainElement);
    deleteAndZero(clientsElement);
    deleteAndZero(clientElement);*/
    clientListBox->updateContent();
}

GUI::ClientListComponent::~ClientListComponent()
{
    removeChildComponent(clientListBox);
}

void GUI::ClientListComponent::resized()
{
    clientListBox->setSize(getWidth(), getHeight());
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
    
}

GUI::ListBoxItemComponent::~ListBoxItemComponent()
{
    
}

void GUI::ListBoxItemComponent::resized()
{
    
}

void GUI::ListBoxItemComponent::paint(Graphics & g)
{
    int stringWidth = g.getCurrentFont().getStringWidth(clientInfo.clientName);
    g.setColour(Colours::grey);
    g.drawText(clientInfo.clientName, 0, 0, stringWidth, getHeight(), Justification::centred, false);

    // backGround Filling
    /*if(isSelected)
        g.fillAll (Colours::grey);
    else
        g.fillAll (Colour (0xff292929));*/

    /*if(permissionTB->getToggleState())
    {
        if(clientInfo.isConnected)
            permissionTB->setColour(ToggleButton::textColourId, Colours::green);
        else
            permissionTB->setColour(ToggleButton::textColourId, Colours::white);
    }
    else
        permissionTB->setColour(ToggleButton::textColourId, Colours::grey);*/
}

void GUI::ListBoxItemComponent::setSelected(bool selected)
{
    isSelected = selected;
    repaint();
}