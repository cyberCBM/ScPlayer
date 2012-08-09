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

#ifndef hpp_ClientListComponent_hpp
#define hpp_ClientListComponent_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// Get our structure definitions from here
#include "../../Common/Configurations.hpp"
// This provides our custom Csplayer lookAndFeel
#include "../../Common/CsLookAndFeel.hpp"

namespace GUI
{
    /**  This class created client item in ClientListBoxComponent */
    class ListBoxItemComponent : public Component, public ButtonListener 
    {
	public:
		 typedef juce::MouseEvent        MouseEvent;

    private:
        /**  For Row selection */
        bool                            isSelected;
        /** Flag to show this is being dragged or not */
        bool                            isDragging;
        /** When not selected select when mouse up */
        bool                            selectRowOnMouseUp;
        /** When show details is true - Show by name else by Ipaddress */
		bool							showDetail;
        /** ListBox object which is holding this component */
        ListBox             &           ownerListBox;
        /** Client Information is all stored in here */
        Configurations::ClientInfo      clientInfo;
        /** Number of row in listbox this item is set for */
        int                             rowNumber;
		/** Toggle Button for Access Permission */
		ScopedPointer< ToggleButton>    accessToggleButton;
		
        // Methods
    public:
        // Component interface 
        /** Components's size and bounding are set in this methods */
        void resized();
        /** Components's paint related things are in this methods */
        void paint(Graphics &g);
        /** Called when a mouse button is pressed while it's over this component. */
        void mouseDown(const MouseEvent & e);
        /** Called when a mouse button is released.
			@param[in] e    Mouse event to send with */
        void mouseUp(const MouseEvent & e);

        // ButtonListener interface
		/** To perform action on button press of accessTB
			@parm[in] buttonThatWasClicked   button that was clicked to send with */
		void buttonClicked (Button* buttonThatWasClicked);
		
		// Class Methods
		/** Called when a mouse button is pressed while it's over this component.
			@param[in] e    Mouse event to send with */
        void setClientInfo(Configurations::ClientInfo clInfo);
        /** Forward isSelected Property to next Class. 
            @param[in] selected     Boolean value to select/deselect item */
        void setSelected(bool selected);
        /** Set clientinfo to provided updated client information 
		    @param[in] clInfo to set the value of clientInfo*/
		inline void setShowDetail(bool show) {	showDetail = show; repaint(); }
		/** Set the view of clientList by clientName or ClientIPAddress
			@parm[in] show Boolean value to select view type of clientList*/
		inline bool getShowDetail() {	return showDetail; }
       
        // Constructor & Destructor
    public:
        /** Constructor */
        ListBoxItemComponent(Configurations::ClientInfo clientInfo, ListBox & ownerListBox, const int rowNum);
        /** Destructor */
        ~ListBoxItemComponent();
	private:
		// (prevent copy constructor and operator= being generated..)
		ListBoxItemComponent (const ListBoxItemComponent&);
		const ListBoxItemComponent& operator= (const ListBoxItemComponent&);
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////////////	
    /**  This class is used to show number of clients are possibly attached to CsPlayer Server */
    class ClientListComponent : public Component, public ListBoxModel
    {
        // Members
    private:
       bool                                 firstCall;
        /** ListBox which is shown in this component to show clients */
        ScopedPointer<ListBox>              clientListBox;
        /** Array of ClientInfo */
        Array<Configurations::ClientInfo>   clientInfoArray;
		/**csPlayer.xml file path*/
		String                              csplayerxmlFilePath;
        /** The CsLookAndFeel object for showing customized scrollbar */
        CsLookAndFeel                       csLnF;
        
        // Methods
    public:
        // Component interface 
        /** Components's size and bounding are set in this methods */
        void resized();
        /** Components's paint related things are in this methods */
        void paint(Graphics &g);
		/** Called when a mouse button is pressed while it's over this component.
			 @param[in] e    Mouse event to send with */
        void mouseDown(const MouseEvent & e);
        
        // ListBoxModel interface
        /** return number of rows we have in this listBox */
        int getNumRows();
        /** paint ListBox item*/
        void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
		/** Add new component or refresh here 
			@param[in]  rowNumber                   Row Number which is reshreshed for this component
            @param[in]  isRowSelected               Is that row selected or not ?
            @param[in]  existingComponentToUpdate   If component exist or create new custom component for listbox item
            @return     Component                   Existing or new created CustomItemComponent */
        Component * refreshComponentForRow(int row, bool isSelected, Component* existingComponentToUpdate);
        
		// Class Methods
        /** read from xml and create client list */
        void readClientDetailsFromXML();
		/** write to xml and create xml file */
		void writeClientDetailsToXML();
		/**setting control access value in clientInfoArray
			@parm[in] boolean access true if allow access  false if not allowed
			@parm[in] row for perticular client*/
		void setAccess(bool access, int row);
        /** Add clientInfo into array as new client is added to Server
			@parm[in] clientINfo   is to add new client in clientInfoArray*/
        void addClient(Configurations::ClientInfo & clientInfo);
        /** When client is connected
		    @parm[in]  clientInfo to check is connected or not?
			return true if is connected,false if is not connected*/
        bool connectClient(Configurations::ClientInfo clientInfo);
        /** When client is  disconnected
		    @parm[in]  clientInfo to check is connected or not?
			return true if is connected,false if is not connected*/
        bool disconnectClient(Configurations::ClientInfo clientInfo);
        /** When client is connected and get lock from this client */
        void setClientHasLock(Configurations::ClientInfo clientInfo);

        // Cosntructor & Destructor
    public:
        /** Cosntructor */
        ClientListComponent(); 
        /** Destructor */
        ~ClientListComponent();

	private:
		// (prevent copy constructor and operator= being generated..)
		ClientListComponent (const ClientListComponent&);
		const ClientListComponent& operator= (const ClientListComponent&);
    };
}

#endif // hpp_ClientListComponent_hpp