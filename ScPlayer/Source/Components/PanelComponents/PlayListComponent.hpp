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

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// Get our structure definitions from here
// Included to get our structure definitions from here
#include "../../Common/Configurations.hpp"
// Included to get the Look and Feel Component
#include "../../Common/CsLookAndFeel.hpp"

namespace GUI
{
    // Class Forwarding
    class PlayerComponent;
    class ControlBarComponent;
    /** PlayListComponent class contains the playlist and the features of the playlist. Also communication with the player
    component is been implemented here.
    PlayListComponent class inherits ListBoxModel, Component, ButtonListener and FileDragAndDropTarget classes */
    class PlayListComponent  : public ListBoxModel,
        public Component,
        public ButtonListener,
        public FileDragAndDropTarget
    {
    private:
        //Members
        /** The index for the playing song */
        int                                     playingSongIndex;
        /** playListBox contains the list of Songs */
        ScopedPointer<ListBox>					playListBox;
        /** Browse button to browse the audio files from the disk */
        ScopedPointer<ImageButton>				browseImageButton;
        /** Save button to save the current playlist */
        ScopedPointer<ImageButton>				saveImageButton;
        /** A File Array contains the files present in the PlayList */
        Array<Configurations::Media>			mediaArray;
        /** Contains the audio formats supported by the Player */
        AudioFormatManager						audioFormatManager;
        /** Used to write/get data to/from xml file */
        ScopedPointer<XmlElement>				mainElement;
        /** The CsLookAndFeel object for showing customized scrollbar */
        CsLookAndFeel                           csLnF;
        /** The Player Component */
        PlayerComponent *						playerComponent;
        /** audioSourceReader that gives emdia file's duration */
        ScopedPointer<AudioFormatReaderSource>  audioSourceReader;
        /** audioFormatReader that gives total format and help audioSourceReader */
        ScopedPointer<AudioFormatReader>        audioFormatReader;

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
        /** Set latest playing index from server 
            @param[in]  index latest index to set as current playing */
        inline int currentPlayingSongIndex(){   return playingSongIndex;    }
        /** Return ControlBarComponent which is used to send  */
        GUI::ControlBarComponent * getControlBarComponent();
        /** Get the song path at the playing index
            @param [in] index			(index = 0 i.e playing song, index = -1 i.e previous song, index = 1 i.e next song) 
            @return String 				returns the path of the currently playing audio file at index */
        String getSongPathAtPlayingIndex(int index = 0);
        /** Get current playList from mediaArray in String
            @return     playList    playlist as per in mediaArray as XmlElement*/
        String getPlayListFromMediaArray();
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
        /** Drops the dragged songs in the playlist 
            @param [out, in] files		 gives the string array of the paths of the files dropped
            @param [in]             	 sourceComponent the component where the files are dropped */
        void dropToPlayList (const StringArray & filesNamesArray, const Component * sourceComponent);
        /** When song is played/changed by double click or keyboard enter */
        void songPlayedByClick(const int index);
        /** Delete from current playlist from the server
            @param[in]  indexList        this is the array of index deleted from server */
        void deleteInPlayListFromClient(const Array<int> & indexList);
        /** Add into current playlist from the serverPlayList 
            @param[in]  playListInString        this is the string holding XMl data for playList */
        void addInPlayListFromClient(const String & playListInString);

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