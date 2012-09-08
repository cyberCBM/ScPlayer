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
// We need our definitions here 
#include "ClientSettingComponent.hpp"
// We need client control component to get connection details
#include "ClientControlComponent.hpp"

GUI::ClientSettingComponent::ClientSettingComponent(const bool connectClient) : serverIPLabel(nullptr), serverIPTextEditor(nullptr), 
    portNumberLabel(nullptr), portNumberTextEditor(nullptr), clientNameLabel(nullptr), clientNameTextEditor(nullptr), 
    clientIPLabel(nullptr), connectClient(connectClient), okTextButton(nullptr), clientAdded(false),  getConnected(false), 
    ownerComponent(nullptr)
{
    connector.setOwnerComponent(this);
    setGUIConfiguration();
    if(connectClient)
    {
        addAndMakeVisible(okTextButton = new TextButton("Connect"));
        okTextButton->setColour(TextButton::buttonColourId, Colours::black);
        okTextButton->setColour(TextButton::textColourOnId, Colours::lightgrey);
        okTextButton->setColour(TextButton::textColourOffId, Colours::white);
        okTextButton->setToggleState(false, false);
    }
    okTextButton->addListener(this);
    resized();
}

GUI::ClientSettingComponent::ClientSettingComponent(const bool connectClient, Component * component) : serverIPLabel(nullptr), serverIPTextEditor(nullptr), 
    portNumberLabel(nullptr), portNumberTextEditor(nullptr), clientNameLabel(nullptr), 
    clientNameTextEditor(nullptr), clientIPLabel(nullptr), connectClient(connectClient),
    okTextButton(nullptr), clientAdded(false),  getConnected(false), ownerComponent(component)
{
    setGUIConfiguration();
    if(!connectClient)
    {
        addAndMakeVisible(okTextButton = new TextButton("Save"));
        okTextButton->setColour(TextButton::buttonColourId, Colours::black);
        okTextButton->setColour(TextButton::textColourOnId, Colours::lightgrey);
        okTextButton->setColour(TextButton::textColourOffId, Colours::white);
        okTextButton->setToggleState(false, false);
        ClientControlComponent * ownerClientControlComp = dynamic_cast<GUI::ClientControlComponent*> (ownerComponent);
        serverIPTextEditor->setText(ownerClientControlComp->getServerIPAddress());
        portNumberTextEditor->setText(String(ownerClientControlComp->getPortNumber()));
        clientNameTextEditor->setText(ownerClientControlComp->getClientName());

    }
    okTextButton->addListener(this);
    resized();
}

GUI::ClientSettingComponent::~ClientSettingComponent()
{
    
}


void GUI::ClientSettingComponent::paint(Graphics & g)
{
    // Do your paint related things here
}

void GUI::ClientSettingComponent::resized()
{
    // All sizing goes here
    setSize(330,250);
    Font font = portNumberLabel->getFont();
    int width = font.getStringWidth(portNumberLabel->getText());
    int height = font.getHeight();
    serverIPLabel->setBounds(5, 15, width, height);
    serverIPTextEditor->setBounds(10 + width, 15 , 150 , height + 5);
    portNumberLabel->setBounds(5, 55 + height, width, height);
    portNumberTextEditor->setBounds(10 + width, 55 + height, 150, height + 5);
    clientNameLabel->setBounds(5, 95 +(2 * height), width, height);
    clientNameTextEditor->setBounds(10 + width, 95 + (2 * height), 150, height + 5);
    if(okTextButton)
        okTextButton->setBounds(getWidth()/2 - (80/2), 190, 80, 30);
}

void GUI::ClientSettingComponent::setGUIConfiguration()
{
    addAndMakeVisible(serverIPLabel = new Label("ServerIP","Server IP"));
    serverIPLabel->setFont (Font (20.0000f, Font::bold));
    serverIPLabel->setJustificationType (Justification::centredLeft);
    serverIPLabel->setEditable (false, false, false);
    serverIPLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (serverIPTextEditor = new TextEditor ("Client Detail"));
    serverIPTextEditor->setFont (Font (12.00f, Font::plain));
    serverIPTextEditor->setColour (TextEditor::outlineColourId, Colour (0x0));
    serverIPTextEditor->setColour (TextEditor::highlightColourId, Colours::grey);
    serverIPTextEditor->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
    serverIPTextEditor->setColour (TextEditor::shadowColourId, Colour (0x0));
    serverIPTextEditor->setColour (TextEditor::textColourId, Colours::black);
    serverIPTextEditor->setTextToShowWhenEmpty("ScPlayer Server IpAddress", Colours::grey);
    //serverIPTextEditor->setText("192.168.0.7"); // Temporary for work
    // serverIPTextEditor->setText("127.0.0.1"); // Temporary for work
    serverIPTextEditor->setExplicitFocusOrder(1);

    addAndMakeVisible(portNumberLabel = new Label("PortNum","PortNumber"));
    portNumberLabel->setFont (Font (20.0000f, Font::bold));
    portNumberLabel->setJustificationType (Justification::centredLeft);
    portNumberLabel->setEditable (false, false, false);
    portNumberLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (portNumberTextEditor = new TextEditor ("Client Detail"));
    portNumberTextEditor->setFont (Font (12.00f, Font::plain));
    portNumberTextEditor->setColour (TextEditor::outlineColourId, Colour (0x0));
    portNumberTextEditor->setColour (TextEditor::highlightColourId, Colours::grey);
    portNumberTextEditor->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
    portNumberTextEditor->setColour (TextEditor::shadowColourId, Colour (0x0));
    portNumberTextEditor->setColour (TextEditor::textColourId, Colours::black);
    portNumberTextEditor->setTextToShowWhenEmpty("Enter Portnumber ", Colours::grey);
    portNumberTextEditor->setText("7227"); // This is temporarary in work environment 
    portNumberTextEditor->setExplicitFocusOrder(2);

    addAndMakeVisible(clientNameLabel = new Label("Name","ClientName"));
    clientNameLabel->setFont (Font (20.0000f, Font::bold));
    clientNameLabel->setJustificationType (Justification::centredLeft);
    clientNameLabel->setEditable (false, false, false);
    clientNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (clientNameTextEditor = new TextEditor("Client Detail"));
    clientNameTextEditor->setFont (Font (12.00f, Font::plain));
    clientNameTextEditor->setColour (TextEditor::outlineColourId, Colour (0x0));
    clientNameTextEditor->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
    clientNameTextEditor->setColour (TextEditor::shadowColourId, Colour (0x0));
    clientNameTextEditor->setColour (TextEditor::highlightColourId, Colours::grey);
    clientNameTextEditor->setColour (TextEditor::textColourId, Colours::black);
    clientNameTextEditor->setTextToShowWhenEmpty("Enter name", Colours::grey);
    clientNameTextEditor->setText("YourName"); // Temporary work
    clientNameTextEditor->setExplicitFocusOrder(3);

}

void GUI::ClientSettingComponent::writeToXML()
{
    GUI::ClientControlComponent * comp = dynamic_cast<GUI::ClientControlComponent*> (ownerComponent);
    if(comp)
    {
        comp->setServerIpAddress(serverIPTextEditor->getText());
        comp->setPortNumber(portNumberTextEditor->getText().getIntValue());
        comp->setClientName(clientNameTextEditor->getText());
    }
    XmlElement saveConnection ("ScPlayer");
    XmlElement * connectionDetail = new XmlElement ("ServerIP");
    connectionDetail->addTextElement(getServerIPAddress());
    saveConnection.addChildElement(connectionDetail);
    connectionDetail = new XmlElement ("PortNumber");
    connectionDetail->addTextElement(String(getPortNumber()));
    saveConnection.addChildElement(connectionDetail);
    connectionDetail = new XmlElement ("ClientName");
    connectionDetail->addTextElement(getClientName());
    saveConnection.addChildElement(connectionDetail);
    saveConnection.writeToFile(File::getCurrentWorkingDirectory().getChildFile("csProp.scp"), String::empty);
}

void GUI::ClientSettingComponent::buttonClicked(Button * buttonThatWasClicked)
{
    if(buttonThatWasClicked == okTextButton)
    {
        // This is sure not appropriate place ..... We have to make it at right place - It's just temporary
        LookAndFeel::getDefaultLookAndFeel().setColour (AlertWindow::backgroundColourId, Colours::darkgrey);
        LookAndFeel::getDefaultLookAndFeel().setColour (AlertWindow::textColourId,  Colours::white);
        LookAndFeel::getDefaultLookAndFeel().setColour (AlertWindow::outlineColourId, Colours::black);
        LookAndFeel::getDefaultLookAndFeel().setColour (TextButton::buttonColourId, Colours::black);
        LookAndFeel::getDefaultLookAndFeel().setColour (TextButton::textColourOnId, Colours::lightgrey);
        LookAndFeel::getDefaultLookAndFeel().setColour (TextButton::textColourOffId, Colours::white);

        if(serverIPTextEditor->getText().isEmpty() | portNumberTextEditor->getText().isEmpty() | clientNameTextEditor->getText().isEmpty())
        {
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Error", "Please provide All details.");
            return;
        }
        if(connectClient)
        {
            if(connector.connectToServer(true))
                getConnected = true;
            else
            {
                AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Alert", "Server not running / Incorrect details");
                connector.disconnect();
            }
        }
        else
        {
            // save your settings in clientControlComponent so that we can retrive when we connect to server .....
            writeToXML();
            // Close your dialog window.
            getParentComponent()->setVisible(false);
            getParentComponent()->exitModalState(1);
        }
    }
}

