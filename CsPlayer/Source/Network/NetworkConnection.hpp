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

#ifndef hpp_NetworkConnection_hpp
#define hpp_NetworkConnection_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"
// We need protocol definitions 
#include "../Common/Protocols.hpp"

namespace GUI
{
    class ClientSettingComponent;
    class ClientControlComponent;
}
namespace NetworkConnection
{
    class ClientConnection : public InterprocessConnection
    {
    private:
        /** Owner Component to communicate data inside application */
        Component *                     ownerComponent;
        /** This is clientSetting component used for adding client to server */
        GUI::ClientSettingComponent *   settingComp;
        /** This is clientControl component which 
            control communication to/from server */
        GUI::ClientControlComponent *   controlComp;
        /** common AlertWindow shown wheen needed */
        ScopedPointer<AlertWindow>      alertWin;
        /** Messenger protocols are difined by this one */
        Configurations::Protocols       messengerProtocol;

    public:
        // InterprocessConnection Interface 
        /** Called when the connection is first connected. */
        void 	connectionMade ();
        /** Called when the connection is broken. */
        void 	connectionLost ();
        /** Called when a message arrives. */
        void 	messageReceived (const MemoryBlock &message);
        /** to create and read message protocols */
        Configurations::Protocols messageProtocols;

        // Class Interface
        /** Method for connecting to server */
        bool connectToServer(bool firstTime);
        /** This method set current ownerComponent for this connection
            @param[in]  ownerComp   When first time for this application it is clientSettingComponent
                                    When Normal for this application it is clientControlComponent */
        void setOwnerComponent(Component * ownerComp);
        /** Method for acquiring lock on server */
        void acquireLockOnServer();
        /** Method for releasing lock on server */
        void releaseLockOnServer();

        void sendPlayAfterPauseToServer();

        void sendPlayToServer();

        void sendPauseToServer();

        void sendStopToServer();

        void sendBackToServer();

        void sendNextToServer();

        void songDoubleClickedPlay(const int index);

		void sendDragDropIndex(const String & sourceIndexString, const String & insertionIndex);
        /** To send add of song/songs in playList */
		void sendAddInPlayList(const String & playList);
		/** To send add of song/songs in playList */
		void sendDropInPlayList(const String & playList, int insertionIndex);
		/** To send delete of song/songs in playList */
		void sendDeleteInPlayList(const Array<int> & indexList);

        // Constructor and Destructor 
    public:
        /** Constructor */
        ClientConnection ();
        /** Destructor */
        ~ClientConnection();
    private:
        // (prevent copy constructor and operator= being generated..)
        ClientConnection (const ClientConnection&);
        const ClientConnection& operator= (const ClientConnection&);
    };
}

#endif // hpp_NetworkConnection_hpp