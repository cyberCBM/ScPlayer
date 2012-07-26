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

#ifndef hpp_cpp_ClientSettingComponent_cpp_hpp
#define hpp_cpp_ClientSettingComponent_cpp_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// We Need Client
#include "../../Network/NetworkConnection.hpp"

namespace GUI
{
    class MainAppWindow;

    class ClientSettingComponent : public Component,
                                   public ButtonListener,
                                   public TextEditorListener
    {
        // Members
    private:
        /** For checking whether client is connecting first time */
        bool                            connectClient;
        bool                            getConnected;
        bool                            clientAdded;
        /** Label and TextEditor for server IP address */
        ScopedPointer<Label>            serverIPLabel;
        ScopedPointer<TextEditor>       serverIPTextEditor;
        /** Label and TextEditor for ProtNumber */
        ScopedPointer<Label>            portNumberLabel;
        ScopedPointer<TextEditor>       portNumberTextEditor;
        /** Label and Text Editor for ClientName */
        ScopedPointer<Label>            clientNameLabel;
        ScopedPointer<TextEditor>       clientNameTextEditor;

        /** Label for serverIP error */
        ScopedPointer<Label>            serverIPError;
        /** Label for port number error */
        ScopedPointer<Label>            portNumberError;
        /** Label for clientName error */
        ScopedPointer<Label>            clientNameError;

        /** Label for ClientIP */
        ScopedPointer<Label>            clientIPLabel;
        /** Ok Button */
        ScopedPointer<ImageButton>      okImageButton;
        /** Connector object */
        NetworkConnection::ClientConnection *  connector;

        // Methods
    public:
        // Component Interface
         /** This paints graphical components */
        void paint(Graphics & g);
        /** This resize and set components on screen */
        void resized();
        /** Called when the user changes the text in some way */
        void textEditorTextChanged (TextEditor &editor);

        // TextEditorListener interface

        //ButtonListener Interface
		/** Button Listener to listen when a button is pressed */
        void buttonClicked(Button * buttonThatWasClicked);

        // Class Method
        /** Metho for setting bound of all labels and texteditor */
        void setGUIConfiguration();
        /** This saves Connection Detail in XML file */
        void saveToXML();
        /**  inline method for getting portnumber */
        inline int getPort(){ return portNumberTextEditor->getText().getIntValue(); }
        /** inline method for getting serverIP address */
        inline String getServerIPAddress() { return serverIPTextEditor->getText(); }
        /**  inline method for getting clientname */
        inline String getClientName() { return clientNameTextEditor->getText(); }

        inline bool isClientConnected(){    return getConnected;    }
        inline bool isClientAdded(){    return clientAdded; }
        inline void setClientAdded(bool added){   clientAdded = added; }

        // Constructor & Destructor
    public:
        /** Constructor 
            @param[in]   connectClient   Check whether client is firsttime*/
        ClientSettingComponent(const bool connectClient );
        /** Destructor */
        ~ClientSettingComponent();
    private:
        // (prevent copy constructor and operator= being generated..)
        ClientSettingComponent (const ClientSettingComponent&);
        const ClientSettingComponent& operator= (const ClientSettingComponent&);
    };
}

#endif // hpp_cpp_ClientSettingComponent_cpp_hpp