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
        /** ListBox object which is holding this component */
        ListBox             &           ownerListBox;
        /** Client Information is all stored in here */
        Configurations::ClientInfo      clientInfo;
        /** Number of row in listbox this item is set for */
        int                             rowNumber;
		/** Toggle Button for Access Permission */
		ScopedPointer< ToggleButton> accessToggleButton;
		/** Flag to show this is being dragged or not */
        bool                            isDragging;
        /** When not selected select when mouse up */
        bool                            selectRowOnMouseUp;
        /** When show details is true - Show by name else by Ipaddress */
		bool							showDetail;

    public:
        // Component interface 
        void resized();
        void paint(Graphics &g);
        /** Forward isSelected Property to next Class. 
            @param[in] selected     Boolean value to select/deselect item */
        void setSelected(bool selected);
		/** To perform action on button press of accessTB */
		void buttonClicked (Button* buttonThatWasClicked);
		/** Set clientinfo to provided updated client information */
        void setClientInfo(Configurations::ClientInfo clInfo);
		/** Called when a mouse button is pressed while it's over this component. */
        void mouseDown(const MouseEvent & e);
        /** Called when a mouse button is released. */
        void mouseUp(const MouseEvent & e);

		inline void setShowDetail(bool show) {	showDetail = show; repaint(); }
		inline bool getShowDetail() {	return showDetail; }
       
        // Constructor & Destructor
    public:
        /** Constructor */
        ListBoxItemComponent(Configurations::ClientInfo clientInfo, ListBox & ownerListBox, const int rowNum);
        /** Destructor */
        ~ListBoxItemComponent();
	private:
		/** (prevent copy constructor and operator= being generated..)*/
		ListBoxItemComponent (const ListBoxItemComponent&);
		const ListBoxItemComponent& operator= (const ListBoxItemComponent&);
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////////////	
    /**  This class is used to show number of clients are possibly attached to CsPlayer Server */
    class ClientListComponent : public Component, public ListBoxModel
    {
        // Members
    private:
        bool                                firstCall;
        /** ListBox which is shown in this component to show clients */
        ScopedPointer<ListBox>              clientListBox;
        /** Array of ClientInfo */
        Array<Configurations::ClientInfo>   clientInfoArray;
		/** main Element to take document of XMLDocument */
        ScopedPointer<XmlElement>           mainElement;
        /** The CsLookAndFeel object for showing customized scrollbar */
        CsLookAndFeel                       csLnF;
        
        // Methods
    public:
        // Component interface 
        void resized();
        void paint(Graphics & g);
		/** Called when a mouse button is pressed while it's over this component. */
        void mouseDown(const MouseEvent & e);

        // ListBoxModel interface
        /** return number of rows we have in this listBox */
        int getNumRows();
        /** paint ListBox item*/
        void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
        /** Add new component or refresh here */
        Component * refreshComponentForRow(int row, bool isSelected, Component* existingComponentToUpdate);
        
		// Class Methods
		/** Add clientInfo into array as new client is added to Server */
        void addClient(Configurations::ClientInfo clientInfo);
        /** When client is connected ot disconnected */
        bool connectClient(Configurations::ClientInfo clientInfo);
        /** When client is connected ot disconnected */
        bool disconnectClient(Configurations::ClientInfo clientInfo);

        /** read from xml and create client list */
        void readClientDetailsFromXML();
		/** write to xml and create xml file */
		void writeClientDetailsToXML();
		/**setting control access value in clientInfoArray*/
		void setAccess(bool access, int row);
		
			
        // Cosntructor & Destructor
    public:
        /** Cosntructor */
        ClientListComponent(); 
        /** Destructor */
        ~ClientListComponent();

	private:
		/** (prevent copy constructor and operator= being generated..)*/
		ClientListComponent (const ClientListComponent&);
		const ClientListComponent& operator= (const ClientListComponent&);
    };
}

#endif // hpp_ClientListComponent_hpp