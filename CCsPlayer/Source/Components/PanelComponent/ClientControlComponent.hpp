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


#ifndef hpp_ClientControlComponent_hpp
#define hpp_ClientControlComponent_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// We need client
#include "../../Network/NetworkConnection.hpp"
// We need BusyWheel Component
#include "../Panels/RightPanel.hpp"


namespace NetworkConnection
{
    class ServerConnection;
    class ClientConnection;
}

namespace GUI 
{
    class ClientControlComponent : public Component,
                                   public ButtonListener
                        
    {
    // Members
    private:
        /** Boolean to initialise the class only once in resized method */
        bool                                        firstCall;
        
        ScopedPointer<drow::Clock>                clockComp;

        /** Image button for connect/disconnect */
        ScopedPointer<ImageButton>                connectButton;
        /** Image button for setting */
        ScopedPointer<ImageButton>                settingButton;
        /** Image button for backward*/
        ScopedPointer<ImageButton>                backwardButton;
        /** Image button for play/pause */
        ScopedPointer<ImageButton>                playPauseButton;
        /** Image button for forward */
        ScopedPointer<ImageButton>                forwardButton;
        /** Image button for stop */
        ScopedPointer<ImageButton>                stopButton;
        /** Image button for about */
        ScopedPointer<ImageButton>                aboutButton;

        ScopedPointer<XmlElement>                   mainElement;
        
        NetworkConnection::ClientConnection  *     connector;

        /** ServerIP address */
        String serverIpAddress;
        /** Port Number */
        int portNumber;
        /** Client Name*/
        String clientName;

        // Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);

        // ButtonListner interface
        /** This method is called when any button is clicked */
        void buttonClicked (Button* buttonThatWasClicked);

        //Class Method
        /** Showing AboutusComponent */
        void showAboutUs();
        /** For Taking Informstion from client */
        void setConfiguration();
        /** inline method for setting serverIp address */
        inline void setServerIpAddress(const String & ipAddress){ serverIpAddress = ipAddress;  }
        /** inline method for setting port number */
        inline void setPortNumber(const int portNo){ portNumber = portNo;  }
        /** inline method for setting client name */
        inline void setClientName(const String & name){ clientName = name;  }

        /**  inline method for getting portnumber */
        inline int getPortNumber(){ return portNumber; }
        /** inline method for getting serverIP address */
        inline String getServerIPAddress() { return serverIpAddress; }
        /**  inline method for getting clientname */
        inline String getClientName() { return clientName; }


        // Constructor & Destructor
    public:
        /** Constructor */
        ClientControlComponent ();
        /** Destructor */
        ~ClientControlComponent ();
    
    private:
        // (prevent copy constructor and operator= being generated..)
        ClientControlComponent (const ClientControlComponent&);
        const ClientControlComponent& operator= (const ClientControlComponent&);
    };
}

#endif  // hpp_PlayerComponent_hpp