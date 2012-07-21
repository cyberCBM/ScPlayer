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

namespace GUI
{
    class PlayListComponent  : public ListBoxModel,
				      public Component,
				      public ButtonListener,
				      public FileDragAndDropTarget
    {
	    //Type Definitions
	    //** Audio structure consists the details of the audio file */
	    struct Audio
	    {
		    String filePath;
		    String fileName;
		    String duration;
	    };

	    typedef juce::Array<Audio> PlayListArray; 

	    private:
		    //Members
		    /** listBox contains the list of Songs */
		    ScopedPointer<ListBox>		listBox;
		    /** Browse button to browse the audio files from the disk */
		    ScopedPointer<ImageButton>	browseButton;
		    /** Save button to save the current playlist */
		    ScopedPointer<ImageButton>	saveButton;
		    /**A File Array contains the files present in the PlayList */
		    PlayListArray				listOfFiles;

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
		    /** Get the Number of Rows in a ListBox */
		    virtual int getNumRows();
		    /** Paints the ListBox at regular interval */
		    virtual void paintListBoxItem (int rowNumber, Graphics & g, int width, int height, bool rowIsSelected);
		    ///** Drag and Drop feature in the ListBox */
		    //var getDragSourceDescription(const SparseSet<int>& selectedRows);
		    /** Delete a song from the PlayList */
		    void deleteKeyPressed (int rowSelected);

		    //FileDragAndDropTarget interface
		    /**	Callback to check whether this target is interested in the set of files being offered */
		    virtual bool isInterestedInFileDrag (const StringArray & files);
		    /** Callback to indicate that the user has dropped the files onto this component */
		    virtual void filesDropped (const StringArray & files, int x, int y);
		    //Class Methods
	    public:
		    // Constructor & Destructor
	    public:
		    /** Constructor */
		    PlayListComponent ();
		    /** Destructor */
		    ~PlayListComponent();

        //==============================================================================
        // (prevent copy constructor and operator= being generated..)
        PlayListComponent (const PlayListComponent&);
        const PlayListComponent& operator= (const PlayListComponent&);
};
}
#endif   // hpp_PlayList_hpp