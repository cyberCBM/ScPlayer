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

#ifndef hpp_ControlBarComponent_hpp
#define hpp_ControlBarComponent_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"

#include "../../Netwrok/NetworkConnection.hpp"

#include "ClientListComponent.hpp"

#include "PlayListComponent.hpp"

#include "PlayerComponent.hpp"

namespace NetworkConnection
{
    class ServerConnection;
}

namespace GUI
{
    class ControlBarComponent : public Component, public ButtonListener
    {
        // Members
    private:
        /** Audio Device Manager that hold input and output devices */
        AudioDeviceManager &        audioDeviceManager;
        /** Image button that are controllers for CsPlayer-server */
        ScopedPointer<ImageButton>  audioDeviceSettingImageButton;
        ScopedPointer<ImageButton>  serverImageButton;
        ScopedPointer<ImageButton>  aboutImageButton;
        ScopedPointer<ImageButton>  enableClientsImageButton;

        ScopedPointer<drow::Clock>  clockComp;

        /** Server that use IP and PortNumber to start self as server */
        ScopedPointer<NetworkConnection::ServerConnection> csServer;

        // Methods
    public:
        void resized();
        void paint(Graphics & g);

        void buttonClicked (Button * button);

        void showAudioSettings();

        void showAboutUs();

        ClientListComponent *   getClientListComponent();

        PlayListComponent *     getPlayListComponent();

        PlayerComponent *       getPlayerComponent();

        // Constructor & Destructor
    public:
        ControlBarComponent(AudioDeviceManager & audioDeviceManager);
        ~ControlBarComponent();
    };
}

#endif // hpp_ControlBarComponent_hpp