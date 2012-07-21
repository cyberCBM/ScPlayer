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
#include "../../Common/Configurations.hpp"
 
namespace GUI
{
	class Client : public Component
	{
	private:
        bool            isConnected;
        bool            isSelected;
		ToggleButton *  permissionTB;
		
	public:
		void resized();
		void paint(Graphics &g);
		void buttonStateChanged(ToggleButton * buttonThatWasChanged);

        void GUI::Client::setSelected(bool selected);

	public:
		Client(Configurations::ClientInfo clientInfoDetails);
		~Client();
	};

///////////////////////////////////////////////////////////////////////////////////////////////////////	

	class ClientListComponent : public Component, public ListBoxModel
	{
	// Members
	private:
		ListBox		*                       clientListBox;
		Array <Configurations::ClientInfo>  clientInfoArray;
	//xml data Members
		 ScopedPointer<XmlElement> demoData;   // This is the XML document loaded from the embedded file "demo table data.xml"
		 XmlElement* dataList;   // A pointer to the sub-node of demoData that contains the list of data rows
		 int numRows;    
	//methods
	public:
		void setClientDetails();
		void resized();
		void paint(Graphics & g);
		int getNumRows();
		void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
		Component * refreshComponentForRow(int row, bool isSelected, Component* existingComponentToUpdate);

        void addClientInfo(Configurations::ClientInfo clientInfo);

	// Cosntructor & Destructor
	public:
		ClientListComponent(); 
		~ClientListComponent();
	};
}

#endif // hpp_ClientListComponent_hpp