/*                                                                                  
*=====================================================================================
*ScPlayer - Server Client Player                                                                   |
*Music file player that works in Network                                             |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com															 |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
*                                                                                    |
*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
* ScPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the ScPlayer distribution, or can be found     |
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
    class PlayListComponent;
    /** This is main Player component which makes actual play/pause and vivid operation on songs */
    class PlayerComponent : public drow::AudioFileDropTarget,
                            public drow::AudioFilePlayer::Listener,
                            public Thread,
                            public Slider::Listener,
                            public MouseListener,
                            public Timer
                        
    {
        // Type definitions
        
        // Members
    private:
        /** Image button for play/pause */
        ScopedPointer<ImageButton>          playPauseImageButton;        
        /** Image button for stop */
        ScopedPointer<ImageButton>          stopImageButton;
        /** Image button for next */
        ScopedPointer<ImageButton>          nextImageButton;
        /** Image button for previous */
        ScopedPointer<ImageButton>          backImageButton;
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
        virtual void paintOverChildren (Graphics & g);

        // AudioFileDropTarget interface
 	    /** Callback to indicate that the user has dropped the files onto this component */
        virtual void filesDropped (const StringArray &files, int x, int y);

        // AudioFilePlayer::Listener interface
        /** Called when the player's file is changed. */
        virtual void fileChanged (drow::AudioFilePlayer * player);
        /** Called when the the player is stopped or started. */
 	    virtual void playerStoppedOrStarted (drow::AudioFilePlayer * player);

        // Thread interface
        /** Must be implemented to perform the thread's actual code */
 	    virtual void run ();

        // Slider::Listener interface
        /** Called when the slider's value is changed */
        virtual void sliderValueChanged (Slider *slider);
     	/** Called after a drag operation has finished */
        virtual void sliderDragEnded (Slider *slider);
 	
 	    // MouseListener interface
        /** Called when a mouse button is pressed */
        virtual void mouseDown (const MouseEvent & e);
 	    /** Called when a mouse button is released */
        virtual void mouseUp (const MouseEvent & e);
 	 	
        // Timer interface
        /** The user-defined callback routine that actually gets called periodically */
        virtual void timerCallback ();

        // Class methods
        /** Set the current song values 
            @param  songPath        The path for the current song
            return  true/false      If song is correctly set return true else false */
        bool setCurrentSong(String songPath);
        /** Play/Pause button clicked */
        void playPauseButtonClicked();
        /** Stop button clicked */
        void stopButtonClicked();
        /** Next button clicked */
        void nextButtonClicked();
        /** Back button clicked */
        void backButtonClicked();
        /** To check weather any song is currently playing 
            @param[out] index       if current status is playing of any song then return it's index 
            @return     true/false  If currently any song is playing return true else false(for pause and stop) */
        bool isCurrentlyPlaying(int & index);
 	    
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