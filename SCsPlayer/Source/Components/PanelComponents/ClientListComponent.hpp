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
namespace GUI
{
	class Client : public Component
	{
	private:
		ToggleButton * permissionTB;

	public:
		void resized();
		void paint(Graphics &g);
		void buttonStateChanged(ToggleButton* buttonThatWasChanged);

	public:
		Client(const String & name);
		~Client();


	};

	class ClientListComponent : public Component, public ListBoxModel
	{
		// Members
	private:
		ListBox * clientListBox;

		//methods
	public:
		void resized();
		void paint(Graphics & g);
		int getNumRows();
		void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
		Component * refreshComponentForRow(int row, bool isSelected, Component* existingComponentToUpdate);

		// Cosntructor & Destructor
	public:
		ClientListComponent(); 
		~ClientListComponent();
	};
}

#endif // hpp_ClientListComponent_hpp