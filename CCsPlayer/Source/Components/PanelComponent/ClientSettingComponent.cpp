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

#include "ClientSettingComponent.hpp"

#include "ClientControlComponent.hpp"

GUI::ClientSettingComponent::ClientSettingComponent(const bool connectClient) : serverIPLabel(nullptr), serverIPTextEditor(nullptr), 
    portNumberLabel(nullptr), portNumberTextEditor(nullptr), clientNameLabel(nullptr), 
    clientNameTextEditor(nullptr), clientIPLabel(nullptr), connectClient(connectClient),
    okImageButton(nullptr), clientAdded(false),  getConnected(false), connector(nullptr),
    serverIPError(nullptr), portNumberError(nullptr), clientNameError(nullptr), ownerComponent(nullptr)
{
    setGUIConfiguration();
    if(connectClient)
    {
        addAndMakeVisible(okImageButton = new ImageButton("Connect"));
        okImageButton->setToggleState(false, false);
        okImageButton->setImages (true, false, true, 
            ImageCache::getFromMemory(BinaryData::connectB_gif, BinaryData::connectB_gifSize), 1.0f, Colours::transparentBlack,
            ImageCache::getFromMemory(BinaryData::connectB_gif, BinaryData::connectB_gifSize), 0.7f, Colours::transparentBlack,
            ImageCache::getFromMemory(BinaryData::connectB_gif, BinaryData::connectB_gifSize), 1.0f, Colours::transparentBlack);
    }
    okImageButton->addButtonListener(this);
    resized();
}

GUI::ClientSettingComponent::ClientSettingComponent(const bool connectClient, Component * component) : serverIPLabel(nullptr), serverIPTextEditor(nullptr), 
    portNumberLabel(nullptr), portNumberTextEditor(nullptr), clientNameLabel(nullptr), 
    clientNameTextEditor(nullptr), clientIPLabel(nullptr), connectClient(connectClient),
    okImageButton(nullptr), clientAdded(false),  getConnected(false), 
    serverIPError(nullptr), portNumberError(nullptr), clientNameError(nullptr),
    ownerComponent(component), connector(nullptr)
{
    setGUIConfiguration();
    if(!connectClient)
    {
        addAndMakeVisible(okImageButton = new ImageButton("Save"));
        okImageButton->setToggleState(false, false);
        okImageButton->setImages (true, false, true, 
            ImageCache::getFromMemory(BinaryData::saveB_gif, BinaryData::saveB_gifSize), 1.0f, Colours::transparentBlack,
            ImageCache::getFromMemory(BinaryData::saveB_gif, BinaryData::saveB_gifSize), 0.7f, Colours::transparentBlack,
            ImageCache::getFromMemory(BinaryData::saveB_gif, BinaryData::saveB_gifSize), 1.0f, Colours::transparentBlack);

        ClientControlComponent * ownerClientControlComp = dynamic_cast<GUI::ClientControlComponent*> (ownerComponent);
        serverIPTextEditor->setText(ownerClientControlComp->getServerIPAddress());
        portNumberTextEditor->setText(String(ownerClientControlComp->getPortNumber()));
        clientNameTextEditor->setText(ownerClientControlComp->getClientName());

    }
    okImageButton->addButtonListener(this);
    resized();
}

GUI::ClientSettingComponent::~ClientSettingComponent()
{
    okImageButton->removeButtonListener(this);
    if(connector)
    {
        connector->disconnect();
        connector = 0;
        delete connector;
    }
}


void GUI::ClientSettingComponent::paint(Graphics & g)
{

}

void GUI::ClientSettingComponent::resized()
{
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
    serverIPError->setBounds(10 + width, height + 20 , 150 , height + 5);
    portNumberError->setBounds(10 + width, 65 + (2 * height), 150, height + 5);
    clientNameError->setBounds(10 + width, 105 + (3 * height), 150, height + 5);
    if(okImageButton)
        okImageButton->setBounds(getWidth()/2 - (130/2), 190, 130, 50);
}

void GUI::ClientSettingComponent::setGUIConfiguration()
{
    addAndMakeVisible(serverIPLabel = new Label("ServerIP","Server IP"));
    serverIPLabel->setFont (Font (20.0000f, Font::bold));
    serverIPLabel->setJustificationType (Justification::centredLeft);
    serverIPLabel->setEditable (false, false, false);
    serverIPLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (serverIPTextEditor = new TextEditor ("Client Detail"));
    serverIPTextEditor->addListener(this);
    serverIPTextEditor->setFont (Font (12.00f, Font::plain));
    serverIPTextEditor->setColour (TextEditor::outlineColourId, Colour (0x0));
    serverIPTextEditor->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
    serverIPTextEditor->setColour (TextEditor::shadowColourId, Colour (0x0));
    serverIPTextEditor->setColour (TextEditor::textColourId, Colours::black);
    serverIPTextEditor->setTextToShowWhenEmpty("Enter server CsPlyer Ipaddress", Colours::grey);

    addAndMakeVisible(portNumberLabel = new Label("PortNum","PortNumber"));
    portNumberLabel->setFont (Font (20.0000f, Font::bold));
    portNumberLabel->setJustificationType (Justification::centredLeft);
    portNumberLabel->setEditable (false, false, false);
    portNumberLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (portNumberTextEditor = new TextEditor ("Client Detail"));
    portNumberTextEditor->addListener(this);
    portNumberTextEditor->setFont (Font (12.00f, Font::plain));
    portNumberTextEditor->setColour (TextEditor::outlineColourId, Colour (0x0));
    portNumberTextEditor->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
    portNumberTextEditor->setColour (TextEditor::shadowColourId, Colour (0x0));
    portNumberTextEditor->setColour (TextEditor::textColourId, Colours::black);
    portNumberTextEditor->setTextToShowWhenEmpty("Enter portnumber ", Colours::grey);

    addAndMakeVisible(clientNameLabel = new Label("Name","ClientName"));
    clientNameLabel->setFont (Font (20.0000f, Font::bold));
    clientNameLabel->setJustificationType (Justification::centredLeft);
    clientNameLabel->setEditable (false, false, false);
    clientNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (clientNameTextEditor = new TextEditor ("Client Detail"));
    clientNameTextEditor->addListener(this);
    clientNameTextEditor->setFont (Font (12.00f, Font::plain));
    clientNameTextEditor->setColour (TextEditor::outlineColourId, Colour (0x0));
    clientNameTextEditor->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
    clientNameTextEditor->setColour (TextEditor::shadowColourId, Colour (0x0));
    clientNameTextEditor->setColour (TextEditor::textColourId, Colours::black);
    clientNameTextEditor->setTextToShowWhenEmpty("Enter name", Colours::grey);

    // labels of error message
    addAndMakeVisible(serverIPError = new Label("Error ServerIP","Enter ServerIP"));
    serverIPError->setFont (Font (12.0000f, Font::bold));
    serverIPError->setJustificationType (Justification::centredLeft);
    serverIPError->setEditable (false, false, false);
    serverIPError->setVisible(false);
    serverIPError->setColour (Label::textColourId, Colours::red);

    addAndMakeVisible(portNumberError = new Label("Error port number","Enter port number"));
    portNumberError->setFont (Font (12.0000f, Font::bold));
    portNumberError->setJustificationType (Justification::centredLeft);
    portNumberError->setEditable (false, false, false);
    portNumberError->setVisible(false);
    portNumberError->setColour (Label::textColourId, Colours::red);

    addAndMakeVisible(clientNameError = new Label("Error client name","Enter client name"));
    clientNameError->setFont (Font (12.0000f, Font::bold));
    clientNameError->setJustificationType (Justification::centredLeft);
    clientNameError->setEditable (false, false, false);
    clientNameError->setVisible(false);
    clientNameError->setColour (Label::textColourId, Colours::red);
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
    XmlElement saveConnection ("Configuration");
    XmlElement * connectionDetail = new XmlElement ("ServerIP");


    connectionDetail->addTextElement(getServerIPAddress());
    saveConnection.addChildElement(connectionDetail);
    connectionDetail = new XmlElement ("PortNumber");
    connectionDetail->addTextElement(String(getPortNumber()));
    saveConnection.addChildElement(connectionDetail);
    connectionDetail = new XmlElement ("ClientName");
    connectionDetail->addTextElement(getClientName());
    saveConnection.addChildElement(connectionDetail);

    saveConnection.writeToFile(File::getCurrentWorkingDirectory().getChildFile("csProp.xml"), String::empty);

}

void GUI::ClientSettingComponent::buttonClicked(Button * buttonThatWasClicked)
{
    if(buttonThatWasClicked == okImageButton)
    {
        if(serverIPTextEditor->getText().isEmpty())
            serverIPError->setVisible(true);
        else
            serverIPError->setVisible(false);
        if(portNumberTextEditor->getText().isEmpty())
            portNumberError->setVisible(true);
        else
            portNumberError->setVisible(false);
        if(clientNameTextEditor->getText().isEmpty())
            clientNameError->setVisible(true);
        else
            clientNameError->setVisible(false);
        if(serverIPTextEditor->getText().isEmpty() | portNumberTextEditor->getText().isEmpty() | clientNameTextEditor->getText().isEmpty())
            return;
        if(connectClient)
        {
            if(!connector)
                connector = new NetworkConnection::ClientConnection(*this);
            if(connector->connectToServer(true))
                getConnected = true;
            else
                connector->disconnect();
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

void GUI::ClientSettingComponent::textEditorTextChanged(TextEditor &editor)
{
    if(!serverIPTextEditor->getText().isEmpty())
    {
        serverIPError->setVisible(false);
    }
    if(!portNumberTextEditor->getText().isEmpty())
    {
        portNumberError->setVisible(false);
    }
    if(!clientNameTextEditor->getText().isEmpty())
    {
        clientNameError->setVisible(false);
    }
}


