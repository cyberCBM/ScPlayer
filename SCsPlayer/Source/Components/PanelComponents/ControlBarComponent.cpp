// Control Bar definitions
#include "ControlBarComponent.hpp"
// AboutUs components
#include "AboutusComponent.hpp"
// LookAndFeel to set for scrollBar and other things
#include "../../Common/CsLookAndFeel.hpp"

#include "../MainComponent.hpp"

GUI::ControlBarComponent::ControlBarComponent(AudioDeviceManager & audioDeviceManager) :
audioDeviceManager(audioDeviceManager), audioDeviceSettingImageButton(nullptr), serverImageButton(nullptr),
aboutImageButton(nullptr), enableClientsImageButton(nullptr), clockComp(nullptr), csServer(nullptr)
{
    addAndMakeVisible(audioDeviceSettingImageButton = new ImageButton("Audio Setting"));
    addAndMakeVisible(serverImageButton = new ImageButton("Server Setting"));
    addAndMakeVisible(enableClientsImageButton = new ImageButton("Enable Client"));
    addAndMakeVisible(aboutImageButton = new ImageButton("About us"));
    
    addAndMakeVisible(clockComp = new drow::Clock());

    Image img1, img2;

    img1 = ImageCache::getFromMemory(BinaryData::setting_gif, BinaryData::setting_gifSize);
    audioDeviceSettingImageButton->setImages(true, false, true, 
                                            img1, 1.0f, Colours::transparentBlack,
                                            img1, 0.7f, Colours::transparentBlack,
                                            img1, 1.0f, Colours::transparentBlack);
    audioDeviceSettingImageButton->addButtonListener(this);
    audioDeviceSettingImageButton->setToggleState(false, false);
    audioDeviceSettingImageButton->setTooltip("Audio Settings");
    img1 = ImageCache::getFromMemory(BinaryData::startS_gif, BinaryData::startS_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::stopS_gif, BinaryData::stopS_gifSize);
    serverImageButton->setImages (true, false, true, 
                                img1, 1.0f, Colours::transparentBlack,
                                img1, 0.7f, Colours::transparentBlack,
                                img2, 1.0f, Colours::transparentBlack);
    serverImageButton->addButtonListener(this);
    serverImageButton->setToggleState(false, false);
    serverImageButton->setTooltip("Start Server");
    img1 = ImageCache::getFromMemory(BinaryData::connect_gif, BinaryData::connect_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::disconnect_gif, BinaryData::disconnect_gifSize);
    enableClientsImageButton->setImages (true, false, true, 
                                img1, 1.0f, Colours::transparentBlack,
                                img1, 0.7f, Colours::transparentBlack,
                                img2, 1.0f, Colours::transparentBlack);
    enableClientsImageButton->addButtonListener(this);
    enableClientsImageButton->setToggleState(false, false);
    enableClientsImageButton->setTooltip("Enable Clients");
    img1 = ImageCache::getFromMemory(BinaryData::about_gif, BinaryData::about_gifSize);
    aboutImageButton->setImages(true, false, true, 
                                            img1, 1.0f, Colours::transparentBlack,
                                            img1, 0.7f, Colours::transparentBlack,
                                            img1, 1.0f, Colours::transparentBlack);
    aboutImageButton->addButtonListener(this);
    aboutImageButton->setToggleState(false, false);

    csServer = new NetworkConnection::ServerConnection(*this, enableClientsImageButton->getToggleState());
}

GUI::ControlBarComponent::~ControlBarComponent()
{
    removeChildComponent(clockComp);
}

void GUI::ControlBarComponent::paint(Graphics & g)
{
    // backGround Filling
    g.fillAll (Colour (0xff292929));

    // if needed here show locked status with Red and Green circle (Using eclipse)
}

void GUI::ControlBarComponent::resized()
{
    audioDeviceSettingImageButton->setBounds(proportionOfWidth(0.05f), proportionOfHeight(0.5f) - audioDeviceSettingImageButton->getHeight()/2, audioDeviceSettingImageButton->getWidth(), audioDeviceSettingImageButton->getHeight());
    serverImageButton->setBounds(proportionOfWidth(0.25f), proportionOfHeight(0.5f) - serverImageButton->getHeight()/2, serverImageButton->getWidth(), serverImageButton->getHeight());
    enableClientsImageButton->setBounds(proportionOfWidth(0.45f), proportionOfHeight(0.5f) - enableClientsImageButton->getHeight()/2, enableClientsImageButton->getWidth(), enableClientsImageButton->getHeight());
    aboutImageButton->setBounds(proportionOfWidth(0.65f), proportionOfHeight(0.5f) - aboutImageButton->getHeight()/2, aboutImageButton->getWidth(), aboutImageButton->getHeight());
    const int clockHeight = 20, clockWidth = 70;
    clockComp->setBounds(proportionOfWidth(0.80f), proportionOfHeight(0.5f) - clockHeight/2, clockWidth, clockHeight);
}

void GUI::ControlBarComponent::buttonClicked(Button * button)
{
    // What happens when particular button is clicked ?
    if (button == audioDeviceSettingImageButton) 
    {
        showAudioSettings();
    }
    else if (button == serverImageButton) 
    {
        // start te http server
        serverImageButton->setToggleState(!serverImageButton->getToggleState(), false);
        if(serverImageButton->getToggleState())
        {
            csServer->start();
            Logger::outputDebugString("Cs Server is stopped");
            serverImageButton->setTooltip("Disable Clients");
        }
        else
        {
            csServer->stop();
            Logger::outputDebugString("Cs Server is stopped");
            serverImageButton->setTooltip("Enable Clients");
        }
    }
    else if(button == enableClientsImageButton)
    {
        // start
        enableClientsImageButton->setToggleState(!enableClientsImageButton->getToggleState(), false);
        if(enableClientsImageButton->getToggleState())
        {
            csServer->setEnableClients(true);
            enableClientsImageButton->setTooltip("Enable Clients");
        }
        else
        {
            csServer->setEnableClients(false);
            enableClientsImageButton->setTooltip("Disable Clients");
        }
        
    }
    else if(button == aboutImageButton)
    {
        showAboutUs();
    }
}

void GUI::ControlBarComponent::showAudioSettings()
{
    // Show Audio Setting Page and make audio settings done here.
    AudioDeviceSelectorComponent settingsComp (audioDeviceManager, 0, 2, 0, 2, true, true, true, false);
    settingsComp.setSize (300, 350);
    LookAndFeel settingsLaf;
    settingsLaf.setColour (Label::textColourId, Colours::white);
    settingsLaf.setColour (TextButton::buttonColourId, Colours::white);
    settingsLaf.setColour (TextButton::textColourOffId, Colours::black);
    settingsComp.setLookAndFeel (&settingsLaf);
    // Show the component inside dialog
    DialogWindow::showModalDialog ("Audio Settings", &settingsComp, nullptr, Colours::darkgrey, true, false, false);
}


void GUI::ControlBarComponent::showAboutUs()
{
    // Show About Us Page and give the required information to users.
    AboutUsComponent aboutUsComponent;
    aboutUsComponent.setSize (300, 350);
    CsPlayerLookAndFeel csLnF;
    csLnF.setColour (Label::textColourId, Colours::white);
    csLnF.setColour (TextButton::buttonColourId, Colours::white);
    csLnF.setColour (TextButton::textColourOffId, Colours::black);
    csLnF.setColour (TextEditor::textColourId, Colours::grey);
    aboutUsComponent.setLookAndFeel(&csLnF);
    // Show the component inside dialog
    DialogWindow::showModalDialog ("About CsPlayer", &aboutUsComponent, nullptr, Colours::darkgrey, true, false, false);
}

GUI::ClientListComponent * GUI::ControlBarComponent::getClientListComponent()
{
    return findParentComponentOfClass<GUI::MainComponent>()->getLeftPanel()->getClientListComponent();
}

GUI::PlayListComponent * GUI::ControlBarComponent::getPlayListComponent()
{
    return findParentComponentOfClass<GUI::MainComponent>()->getRightPanel()->getPlayListComponent();
}

GUI::PlayerComponent * GUI::ControlBarComponent::getPlayerComponent()
{
    return findParentComponentOfClass<GUI::MainComponent>()->getCenterPanel()->getPlayerComponent();
}