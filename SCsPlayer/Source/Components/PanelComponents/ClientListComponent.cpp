#include "ClientListComponent.hpp"

GUI::ClientListComponent::ClientListComponent() : clientListBox(0)
    {
		clientListBox = new ListBox("ClientList", this);
		addAndMakeVisible(clientListBox);   
		clientListBox->setMultipleSelectionEnabled(true);
		clientListBox->updateContent();
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
	//g.setColour(Colours::grey);
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
	jassert (existingComponentToUpdate == nullptr || dynamic_cast <Client*> (existingComponentToUpdate) != nullptr);
	Client * comp = dynamic_cast<Client*>(existingComponentToUpdate);

	if (comp==NULL)	
		comp = new Client("valay");

   return comp;
}

////////////////////////////////////////////////////////////////////////

GUI::Client::Client(const String & name) : permissionTB(0)
{
	addAndMakeVisible (permissionTB = new ToggleButton(name));
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
	if(permissionTB->getToggleState()==false)
	{
		permissionTB->setColour(0x1006501,Colours::grey);
		g.fillAll(Colours::wheat);
	}
	else
	{
		permissionTB->setColour(0x1006501,Colours::blue);
		g.fillAll(Colours::wheat);
	}
}
void GUI::Client::buttonStateChanged(ToggleButton* buttonThatWasChanged)
{
	this->repaint();
}
