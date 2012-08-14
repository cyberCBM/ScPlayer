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

#ifndef hpp_PlayListComponent_hpp
#define hpp_PlayListComponent_hpp

#include "../JuceLibraryCode/JuceHeader.h"
// Included to get our structure definitions from here
#include "../../Common/Configurations.hpp"
// Included to get the Look and Feel Component
#include "../../Common/CsLookAndFeel.hpp"

namespace GUI
{
    class ClientControlComponent;
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
            AudioFormatManager						audioFormatManager;
			/** Used to write/get data to/from xml file */
			ScopedPointer<XmlElement>				mainElement;
            /** The CsLookAndFeel object for showing customized scrollbar */
            CsPlayerLookAndFeel                     csLnF;			
            /** Audio format reader and soure to get file duration and all */
            ScopedPointer<AudioFormatReaderSource>  audioSourceReader;
            ScopedPointer<AudioFormatReader>        audioFormatReader;
            /** clientControlComponent to pass infromation to pass to server */
            ClientControlComponent          *       clientControlComponent;
            /** Current playing song's index */
            int                                     playingSongIndex;

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
            /** Set latest playing index from server 
                @param[in]  index latest index to set as current playing */
			inline void setPlayingSongIndex(const int index){    playingSongIndex = index;   repaint(); }
            /** It might be possible that here -1 can be return so take care of it ..... think */
            inline int getCurrentSelectedIndex() 
            {
                if(playListBox->getLastRowSelected() == -1)
                    return 0; 
                else
                    return playListBox->getLastRowSelected(); 
            }
            /** Get the song details from the playlist file 
			    @param [in] playListFile	passes the file path as an input */
			void getPlaylist (const String & playListFile);
			/** Save the playlist at a location in the disk */
			void savePlayList();
			/** Save the default playlist when the player is closed */
			void saveDefaultPlayList();
			/** Drops the dragged songs in the playlist 
			    @param [out, in] files		gives the string array of the paths of the files dropped
							                sourceComponent the component where the files are dropped */
			void dropToPlayList (const StringArray & files, const Component * sourceComponent);
			/** Update current playlist from the serverPlayList while connected for first time 
                After application start 
                @param[in]  playListInString        this is the string holding XMl data for playList */
            void updatePlayListFromServer(const String & playListInString);
            /** Delete from current playlist from the server
                @param[in]  indexList        this is the array of index deleted from server */
            void deleteInPlayListFromServer(const Array<int> & indexList);
			/** Add into current playlist from the serverPlayList 
                @param[in]  playListInString        this is the string holding XMl data for playList */
            void addInPlayListFromServer(const String & playListInString);
            /** Allow or DisAllow modifications in playList 
                @param[in]    allow     If true allow / if false disAllow*/
            void allowPlayListModification(bool allow);

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