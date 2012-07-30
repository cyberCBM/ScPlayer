//We need our Basic class definitions
#include "PlayerComponent.hpp"
// We need the main component
#include "../MainComponent.hpp"

GUI::PlayerComponent::PlayerComponent (drow::AudioFilePlayerExt & _audioFilePlayer): 
isPlaying(false), playPauseImageButton(nullptr), stopImageButton(nullptr), 
    nextImageButton(nullptr), backImageButton(nullptr), seekSlider(nullptr), currentPosition(0),
    audioFilePlayer(_audioFilePlayer), drow::AudioFileDropTarget(&_audioFilePlayer), 
    Thread("Duration Thread"), playListComponent(nullptr)
{
    Image tempImg;

    tempImg = ImageCache::getFromMemory (BinaryData::play_gif, BinaryData::play_gifSize);
    addAndMakeVisible (playPauseImageButton = new ImageButton("play/pause"));
    playPauseImageButton->setButtonText (String::empty);
    playPauseImageButton->setToggleState(false, false);
    playPauseImageButton->setTooltip("Play/pause song");
    playPauseImageButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         ImageCache::getFromMemory (BinaryData::pause_gif, BinaryData::pause_gifSize), 1.0000f, Colours::transparentBlack);    
    playPauseImageButton->addButtonListener (this);

    tempImg = ImageCache::getFromMemory (BinaryData::stop_gif, BinaryData::stop_gifSize);
    addAndMakeVisible (stopImageButton = new ImageButton("stop"));
    stopImageButton->setButtonText (String::empty);
    stopImageButton->setTooltip("Stop song");
    stopImageButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 1.0000f, Colours::transparentBlack);
    stopImageButton->addButtonListener (this);

    tempImg = ImageCache::getFromMemory (BinaryData::next_gif, BinaryData::next_gifSize);
    addAndMakeVisible (nextImageButton = new ImageButton("next"));
    nextImageButton->setButtonText (String::empty);
    nextImageButton->setTooltip("Next song");
    nextImageButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 1.0000f, Colours::transparentBlack);
    nextImageButton->addButtonListener (this);

    tempImg = ImageCache::getFromMemory (BinaryData::back_gif, BinaryData::back_gifSize);
    addAndMakeVisible (backImageButton = new ImageButton("back"));
    backImageButton->setButtonText (String::empty);
    backImageButton->setTooltip("Previous song");
    backImageButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 1.0000f, Colours::transparentBlack);
    backImageButton->addButtonListener (this);

    addAndMakeVisible(seekSlider = new Slider(Slider::SliderStyle::LinearBar, Slider::TextEntryBoxPosition::NoTextBox));
    seekSlider->setTooltip("Seek bar");
    seekSlider->setRange(0.0, 1.0, 1.0);
    seekSlider->setEnabled(true);
    seekSlider->setTextBoxIsEditable(false);
    seekSlider->setColour(Slider::ColourIds::thumbColourId, Colours::grey);
    seekSlider->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::white);
    seekSlider->setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    seekSlider->addListener(this);

    audioFilePlayer.addListener(this);    
}
GUI::PlayerComponent::~PlayerComponent ()
{
    audioFilePlayer.removeListener(this);
    playPauseImageButton->removeButtonListener(this);
    stopImageButton->removeButtonListener(this);
    nextImageButton->removeButtonListener(this);
    backImageButton->removeButtonListener(this);
    seekSlider->removeListener(this);
    stopThread(1000);
}
void GUI::PlayerComponent::resized ()
{
    if(!playListComponent)
        playListComponent = dynamic_cast<PlayListComponent*>(findParentComponentOfClass<MainComponent>()->getRightPanel()->getPlayListComponent());

    int yPosition = proportionOfHeight(0.800f);

    seekSlider->setBounds(proportionOfWidth(0.025f), yPosition - backImageButton->getHeight()/2, getWidth() - proportionOfWidth(0.050f), backImageButton->getHeight()/2);
    backImageButton->setBounds((getWidth()/2) - (backImageButton->getWidth() * 2), yPosition, backImageButton->getWidth(), backImageButton->getHeight());
    playPauseImageButton->setBounds(backImageButton->getRight(), yPosition, playPauseImageButton->getWidth(), playPauseImageButton->getHeight());
    stopImageButton->setBounds(playPauseImageButton->getRight(), yPosition, stopImageButton->getWidth(), stopImageButton->getHeight());
    nextImageButton->setBounds(stopImageButton->getRight(), yPosition, nextImageButton->getWidth(), nextImageButton->getHeight());
}
void GUI::PlayerComponent::paint (Graphics & g)
{    
    // backGround Filling
    g.fillAll (Colour (0xff292929));
    g.setColour (Colours::black);
    g.drawRect (1.0f, 1.0f, (float)getWidth() - 2.0f, (float)getHeight() - 2.0f, 1.0f);

    if(isPlaying)
    {
        g.setColour(Colours::grey);
        Font f(Font ((float)proportionOfHeight(0.070f), Font::plain));
        g.setFont(f);
        g.drawText("Song: ", (int)proportionOfWidth(0.050f), (int)proportionOfHeight(0.100f), (int)proportionOfWidth(0.250f), (int)f.getHeight(), Justification::left, false);
        g.drawText(currentSong.filePath, (int)proportionOfWidth(0.250f), (int)proportionOfHeight(0.100f), getWidth() - (int)proportionOfWidth(0.250f), (int)f.getHeight(), Justification::left, true);
    }
}

void GUI::PlayerComponent::paintOverChildren (Graphics &g)
{   
    if(isPlaying)
    {
        g.setColour(Colours::white);
        Font f(Font (proportionOfHeight(0.050f), Font::plain));
        int hours = (int)currentPosition/3600;
        int mins = ((int)currentPosition - (hours * 3600))/60;
        int secs = ((int)currentPosition - (hours * 3600) - (mins * 60));
        String duration = ((hours > 9 ? (String)hours : "0"+ (String)hours) + ":" +
                                (mins > 9 ? (String)mins : "0"+ (String)mins) + ":" +
                                (secs > 9 ? (String)secs : "0"+ (String)secs));
        g.drawText(duration, ((getWidth()/2) - (f.getStringWidth(duration)/2)), seekSlider->getY() + 5, f.getStringWidth(duration) + 5, (int)f.getHeight(), Justification::left, true);
    }
}
void GUI::PlayerComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if(buttonThatWasClicked == playPauseImageButton)
    {   
        playPauseButtonClicked();
    }
    else if(buttonThatWasClicked == stopImageButton)
    {
        signalThreadShouldExit();
        stopButtonClicked();
    }
    else if(buttonThatWasClicked == nextImageButton)
    {
        nextButtonClicked();
    }
    else if(buttonThatWasClicked == backImageButton)
    {
        backButtonClicked();
    }
}

void GUI::PlayerComponent::filesDropped (const StringArray &files, int x, int y)
{
    playListComponent->dropToPlayList(files, this);
    signalThreadShouldExit();
    stopButtonClicked();
    playPauseButtonClicked();
}

void GUI::PlayerComponent::fileChanged (drow::AudioFilePlayer * player)
{
    if(player == &audioFilePlayer)
    {
        int i = 0;
    }
}

void GUI::PlayerComponent::playerStoppedOrStarted (drow::AudioFilePlayer * player)
{
    if(player == &audioFilePlayer)
    {
        if(!audioFilePlayer.isPlaying() && !audioFilePlayer.isCurrentlyPaused())
        {
            if(audioFilePlayer.hasStreamFinished())
            {
                currentPosition = 0;
                seekSlider->setValue(currentPosition);
                setCurrentSong(playListComponent->getSongPathAtPlayingIndex(1));
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

        if((!audioFilePlayer.isCurrentlyPaused()) && (currentPosition < currentSong.duration))
        {
            currentPosition++;
            seekSlider->setValue(currentPosition);
            
            repaint();
        }        
    }
}

void GUI::PlayerComponent::sliderValueChanged (Slider * slider)
{
    if(slider == seekSlider)
    {
    }
}

void GUI::PlayerComponent::sliderDragEnded (Slider * slider)
{
    if(slider == seekSlider)
    {
        audioFilePlayer.setPosition(currentPosition = seekSlider->getValue());
    }
        
}

void GUI::PlayerComponent::setCurrentSong(String songPath)
{
    audioFilePlayer.setFile(songPath);

    currentSong.filePath = audioFilePlayer.getFile().getFileNameWithoutExtension();
    currentSong.duration = audioFilePlayer.getLengthInSeconds();

    seekSlider->setRange(0.0, currentSong.duration - 1, 1.0);
}

void GUI::PlayerComponent::playPauseButtonClicked()
{
    if(!playPauseImageButton->getToggleState())
    {
        if(!audioFilePlayer.isCurrentlyPaused())
            setCurrentSong(playListComponent->getSongPathAtPlayingIndex());

        audioFilePlayer.start();
        if(!isThreadRunning())
            startThread();
    }
    else
        audioFilePlayer.pause();
        
    isPlaying = true;
    playPauseImageButton->setToggleState(!playPauseImageButton->getToggleState(), false);
    repaint();
}

void GUI::PlayerComponent::stopButtonClicked()
{
    if(isThreadRunning() && threadShouldExit())
    {
        stopThread(1000);
        audioFilePlayer.stop();
        isPlaying = false;
        playPauseImageButton->setToggleState(false, false);
        currentPosition = 0;
        seekSlider->setValue(currentPosition);
        repaint();
    }
}

void GUI::PlayerComponent::nextButtonClicked()
{
    bool isPaused = audioFilePlayer.isPlaying();
    signalThreadShouldExit();
    stopButtonClicked();
    setCurrentSong(playListComponent->getSongPathAtPlayingIndex(1));
    
    if(isPaused)
        playPauseButtonClicked();
    else
    {
        isPlaying = true;
        repaint();
    }    
}

void GUI::PlayerComponent::backButtonClicked()
{
    bool isPaused = audioFilePlayer.isPlaying();
    signalThreadShouldExit();
    stopButtonClicked();
    setCurrentSong(playListComponent->getSongPathAtPlayingIndex(-1));

    if(isPaused)
        playPauseButtonClicked();
    else
    {
        isPlaying = true;
        repaint();
    } 
}
