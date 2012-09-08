/*                                                                                  
*=====================================================================================
*ScPlayer - Server Client Player                                                                   |
*Music file player that works in Network                                             |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com															 |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
*                                                                                    |
*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
* ScPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the ScPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

#ifndef hpp_ControlBarComponent_hpp
#define hpp_ControlBarComponent_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// This is used to create server and client connections 
#include "../../Network/NetworkConnection.hpp"
// It gives following components on need
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
        ScopedPointer<ImageButton>  lockUnlockImageButton;
        /** Clock Component that is managed by timer */
        ScopedPointer<drow::Clock>  clockComp;
        /** Server that use IP and PortNumber to start self as server */
        ScopedPointer<NetworkConnection::ServerConnection> csServer;

        // Methods
    public:
        /** Component interface */
        void resized();
        void paint(Graphics & g);
        /** ButtonListener interface */
        void buttonClicked (Button * button);
        /** Disconnect the client if client is already connected and server cut it down. 
			@param[in]	clientIpAddress		The client's address which need to be disconnected from server
			@param[in]	hadLock				If it had lock release it and manage the lock */
        void disconnectConnectedClient(const String & clientIpAddress, const bool hadLock);
        
        // Class methods
        inline bool IsServerLocked(){   return lockUnlockImageButton->getToggleState(); }
        /** This method shows AudioSetting component which changes AudioDeviceManager */
        void showAudioSettings();
        /** It shows About Page which has information regarding 
            * Application
            * Team
            * Source Code
            * Licence */
        void showAboutUs();
        /** This method manage Server's lock button 
            @param[in] lock         To apply lock(true) or false
            @return    true/false   If locked return true else return false */
        bool manageServerLock(const bool lock);
        /** Send current playing index to all clients out there 
            @param[in]  index   */
        void sendPlayingIndexToAllClients(const int index);
        /** Send added songs in playingList to all clients out there 
            @param[in]  playList */
		void addInPlayListToAllClients(const String & playList);
        /** Send added songs in playingList to all clients out there 
            @param[in]  filesNamesArray 
			@param[in]  insertionIndex */
		void dropInPlayListToAllClients(const String & playList, int insertionIndex);
		/** Send delete songs in playingList to all clients out there 
            @param[in]  indexList */
		void deleteInPlayListToAllClients(const Array<int> & indexList);
        /** Send pause signal to all the clients out there */
        void sendPauseToAllClients();
        /** Send Stop signal to all the clients out there */
        void sendStopToAllClients();
        /** Send Play signal to all the clients out there */
        void sendPlayToAllClient();
		/** Send Drag Drop signal to all the clients out there */
		void sendDragDropIndexToAllClients(const String sourceIndexString, const String insertionIndex);

        /** Return ClientListComponentwhich is used to send 
            * new client added 
            * client connected
            * client acquired lock */
        ClientListComponent *   getClientListComponent();
        /** Return PlayListComponent which is used to send 
            * playList changed information
            * file added or removed information
            * Current playing show information */
        PlayListComponent *     getPlayListComponent();
        /** Return PlayerComponent which is used to send 
            * Play/pause/Stop/Back/Next
            * Notice we don't send any seeking info to client */
        PlayerComponent *       getPlayerComponent();

        // Constructor & Destructor
    public:
        /** Constructor 
            @param[in/out] audioDeviceManager       Audio Device Manager that do audio setting */
        ControlBarComponent(AudioDeviceManager & audioDeviceManager);
        /** Destructor */
        ~ControlBarComponent();
    private:
        // (prevent copy constructor and operator= being generated..)
        ControlBarComponent (const ControlBarComponent&);
        const ControlBarComponent& operator= (const ControlBarComponent&);
    };
}

#endif // hpp_ControlBarComponent_hpp