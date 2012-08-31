/*                                                                                  
*=====================================================================================
*ScPlayer - Server Client Player                                                     |
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

//We need our Basic class definitions
#include "PlayerComponent.hpp"
// We need the main component
#include "../MainComponent.hpp"

GUI::PlayerComponent::PlayerComponent (AudioDeviceManager & audioDeviceManager, drow::AudioFilePlayerExt & audioFilePlayer): 
    playPauseImageButton(nullptr), stopImageButton(nullptr), gainSlider(nullptr),
    nextImageButton(nullptr), backImageButton(nullptr), seekSlider(nullptr), currentPosition(0),
    audioFilePlayer(audioFilePlayer), drow::AudioFileDropTarget(&audioFilePlayer), isPaused(false), 
    Thread("Duration Thread"), playListComponent(nullptr), cpuMeter (&audioDeviceManager), meterThread("Meter Thread")
{
    addAndMakeVisible (&meterL);
    addAndMakeVisible (&meterR);
    addAndMakeVisible (&cpuMeter);

    meterThread.addTimeSliceClient (&meterL);
    meterThread.addTimeSliceClient (&meterR);
    meterThread.startThread (1);

    cpuMeter.setTextColour (Colours::red);
    cpuMeter.setJustificationType (Justification::centred);
    cpuMeter.setBorderSize (0, 0);

    Image tempImg;

    tempImg = ImageCache::getFromMemory (BinaryData::play_gif, BinaryData::play_gifSize);
    addAndMakeVisible (playPauseImageButton = new ImageButton("play/pause"));
    playPauseImageButton->setToggleState(false, false);
    playPauseImageButton->setTooltip("Play/pause");
    playPauseImageButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         ImageCache::getFromMemory (BinaryData::pause_gif, BinaryData::pause_gifSize), 1.0000f, Colours::transparentBlack);    
    // This button will work over mouse events and not the button events to play/pause
    playPauseImageButton->addMouseListener (this, false);

    tempImg = ImageCache::getFromMemory (BinaryData::stop_gif, BinaryData::stop_gifSize);
    addAndMakeVisible (stopImageButton = new ImageButton("stop"));
    stopImageButton->setTooltip("Stop");
    stopImageButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 1.0000f, Colours::transparentBlack);
    // This button will work over mouse events and not the button events to stop
    stopImageButton->addMouseListener (this, false);

    tempImg = ImageCache::getFromMemory (BinaryData::next_gif, BinaryData::next_gifSize);
    addAndMakeVisible (nextImageButton = new ImageButton("next"));
    nextImageButton->setTooltip("Next");
    nextImageButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 1.0000f, Colours::transparentBlack);
    // This button will work over mouse events and not the button events to forward
    nextImageButton->addMouseListener (this, false);

    tempImg = ImageCache::getFromMemory (BinaryData::back_gif, BinaryData::back_gifSize);
    addAndMakeVisible (backImageButton = new ImageButton("back"));
    backImageButton->setButtonText (String::empty);
    backImageButton->setTooltip("Previous");
    backImageButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 1.0000f, Colours::transparentBlack);
    // This button will work over mouse events and not the button events to rewind
    backImageButton->addMouseListener (this, false);

	tempImg = ImageCache::getFromMemory (BinaryData::shuffle_gif, BinaryData::shuffle_gifSize);
	addAndMakeVisible (shuffleImageButton = new ImageButton("shuffle"));
    shuffleImageButton->setButtonText (String::empty);
    shuffleImageButton->setTooltip("Shuffle");
    shuffleImageButton->setImages (false, true, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 0.4000f, Colours::transparentBlack);
    // This button will work over mouse events and not the button events to shuffle
    shuffleImageButton->addMouseListener (this, false);

	tempImg = ImageCache::getFromMemory (BinaryData::repeat_gif, BinaryData::save_gifSize);
	addAndMakeVisible (repeatImageButton = new ImageButton("repeat"));
    repeatImageButton->setButtonText (String::empty);
    repeatImageButton->setTooltip("Repeat");
    repeatImageButton->setImages (false, true, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 0.4000f, Colours::transparentBlack);
    // This button will work over mouse events and not the button events to shuffle
    repeatImageButton->addMouseListener (this, false);

    addAndMakeVisible(seekSlider = new Slider(Slider::LinearBar, Slider::NoTextBox));
    seekSlider->setTooltip("Seek bar");
    seekSlider->setRange(0.0, 1.0, 1.0);
    seekSlider->setEnabled(true);
    seekSlider->setTextBoxIsEditable(false);
    seekSlider->setColour(Slider::thumbColourId, Colours::grey);
    seekSlider->setColour(Slider::textBoxOutlineColourId, Colours::white);
    seekSlider->setColour(Slider::textBoxTextColourId, Colours::black);
    seekSlider->addListener(this);
    
    addAndMakeVisible(gainSlider = new Slider(Slider::LinearHorizontal, Slider::NoTextBox));
    gainSlider->setTooltip("Set Volume");
    gainSlider->setRange(0.0, 1.0, 0.1);
    gainSlider->setValue(0.5, false, false);
    gainSlider->setEnabled(true);
    gainSlider->setColour(Slider::thumbColourId, Colours::aquamarine);
    gainSlider->setColour(Slider::textBoxOutlineColourId, Colours::white);
    gainSlider->setColour(Slider::textBoxTextColourId, Colours::black);
    gainSlider->addListener(this);
    
	audioFilePlayer.getAudioTransportSource()->setGain (0.5);
    // Enhance the equalizer by decreasing the default low filter and optimize sound quality
    audioFilePlayer.setFilterGain (drow::FilteringAudioSource::Low, (float) 0.900f);
    audioFilePlayer.addListener(this);    
}
GUI::PlayerComponent::~PlayerComponent ()
{
    audioFilePlayer.removeListener(this);
    playPauseImageButton->removeMouseListener(this);
    stopImageButton->removeMouseListener(this);
    nextImageButton->removeMouseListener(this);
    backImageButton->removeMouseListener(this);
	shuffleImageButton->removeMouseListener(this);
	repeatImageButton->removeMouseListener(this);
	seekSlider->removeListener(this);
    gainSlider->removeListener(this);
    stopThread(1000);
    meterThread.stopThread (500);
}
void GUI::PlayerComponent::resized ()
{
    if(!playListComponent)
    {
        playListComponent = dynamic_cast<PlayListComponent*>(findParentComponentOfClass<MainComponent>()->getRightPanel()->getPlayListComponent());
        setCurrentSong(playListComponent->getSongPathAtPlayingIndex(repeatImageButton->getToggleState(), shuffleImageButton->getToggleState()));
        playListComponent->getControlBarComponent()->sendPlayingIndexToAllClients(playListComponent->currentPlayingSongIndex());
    }
    int yPosition = proportionOfHeight(0.800f);
    seekSlider->setBounds(proportionOfWidth(0.025f), yPosition - backImageButton->getHeight()/2, getWidth() - proportionOfWidth(0.050f), backImageButton->getHeight()/2);
    
	shuffleImageButton->setBounds((getWidth()/2) - (backImageButton->getWidth() * 2) - (backImageButton->getWidth()/2) , yPosition + backImageButton->getHeight()/4, 28, 28);
    backImageButton->setBounds(shuffleImageButton->getRight(), yPosition, backImageButton->getWidth(), backImageButton->getHeight());
	playPauseImageButton->setBounds(backImageButton->getRight(), yPosition, playPauseImageButton->getWidth(), playPauseImageButton->getHeight());
    stopImageButton->setBounds(playPauseImageButton->getRight(), yPosition, stopImageButton->getWidth(), stopImageButton->getHeight());
    nextImageButton->setBounds(stopImageButton->getRight(), yPosition, nextImageButton->getWidth(), nextImageButton->getHeight());
    repeatImageButton->setBounds(nextImageButton->getRight(), yPosition + nextImageButton->getHeight()/4, 28, 28);
    
    meterL.setBounds(getWidth()/2 - 20, proportionOfHeight(0.270f) , 20, (yPosition - backImageButton->getHeight()/2 - proportionOfHeight(0.170f))/2);
    meterR.setBounds(getWidth()/2 + 20, proportionOfHeight(0.270f) , 20, (yPosition - backImageButton->getHeight()/2 - proportionOfHeight(0.170f))/2);
    gainSlider->setBounds(getWidth()/2 - 25, meterL.getBottom() + 10, 75, 25);
    cpuMeter.setBounds(getWidth()/2 - 10, meterR.getHeight()/2, 40, 40);
}
void GUI::PlayerComponent::paint (Graphics & g)
{    
    // backGround Filling
    g.fillAll (Colour (0xff292929));
    g.setColour (Colours::black);
    g.drawRect(2, 2, getWidth()- 4, getHeight() - 4, 1);

    // Check if there is currently set song
    if(currentSong.duration > 0)
    {
        g.setColour(Colours::white);
        Font f(Font ((float)proportionOfHeight(0.060f), Font::plain));
        g.setFont(f);
        g.drawText("Song: ", proportionOfWidth(0.050f), proportionOfHeight(0.100f), proportionOfWidth(0.250f), (int)f.getHeight(), Justification::left, false);
        g.drawText(currentSong.filePath, proportionOfWidth(0.250f), proportionOfHeight(0.100f), getWidth() - proportionOfWidth(0.250f), (int)f.getHeight(), Justification::left, true);
    }
}

void GUI::PlayerComponent::paintOverChildren (Graphics &g)
{   
    // Check if there is currently set song
    if(currentSong.duration > 0)
    {
        g.setColour(Colours::white);
        Font f(Font ((float)proportionOfHeight(0.050f), Font::plain));
        int hours = (int)currentPosition/3600;
        int mins = ((int)currentPosition - (hours * 3600))/60;
        int secs = ((int)currentPosition - (hours * 3600) - (mins * 60));
        String duration = ((hours > 9 ? (String)hours : "0"+ (String)hours) + ":" +
                                (mins > 9 ? (String)mins : "0"+ (String)mins) + ":" +
                                (secs > 9 ? (String)secs : "0"+ (String)secs));
        g.drawText(duration, ((getWidth()/2) - (f.getStringWidth(duration)/2)), seekSlider->getY() + 5, f.getStringWidth(duration) + 5, (int)f.getHeight(), Justification::left, true);
    }
}


void GUI::PlayerComponent::filesDropped (const StringArray & filesNamesArray, int /*x*/, int /*y*/)
{
    playListComponent->dropToPlayList(filesNamesArray, this);
    signalThreadShouldExit();
    stopButtonClicked();
    playPauseButtonClicked();
}

void GUI::PlayerComponent::fileChanged (drow::AudioFilePlayer * /*player*/)
{
    /*if(player == &audioFilePlayer)
    {
    }*/
}

void GUI::PlayerComponent::playerStoppedOrStarted (drow::AudioFilePlayer * player)
{
    if(player == &audioFilePlayer)
    {
        // Check when the audio has stopped
        if(!audioFilePlayer.isPlaying() && !isPaused)
        {
            // Check if the audio song has completed its entire play duration
            if(audioFilePlayer.hasStreamFinished())
            {
                seekSlider->setValue(currentPosition = 0);
                playPauseImageButton->setToggleState(false, false);
                // Get the next track
				if(!setCurrentSong(playListComponent->getSongPathAtPlayingIndex(repeatImageButton->getToggleState(), shuffleImageButton->getToggleState(), 1)))
                    return;                
                playPauseButtonClicked();
            }
        }
    }
}

void GUI::PlayerComponent::run()
{
    while (!threadShouldExit())
    {      
        wait(1000);
        const MessageManagerLock mml (Thread::getCurrentThread());
        if (! mml.lockWasGained())  // if something is trying to kill this job, the lock
            return;        

        if((!isPaused) && (currentPosition <= currentSong.duration - 1))
        {
            currentPosition++;
            seekSlider->setValue(currentPosition);
            
            repaint();
        }        
    }
}

void GUI::PlayerComponent::sliderValueChanged (Slider * slider)
{
    if(slider == gainSlider)
    {
        audioFilePlayer.getAudioTransportSource()->setGain(gainSlider->getValue());
    }
    else if(slider == seekSlider)
    {
        // If any change for seekSlider
    }

}

void GUI::PlayerComponent::sliderDragEnded (Slider * slider)
{
    if(slider == seekSlider)
    {
        audioFilePlayer.setPosition(currentPosition = seekSlider->getValue());
    }
    else if(slider = gainSlider)
    {
        //audioFilePlayer.getAudioTransportSource()->setGain(gainSlider->getValue());
    }
}

bool GUI::PlayerComponent::setCurrentSong(String songPath)
{   
    // If is playing or paused then reject request for file change
    if(audioFilePlayer.isPlaying() || isPaused)
        return false;

    audioFilePlayer.setFile(songPath);    

    // Set the file attributes into our component; if file is non existent then empty values are set
    if(songPath == String::empty)
    {
        currentSong.filePath = String::empty;
        currentSong.duration = 0;    

        seekSlider->setRange(0.0, 1.0, 1.0);
        return false;
    }
    else
    {
        // If file is bad then set the next song
        if(!audioFilePlayer.getFile().existsAsFile())
        {
            //@todo report bad file to playlist
            setCurrentSong(playListComponent->getSongPathAtPlayingIndex(repeatImageButton->getToggleState(), shuffleImageButton->getToggleState(), 1));
            playListComponent->getControlBarComponent()->sendPlayingIndexToAllClients(playListComponent->currentPlayingSongIndex());
        }

        currentSong.filePath = audioFilePlayer.getFile().getFileNameWithoutExtension();
        currentSong.duration = audioFilePlayer.getLengthInSeconds();    

        seekSlider->setRange(0.0, currentSong.duration - 1, 1.0);
        return true;
    }
    return true;   
}

void GUI::PlayerComponent::mouseDown (const MouseEvent & e)
{
    if((e.mods.isLeftButtonDown()) && (!isTimerRunning()))
    {
        // Forward/Rewind when nextButton/backButton is pressed for more than 500 milliseconds
        if((nextImageButton == e.eventComponent) || (backImageButton == e.eventComponent))
            if(currentSong.filePath != String::empty)
                startTimer(500);
    }
}

void GUI::PlayerComponent::mouseUp (const MouseEvent & e)
{
    if((e.mods.isLeftButtonDown()) && (isTimerRunning()))
    {
        // nextButton released
        if(nextImageButton == e.eventComponent)
        {        
            stopTimer();
            // Check whether we need to jump over the next track or simply stop forwarding
            if(e.getLengthOfMousePress() < 500)
                nextButtonClicked();
        }
        // backButton released
        else if(backImageButton == e.eventComponent)
        {        
            stopTimer();
            // Check whether we need to jump over the previous track or simply stop rewinding
            if(e.getLengthOfMousePress() < 500)
                backButtonClicked();
        }
    }
    else if(e.mods.isLeftButtonDown())
    {
        // playPauseButton released
        if(playPauseImageButton == e.eventComponent)
        {   
            playPauseButtonClicked();
        }
        // stopButton released
        else if(stopImageButton == e.eventComponent)
        {
            signalThreadShouldExit();
            stopButtonClicked();
            playListComponent->getControlBarComponent()->sendStopToAllClients();
        }
		// shuffleButton released
		else if (shuffleImageButton == e.eventComponent)
		{
			if(shuffleImageButton->getToggleState())
				shuffleImageButton->setToggleState (false, true);
			else
				shuffleImageButton->setToggleState (true, true);
		}
		else if (repeatImageButton == e.eventComponent)
		{
			if(repeatImageButton->getToggleState())
				repeatImageButton->setToggleState (false, true);
			else
				repeatImageButton->setToggleState (true, true);
		}
    }
}

void GUI::PlayerComponent::timerCallback ()
{   
    // Increase the timer interval to avoid excess position shift 
    startTimer(1000);
    if(nextImageButton->isMouseButtonDown())
    {   
        if(currentPosition > currentSong.duration - 20)
        {
            stopTimer();
            nextButtonClicked();
        }
            
        // Forward the play by twenty seconds
        audioFilePlayer.setPosition(currentPosition += 20);
    }
    else if(backImageButton->isMouseButtonDown())
    {
        if(currentPosition < 20)
        {
            stopTimer();
            backButtonClicked();
        }
        // Rewind the play by twenty seconds
        audioFilePlayer.setPosition(currentPosition -= 20);
    }
}

void GUI::PlayerComponent::playPauseButtonClicked()
{
    if(!playPauseImageButton->getToggleState())
    {
        // Check if the player is paused then simply play
        if(!isPaused)
        {
            if(!setCurrentSong(playListComponent->getSongPathAtPlayingIndex(false, false)))
                return;
            playListComponent->getControlBarComponent()->sendPlayingIndexToAllClients(playListComponent->currentPlayingSongIndex());
        }
            
        audioFilePlayer.start();
        isPaused = false;
        if(!isThreadRunning())
            startThread();
        playPauseImageButton->setToggleState(true, false);
        playListComponent->getControlBarComponent()->sendPlayToAllClient();
    }
    else
    {
        if (audioFilePlayer.getAudioTransportSource()->isPlaying())
        {
		    audioFilePlayer.getAudioTransportSource()->stop();
            isPaused = true;
        }
	    else
        {
		    audioFilePlayer.getAudioTransportSource()->start();
            isPaused = false;
        }
        playPauseImageButton->setToggleState(false, false);
        playListComponent->getControlBarComponent()->sendPauseToAllClients();
    }
    repaint();
}

void GUI::PlayerComponent::stopButtonClicked()
{
    if(isThreadRunning() && threadShouldExit())
    {
        stopThread(1000);
        audioFilePlayer.stop();
        isPaused = false;
        playPauseImageButton->setToggleState(false, false);
        currentPosition = 0;
        seekSlider->setValue(currentPosition);
        repaint();
    }
}

void GUI::PlayerComponent::nextButtonClicked()
{
    // Check if file is playing or paused/stopped before stopping
    bool isPlaying = audioFilePlayer.isPlaying();
    signalThreadShouldExit();
    stopButtonClicked();
    if(!setCurrentSong(playListComponent->getSongPathAtPlayingIndex(repeatImageButton->getToggleState(), shuffleImageButton->getToggleState(), 1)))
        return;
    playListComponent->getControlBarComponent()->sendPlayingIndexToAllClients(playListComponent->currentPlayingSongIndex());
    if(isPlaying)
        playPauseButtonClicked();
    else
        repaint();
}

void GUI::PlayerComponent::backButtonClicked()
{
    // Check if file is playing or paused/stopped before stopping
    bool isPlaying = audioFilePlayer.isPlaying();
    signalThreadShouldExit();
    stopButtonClicked();
    if(!setCurrentSong(playListComponent->getSongPathAtPlayingIndex(repeatImageButton->getToggleState(), shuffleImageButton->getToggleState(), -1)))
        return;
    playListComponent->getControlBarComponent()->sendPlayingIndexToAllClients(playListComponent->currentPlayingSongIndex());
    if(isPlaying)
        playPauseButtonClicked();
    else
        repaint();
}

bool GUI::PlayerComponent::isCurrentlyPlaying(int & index)
{   
    index = playListComponent->currentPlayingSongIndex();
    return audioFilePlayer.isPlaying(); 
}
