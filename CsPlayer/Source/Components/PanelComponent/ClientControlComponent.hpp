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
// We need to show clock here
#include "ClockComponent.hpp"

namespace NetworkConnection
{
    class ClientConnection;
}
namespace GUI 
{
    class PlayListComponent;
    /** This class have controller and connector to server */
    class ClientControlComponent : public Component,
                                   public ButtonListener                        
    {
    // Members
    private:
        /** Port Number on which server is listening. */
        int                                         portNumber;
        /** Boolean to initialise the class only once in resized method */
        bool                                        firstCall;
        /** Boolean to check connection between client and server */
        bool                                        isConnected;
        /** Boolean to check connection between client and server */
        bool                                        serverLocked;

        bool                                        songStopped;
        /** clock Component to show time */
        ScopedPointer<ClockComponent>               clockComp;
        /** Image button for connect/disconnect */
        ScopedPointer<ImageButton>                  connectImageButton;
        /** Image button for lock/unlock Server */
        ScopedPointer<ImageButton>                  lockUnlockImageButton;
        /** Image button for setting */
        ScopedPointer<ImageButton>                  settingImageButton;
        /** Image button for backward*/
        ScopedPointer<ImageButton>                  backwardImageButton;
        /** Image button for play/pause */
        ScopedPointer<ImageButton>                  playPauseImageButton;
        /** Image button for forward */
        ScopedPointer<ImageButton>                  forwardImageButton;
        /** Image button for stop */
        ScopedPointer<ImageButton>                  stopImageButton;
        /** Image button for about */
        ScopedPointer<ImageButton>                  aboutImageButton;
        /** Image button for about */
        ScopedPointer<ImageButton>                  ServerLockImageButton;

        /** main Element that hold documentElement (root) */
        ScopedPointer<XmlElement>                   mainElement;
        /** Connector that communicate with Server */
        NetworkConnection::ClientConnection         connector;
        /** ServerIP address used to connect to Server CsPlayer */
        String                                      serverIpAddress;
        /** Client Name that is shown in Server for you. */
        String                                      clientName;

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
        /** For making connection to server client need to set some values(Settings) 
            like :  IpAddress of CsPlayer Server is running on 
                    Port No on which Csplayer is listening clients 
                    Name of Self, which is used to identify yourself on Server */
        void showSettingComponent();
        /** Return PlayListComponent which is used to send 
            * playList changed information
            * file added or removed information
            * Current playing show information */
        PlayListComponent *     getPlayListComponent();
        /** inline method for setting serverIp address */
        inline void setServerIpAddress(const String & ipAddress){ serverIpAddress = ipAddress;  }
        /** inline method for setting port number */
        inline void setPortNumber(const int portNo){ portNumber = portNo;  }
        /** inline method for setting client name */
        inline void setClientName(const String & name){ clientName = name;  }
        /** inline method for getting portnumber */
        inline int getPortNumber(){ return portNumber; }
        /** inline method for getting serverIP address */
        inline String getServerIPAddress() { return serverIpAddress; }
        /** inline method for getting clientname */
        inline String getClientName() { return clientName; }
        /** When song is send by doubl click or pressing enter */
        void songDoubleClickedPlay(const int index);
        /** When Client is disconnected */
        void setClientDisconnected();
        /** Managing client's Lock */
        void manageLock(bool lockGranted);
        /** When server is locked or Unlocked other clients are informed (Not self) */
        void serverIsLocked(bool locked);
        /** Send new added song to server 
            @param[in]  playList    playList as XmlElement */
        void addInPlayListToServer(const String & playList);
        /** Send new added song to server 
            @param[in]  indexList    indexes of all deleted rows */
		void deleteInPlayListToServer(const Array<int> & indexList);
        /** Send stop signal to server only when I have lock */
        void sendStopToServer();
        /** I have got Stop signal from server*/
        void serverSentStop();
        /** I have got Pause signal from server*/
        void serverSentPause();
        /** I have got Play signal from server*/
        void serverSentPlay();

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