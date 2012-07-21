#include "ClientListComponent.hpp"

GUI::ClientListComponent::ClientListComponent() : clientListBox(0)
{
    setClientDetails();
    clientListBox = new ListBox("ClientList", this);
    addAndMakeVisible(clientListBox);   
    clientListBox->setMultipleSelectionEnabled(true);		
    clientListBox->updateContent();
    clientListBox->setColour(ListBox::backgroundColourId, Colour (0xff292929));
}

void GUI::ClientListComponent::setClientDetails()
{
    //this function read the data from xml....
    Configurations::ClientInfo          clientDetails;
    XmlDocument dataDoc(File(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "ClientDetails.xml"));
    demoData  = dataDoc.getDocumentElement();

    if (demoData == nullptr)
    {
        String error = dataDoc.getLastParseError();
    }

    dataList = demoData->getChildByName ("CLIENT");
    numRows = dataList->getNumChildElements();

    for(int i=0;i<numRows;i++)
    {
        clientDetails.clientName=dataList->getChildElement(i)->getAttributeValue(0);
        clientDetails.clientIpAddress=dataList->getChildElement(i)->getAttributeValue(1);


        if(dataList->getChildElement(i)->getAttributeValue(2)=="TRUE")
            clientDetails.controlAccess=true;
        else
            clientDetails.controlAccess=false;

        if(dataList->getChildElement(i)->getAttributeValue(3)=="TRUE")
            clientDetails.isConnected=true;
        else
            clientDetails.isConnected=false;

        clientInfoArray.add(clientDetails);
    }
}

GUI::ClientListComponent::~ClientListComponent()
{
    deleteAndZero(clientListBox);
}

void GUI::ClientListComponent::resized()
{
    clientListBox->setBounds(2, 2, getWidth(), getHeight());
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

}

//to add toggle button dynamically on list rows.
Component * GUI::ClientListComponent::refreshComponentForRow(int row, bool isSelected, Component * existingComponentToUpdate)
{
	if(  clientInfoArray.size()  && existingComponentToUpdate != 0 )
    {
        delete existingComponentToUpdate;    
        return 0;
    }
    else if(row < clientInfoArray.size())
    {
        Client * comp = dynamic_cast<Client*>(existingComponentToUpdate);
        if (comp == 0)
        {
            delete existingComponentToUpdate;
            comp = new Client(clientInfoArray.getReference(row));
            //comp = new Client(clientArray.getelementat(row), row, isSelected);
            comp->setSize(clientListBox->getWidth(), clientListBox->getRowHeight());
            comp->resized();
        }

        comp->setSelected(isSelected);
        comp->repaint();

        return comp;
    }
    
    return 0;
}

void GUI::ClientListComponent::addClientInfo(Configurations::ClientInfo clientInfo)
{
    clientInfoArray.add(clientInfo);
    // Now update your listbox content
}

//////////////////////////////CLIENT CLASS/////////////////////////////////////////////////////////

GUI::Client::Client(Configurations::ClientInfo clientInfoDetails) : permissionTB(0), isConnected(false), isSelected(false)
{
    addAndMakeVisible (permissionTB = new ToggleButton(clientInfoDetails.clientName));
    permissionTB->setColour(TextEditor::backgroundColourId, Colour (0xff292929));
    permissionTB->setColour(TextEditor::focusedOutlineColourId, Colour (0xff292929));
    permissionTB->setColour(ToggleButton::textColourId, Colours::grey);
    if(clientInfoDetails.controlAccess==true)
        permissionTB->setToggleState(true,false);
    isSelected=clientInfoDetails.controlAccess;
    isConnected=clientInfoDetails.isConnected;
    this->isSelected=isSelected;
}

GUI::Client::~Client()
{
    deleteAndZero(permissionTB);
}

void GUI::Client::resized()
{
    permissionTB->setBounds(0,0,getWidth()-4,22);
}


void GUI::Client::paint(Graphics & g)
{
    // Selected BackGround
    if(isSelected)
        g.fillAll (Colours::grey);
    else
        // backGround Filling
        g.fillAll (Colour (0xff292929));

    if(permissionTB->getToggleState())
    {
        if(isConnected)
            permissionTB->setColour(ToggleButton::textColourId, Colours::green);
        else
            permissionTB->setColour(ToggleButton::textColourId, Colours::white);
    }
    else
        permissionTB->setColour(ToggleButton::textColourId, Colours::grey);

}
void GUI::Client::buttonStateChanged(ToggleButton* buttonThatWasChanged)
{
    repaint();
}

void GUI::Client::setSelected(bool selected)
{
    isSelected = selected;
}