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

GUI::ClientSettingComponent::ClientSettingComponent(const bool connectClient ) : serverIPLabel(nullptr), serverIPTextEditor(nullptr), 
                                                            portNumberLabel(nullptr),portNumberTextEditor(nullptr), 
                                                            clientNameLabel(nullptr), clientNameTextEditor(nullptr),
                                                            clientIPLabel(nullptr), connectClient(connectClient),
                                                            okButton(nullptr), connector(0), connectButton(nullptr)
{
    connector = new NetworkConnection::ClientConnection(*this);
    //setSize(300,350);
    setGUIConfiguration();
    addAndMakeVisible(okButton = new TextButton("OK"));
    okButton->addButtonListener(this);
    addAndMakeVisible(connectButton = new TextButton("Connect"));
    connectButton->addButtonListener(this);

}

GUI::ClientSettingComponent::~ClientSettingComponent()
{
    //saveToXML();
    deleteAndZero(connector);
}


void GUI::ClientSettingComponent::paint(Graphics & g)
{

}

void GUI::ClientSettingComponent::resized()
{
    setSize(300,350);
    Font font = portNumberLabel->getFont();
    int width = font.getStringWidth(portNumberLabel->getText());
    serverIPLabel->setBounds(5, 15, width, (int)font.getHeight() );
    serverIPTextEditor->setBounds(10 + width, 15 , 150 , (int)font.getHeight() + 5);
    portNumberLabel->setBounds(5, 35 + (int)font.getHeight(), width, (int)font.getHeight());
    portNumberTextEditor->setBounds(10 + width, 35 + (int)font.getHeight(), 150, (int)font.getHeight() + 5);
    clientNameLabel->setBounds(5, 55 +(2 * (int)font.getHeight()), width, (int)font.getHeight());
    clientNameTextEditor->setBounds(10 + width, 55 + (2 *(int)font.getHeight()), 150, (int)font.getHeight() + 5);
    if(connectButton)
        connectButton->setBounds(getWidth()/2 - (connectButton->getWidth()/2), getHeight()/2 , 50, 50);
    if(okButton)
        okButton->setBounds(getWidth()/2 - (connectButton->getWidth()/2), getHeight()/2 , 50, 50);
}

void GUI::ClientSettingComponent::setGUIConfiguration()
{
    addAndMakeVisible(serverIPLabel = new Label("ServerIP","Server IP"));
    serverIPLabel->setFont (Font (20.0000f, Font::bold));
    serverIPLabel->setJustificationType (Justification::centredLeft);
    serverIPLabel->setEditable (false, false, false);
    serverIPLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (serverIPTextEditor = new TextEditor ("Client Detail"));
    serverIPTextEditor->setFont (Font (20.00f, Font::plain));
    //serverIPTextEditor->setTextToShowWhenEmpty("KJD", Colour::brighter());
    serverIPTextEditor->setColour (TextEditor::outlineColourId, Colour (0x0));
    serverIPTextEditor->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
    serverIPTextEditor->setColour (TextEditor::shadowColourId, Colour (0x0));
    serverIPTextEditor->setColour (TextEditor::textColourId, Colours::grey);


    addAndMakeVisible(portNumberLabel = new Label("PortNum","PortNumber"));
    portNumberLabel->setFont (Font (20.0000f, Font::bold));
    portNumberLabel->setJustificationType (Justification::centredLeft);
    portNumberLabel->setEditable (false, false, false);
    portNumberLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (portNumberTextEditor = new TextEditor ("Client Detail"));
    portNumberTextEditor->setFont (Font (20.00f, Font::plain));
    //serverIPTextEditor->setTextToShowWhenEmpty("KJD", Colour::brighter());
    portNumberTextEditor->setColour (TextEditor::outlineColourId, Colour (0x0));
    portNumberTextEditor->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
    portNumberTextEditor->setColour (TextEditor::shadowColourId, Colour (0x0));
    portNumberTextEditor->setColour (TextEditor::textColourId, Colours::grey);


    addAndMakeVisible(clientNameLabel = new Label("Name","ClientName"));
    clientNameLabel->setFont (Font (20.0000f, Font::bold));
    clientNameLabel->setJustificationType (Justification::centredLeft);
    clientNameLabel->setEditable (false, false, false);
    clientNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (clientNameTextEditor = new TextEditor ("Client Detail"));
    clientNameTextEditor->setFont (Font (20.00f, Font::plain));
    //serverIPTextEditor->setTextToShowWhenEmpty("KJD", Colour::brighter());
    clientNameTextEditor->setColour (TextEditor::outlineColourId, Colour (0x0));
    clientNameTextEditor->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
    clientNameTextEditor->setColour (TextEditor::shadowColourId, Colour (0x0));
    clientNameTextEditor->setColour (TextEditor::textColourId, Colours::grey);

    resized();

}

void GUI::ClientSettingComponent::saveToXML()
{
    XmlElement connection("Connection");
    XmlElement* connectionDetail = new XmlElement("Detail");

    connectionDetail->setAttribute("ServerIP Address", serverIPTextEditor->getText());
    connectionDetail->setAttribute("Port Number", portNumberTextEditor->getText().getIntValue());
    connectionDetail->setAttribute("Client Name", clientNameTextEditor->getText());
    
    connection.addChildElement(connectionDetail);

}
        
void GUI::ClientSettingComponent::buttonClicked(Button * buttonThatWasClicked)
{
    if(buttonThatWasClicked == connectButton)
    {
        if(connector->connectToServer(true))
            int k = 0;

    }
    else if(buttonThatWasClicked == okButton)
    {
                
    }
}

       
