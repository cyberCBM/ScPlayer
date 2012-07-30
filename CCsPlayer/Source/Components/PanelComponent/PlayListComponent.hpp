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

#ifndef hpp_PlayListComponent_hpp
#define hpp_PlayListComponent_hpp

#include "../JuceLibraryCode/JuceHeader.h"
// Included to get our structure definitions from here
#include "../../Common/Configurations.hpp"
// Included to get the Look and Feel Component
#include "../../Common/CsLookAndFeel.hpp"

namespace GUI
{
	/** PlayListComponent class contains the playlist and the features of the playlist. Also communication with the player
	    component is been implemented here. PlayListComponent class inherits ListBoxModel, Component, ButtonListener and FileDragAndDropTarget classes */
    class PlayListComponent  : public ListBoxModel,
							   public Component,
							   public ButtonListener,
							   public FileDragAndDropTarget
	{
    private:
			//Members
			/** Boolean to initialise the class only once in resized method */
			bool	                                firstCall;
			/** playListBox contains the list of Songs */
			ScopedPointer<ListBox>					playListBox;
			/** Browse button to browse the audio files from the disk */
			ScopedPointer<ImageButton>				browseImageButton;
			/** Save button to save the current playlist */
			ScopedPointer<ImageButton>				saveImageButton;
			/** A File Array contains the files present in the PlayList */
			Array<Configurations::Media>            mediaArray;
			/** Contains the audio formats supported by the Player */
			String									audioFormats;
			/** Used to write/get data to/from xml file */
			ScopedPointer<XmlElement>				mainElement;
            /** The CsLookAndFeel object for showing customized scrollbar */
            CsPlayerLookAndFeel                     csLnF;			

		public:
			// Component interface
			/** This resize and set components on screen */
			void resized ();
			/** This paints graphical components */
			void paint (Graphics & g);

			//ButtonListener Interface
			/** Button Listener to listen when a button is pressed */
			void buttonClicked (Button * buttonThatWasClicked);

			// ListBoxModel interface
			/** Get the Number of Rows in a playListBox */
			virtual int getNumRows();
			/** Paints the playListBox at regular interval */
			virtual void paintListBoxItem (int rowNumber, Graphics & g, int width, int height, bool rowIsSelected);
			/** Delete a song from the PlayList */
			void deleteKeyPressed (int rowSelected);
			/** Play a song from the PlayList when return key is pressed */
			void returnKeyPressed (int lastRowSelected);
			/** Play a song from the PlayList when the item is double clicked */
			void listBoxItemDoubleClicked (int row, const MouseEvent & e);
		
			//FileDragAndDropTarget interface
			/**	Callback to check whether this target is interested in the set of files being offered */
			virtual bool isInterestedInFileDrag (const StringArray & files);
			/** Callback to indicate that the user has dropped the files onto this component */
			virtual void filesDropped (const StringArray & files, int x, int y);			

			//Class Methods
		public:
			/** Get the song details from the playlist file 
			    @param [in] playListFile	passes the file path as an input */
			void getPlaylist (const String & playListFile);
			/** Set the songs and display in the PlayList 
			    @param [in] playListFile	passes the file path as an input */
			void setPlaylist (const String & playListFile);
			/** Save the playlist at a location in the disk */
			void savePlayList();
			/** Save the default playlist when the player is closed */
			void saveDefaultPlayList();
			/** Check whether the audio file format is supportyed or not 
			    @param [in] playListFile	passes the extension of a file as an input 
			    @return	true/false			returns true if the file is of supported audio format else false */
			bool isAudioFormat (const String & fileExtension);
			/** Drops the dragged songs in the playlist 
			    @param [out, in] files		gives the string array of the paths of the files dropped
							                sourceComponent the component where the files are dropped */
			void dropToPlayList (const StringArray & files, const Component * sourceComponent);
			
			// Constructor & Destructor
		public:
			/** Constructor */
			PlayListComponent ();
			/** Destructor */
			~PlayListComponent();

		private:
			// (prevent copy constructor and operator= being generated..)
			PlayListComponent (const PlayListComponent&);
			const PlayListComponent& operator= (const PlayListComponent&);
	};
}
#endif   // hpp_PlayList_hpp