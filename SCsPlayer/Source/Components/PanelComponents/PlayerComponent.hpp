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

#ifndef hpp_PlayerComponent_hpp
#define hpp_PlayerComponent_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// We need the playlist component
#include "PlayListComponent.hpp"

namespace GUI 
{
    class PlayerComponent : public drow::AudioFileDropTarget,
                            public ButtonListener,
                            public drow::AudioFilePlayer::Listener,
                            public Thread,
                            public Slider::Listener
                        
    {
        // Type definitions
        
        // Members
    private:
        /** Boolean to initialise the class only once in resized method */
        bool                                firstCall;
        /** Boolean to check if when song playing or not */
        bool                                isPlaying;
        /** Image button for play/pause */
        ScopedPointer<ImageButton>          playPauseButton;        
        /** Image button for stop */
        ScopedPointer<ImageButton>          stopButton;
        /** Image button for next */
        ScopedPointer<ImageButton>          nextButton;
        /** Image button for previous */
        ScopedPointer<ImageButton>          backButton;
        /** The song being currently operated */
        Configurations::Media               currentSong;
        /** The audio file player from drow that shall handle all the inputs over the file */
        drow::AudioFilePlayerExt &          audioFilePlayer;
        /** The slider for seeking the song */
        ScopedPointer<Slider>               seekSlider;
        /** The current position of the song in seconds */
        double                              currentPosition;
        /** The playlist component */
        PlayListComponent *                 playListComponent;

        // Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);
        /** Components can override this method to draw over the top of their children */
        virtual void paintOverChildren (Graphics &g);
 	

        // ButtonListner interface
        /** This method is called when any button is clicked */
        void buttonClicked (Button* buttonThatWasClicked);

        // AudioFileDropTarget interface
 	    /** Callback to indicate that the user has dropped the files onto this component */
        virtual void filesDropped (const StringArray &files, int x, int y);

        // AudioFilePlayer::Listener interface
        /** Called when the player's file is changed. */
        virtual void fileChanged (drow::AudioFilePlayer * player);
        /** Called when the the player is stopped or started. */
 	    virtual void playerStoppedOrStarted (drow::AudioFilePlayer * player);

        // Timer interface
        /** Must be implemented to perform the thread's actual code */
 	    virtual void run ();

        // Slider::Listener interface
        /** Called when the slider's value is changed */
        virtual void sliderValueChanged (Slider *slider);
     	/** Called after a drag operation has finished */
        virtual void sliderDragEnded (Slider *slider);
 	
 	
 	    
        // Constructor & Destructor
    public:
        /** Constructor 
            @param audioFilePlayer      The audio file player that shall control the audio file */
        PlayerComponent (drow::AudioFilePlayerExt & audioFilePlayer);
        /** Destructor */
        ~PlayerComponent ();

    private:
        // (prevent copy constructor and operator= being generated..)
        PlayerComponent (const PlayerComponent&);
        const PlayerComponent& operator= (const PlayerComponent&);

    };
}

#endif  // hpp_PlayerComponent_hpp