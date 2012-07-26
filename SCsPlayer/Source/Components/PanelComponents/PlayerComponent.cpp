//We need our Basic class definitions
#include "PlayerComponent.hpp"
// We need the main component
#include "../MainComponent.hpp"

GUI::PlayerComponent::PlayerComponent (drow::AudioFilePlayerExt & _audioFilePlayer): firstCall(true), isPlaying(false), playPauseButton(nullptr), stopButton(nullptr), nextButton(nullptr), backButton(nullptr), seekSlider(nullptr), currentPosition(0),
    audioFilePlayer(_audioFilePlayer), drow::AudioFileDropTarget(&_audioFilePlayer), Thread("Duration Thread"), playListComponent(0)
{
    Image tempImg;

    tempImg = ImageCache::getFromMemory (BinaryData::play_gif, BinaryData::play_gifSize);
    addAndMakeVisible (playPauseButton = new ImageButton("play/pause"));
    playPauseButton->setButtonText (String::empty);
    playPauseButton->setToggleState(false, false);
    playPauseButton->setTooltip("Play/pause song");
    playPauseButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         ImageCache::getFromMemory (BinaryData::pause_gif, BinaryData::pause_gifSize), 1.0000f, Colours::transparentBlack);    
    playPauseButton->addButtonListener (this);

    tempImg = ImageCache::getFromMemory (BinaryData::stop_gif, BinaryData::stop_gifSize);
    addAndMakeVisible (stopButton = new ImageButton("stop"));
    stopButton->setButtonText (String::empty);
    stopButton->setTooltip("Stop song");
    stopButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 1.0000f, Colours::transparentBlack);
    stopButton->addButtonListener (this);

    tempImg = ImageCache::getFromMemory (BinaryData::next_gif, BinaryData::next_gifSize);
    addAndMakeVisible (nextButton = new ImageButton("next"));
    nextButton->setButtonText (String::empty);
    nextButton->setTooltip("Next song");
    nextButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 1.0000f, Colours::transparentBlack);
    nextButton->addButtonListener (this);

    tempImg = ImageCache::getFromMemory (BinaryData::back_gif, BinaryData::back_gifSize);
    addAndMakeVisible (backButton = new ImageButton("back"));
    backButton->setButtonText (String::empty);
    backButton->setTooltip("Previous song");
    backButton->setImages (true, false, true, tempImg, 1.0000f, Colours::transparentBlack,
         tempImg, 0.7000f, Colours::transparentBlack,
         tempImg, 1.0000f, Colours::transparentBlack);
    backButton->addButtonListener (this);

    addAndMakeVisible(seekSlider = new Slider(Slider::SliderStyle::LinearBar, Slider::TextEntryBoxPosition::NoTextBox));
    seekSlider->setTooltip("Seek bar");
    seekSlider->setRange(0.0, 1.0, 1.0);
    seekSlider->setEnabled(false);
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
    stopThread(100);
}
void GUI::PlayerComponent::resized ()
{
    if(firstCall)
    {
        playListComponent = dynamic_cast<PlayListComponent*>(findParentComponentOfClass<MainComponent>()->getRightPanel()->getPlayListComponent());
        firstCall = false;
    }

    int yPosition = proportionOfHeight(0.800f);

    seekSlider->setBounds(proportionOfWidth(0.025f), yPosition - backButton->getHeight()/2, getWidth() - proportionOfWidth(0.050f), backButton->getHeight()/2);
    backButton->setBounds((getWidth()/2) - (backButton->getWidth() * 2), yPosition, backButton->getWidth(), backButton->getHeight());
    playPauseButton->setBounds(backButton->getRight(), yPosition, playPauseButton->getWidth(), playPauseButton->getHeight());
    stopButton->setBounds(playPauseButton->getRight(), yPosition, stopButton->getWidth(), stopButton->getHeight());
    nextButton->setBounds(stopButton->getRight(), yPosition, nextButton->getWidth(), nextButton->getHeight());
}
void GUI::PlayerComponent::paint (Graphics & g)
{    
    // backGround Filling
    g.fillAll (Colour (0xff292929));

    if(isPlaying)
    {
        g.setColour(Colours::white);
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
    if(buttonThatWasClicked == playPauseButton)
    {   
        if(!playPauseButton->getToggleState())
        {
            audioFilePlayer.start();
            if(!isThreadRunning())
                startThread();
        }
        else
            audioFilePlayer.pause();
        
        isPlaying = true;
        playPauseButton->setToggleState(!playPauseButton->getToggleState(), false);
        repaint();

    }
    else if(buttonThatWasClicked == stopButton)
    {
        if(audioFilePlayer.isPlaying() || audioFilePlayer.isCurrentlyPaused())
        {
            audioFilePlayer.stop();
            playPauseButton->setToggleState(false, false);
            isPlaying = false;
            currentPosition = 0;
            signalThreadShouldExit();
            repaint();
        }
    }
    else if(buttonThatWasClicked == nextButton)
    {
    }
    else if(buttonThatWasClicked == backButton)
    {
    }
}

void GUI::PlayerComponent::filesDropped (const StringArray &files, int x, int y)
{
    if(File(files[0]).existsAsFile())
    {
        stopButton->triggerClick();
        audioFilePlayer.setFile(files[0]);
        playPauseButton->triggerClick();
    
        currentSong.filePath = audioFilePlayer.getFile().getFileNameWithoutExtension();
        currentSong.duration = audioFilePlayer.getLengthInSeconds();

        seekSlider->setRange(0.0, currentSong.duration, 1.0);
        seekSlider->setEnabled(true);
    }    
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
            
        }
    }
}

void GUI::PlayerComponent::run()
{
    while (!threadShouldExit())
    {        
        if(currentPosition >= currentSong.duration - 1)
            signalThreadShouldExit();

        wait(1000);
        const MessageManagerLock mml (Thread::getCurrentThread());
        if (! mml.lockWasGained())  // if something is trying to kill this job, the lock
            return;

        if(!audioFilePlayer.isCurrentlyPaused())
        {
            currentPosition++;
            seekSlider->setValue(currentPosition);
            
            repaint();
        }
    }
}

void GUI::PlayerComponent::sliderValueChanged (Slider *slider)
{
}

void GUI::PlayerComponent::sliderDragEnded (Slider *slider)
{
    if(slider == seekSlider)
    {
        currentPosition = seekSlider->getValue();
        audioFilePlayer.setPosition(currentPosition);
    }
}
