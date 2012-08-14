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

#ifndef hpp_cpp_ClientSettingComponent_cpp_hpp
#define hpp_cpp_ClientSettingComponent_cpp_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// We need client
#include "../../Network/NetworkConnection.hpp"

namespace NetworkConnection
{
    class ClientConnection;
}
namespace GUI
{
    class MainAppWindow;

    class ClientSettingComponent : public Component,
                                   public ButtonListener
    {
        // Members
    private:
        /** For checking whether client is connecting first time */
        bool                                connectClient;
        /** For knowing whether client is connected or not */
        bool                                getConnected;
        /** notify client added successfully */
        bool                                clientAdded;
        /** Label and TextEditor for server IP address */
        ScopedPointer<Label>                serverIPLabel;
        ScopedPointer<TextEditor>           serverIPTextEditor;
        /** Label and TextEditor for ProtNumber */
        ScopedPointer<Label>                portNumberLabel;
        ScopedPointer<TextEditor>           portNumberTextEditor;
        /** Label and Text Editor for ClientName */
        ScopedPointer<Label>                clientNameLabel;
        ScopedPointer<TextEditor>           clientNameTextEditor;
        /** Label for ClientIP */
        ScopedPointer<Label>                clientIPLabel;
        /** Ok Button */
        ScopedPointer<TextButton>           okTextButton;
        /** Connection object that creates connection with server */
        NetworkConnection::ClientConnection connector;
        /**owner Component */
        Component                       *   ownerComponent;

        // Methods
    public:
        // Component Interface
         /** This paints graphical components */
        void paint(Graphics & g);
        /** This resize and set components on screen */
        void resized();

        //ButtonListener Interface
		/** Button Listener to listen when a button is pressed */
        void buttonClicked(Button * buttonThatWasClicked);

        // Class Method
        /** Metho for setting bound of all labels and texteditor */
        void setGUIConfiguration();
        /** This saves Connection Detail in XML file */
        void writeToXML();

        /**  inline method for getting portnumber */
        inline int getPortNumber(){ return portNumberTextEditor->getText().getIntValue(); }
        /** inline method for getting serverIP address */
        inline String getServerIPAddress() { return serverIPTextEditor->getText(); }
        /**  inline method for getting clientname */
        inline String getClientName() { return clientNameTextEditor->getText(); }
        /** inline method for getting clientcinnected */
        inline bool isConnectClient() { return connectClient;    }
        /** inline method for ckecking connection of client*/
        inline bool isClientConnected(){    return getConnected;    }
        /** inline method for getting client added*/
        inline bool isClientAdded(){    return clientAdded; }
        /** inline method for setting clientAdded */        
        inline void setClientAdded(bool added){   clientAdded = added; }

        // Constructor & Destructor
    public:
        /** Constructor 
            @param[in]   connectClient   Check whether client is firsttime*/
        ClientSettingComponent(const bool connectClient);

        ClientSettingComponent(const bool connectClient, Component * component);
        /** Destructor */
        ~ClientSettingComponent();
    private:
        // (prevent copy constructor and operator= being generated..)
        ClientSettingComponent (const ClientSettingComponent&);
        const ClientSettingComponent& operator= (const ClientSettingComponent&);
    };
}

#endif // hpp_cpp_ClientSettingComponent_cpp_hpp