#include "ClientListComponent.hpp"

GUI::ClientListComponent::ClientListComponent() : clientListBox(0)
    {
		clientListBox = new ListBox("ClientList", this);
		addAndMakeVisible(clientListBox);   
		clientListBox->setMultipleSelectionEnabled(true);
		clientListBox->updateContent();
        clientListBox->setColour(ListBox::backgroundColourId, Colour (0xff292929));
}

GUI::ClientListComponent::~ClientListComponent()
{
	deleteAndZero(clientListBox);
}

void GUI::ClientListComponent::resized()
{
	clientListBox->setBounds(0, 13, getWidth(), getHeight());
}

void GUI::ClientListComponent::paint(Graphics & g)
{
	// backGround Filling
    g.fillAll (Colour (0xff292929));
}

int GUI::ClientListComponent::getNumRows()
{
	return 5;
}

void GUI::ClientListComponent::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{

}


Component * GUI::ClientListComponent::refreshComponentForRow(int row, bool isSelected, Component * existingComponentToUpdate)
{
	if( /* clientArray.size()  &&*/ existingComponentToUpdate != 0 )
    {
        delete existingComponentToUpdate;    
        return 0;
    }
    else 
    {
        Client * comp = dynamic_cast<Client*>(existingComponentToUpdate);
        if (comp == 0)
        {
            delete existingComponentToUpdate;
            comp = new Client("name of Client");
            //comp = new Client(clientArray.getelementat(row), row, isSelected);
            comp->setSize(clientListBox->getWidth(), clientListBox->getRowHeight());
            comp->resized();
        }

        /*if(isSelected)
            comp->setSelected(true);*/

        return comp;
    }
    
    return 0;
}

////////////////////////////////////////////////////////////////////////

GUI::Client::Client(const String & name) : permissionTB(0), isConnected(false), isSelected(false)
{
	addAndMakeVisible (permissionTB = new ToggleButton(name));
    permissionTB->setColour(ToggleButton::textColourId, Colours::grey);
}

GUI::Client::~Client()
{
	deleteAndZero(permissionTB);
}

void GUI::Client::resized()
{
	permissionTB->setBounds(0,0,getWidth(),24);
}
void GUI::Client::paint(Graphics & g)
{
    // backGround Filling
    g.fillAll (Colour (0xff292929));
    
    // Selected BackGround
    if(isSelected)
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
	this->repaint();
}
