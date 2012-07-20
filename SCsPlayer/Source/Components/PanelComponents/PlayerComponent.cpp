//We need our Basic class definitions
#include "PlayerComponent.hpp"

GUI::PlayerComponent::PlayerComponent (drow::AudioFilePlayerExt & _audioFilePlayer): firstCall(true), isPlaying(false), playPauseButton(nullptr), stopButton(nullptr), audioFilePlayer(_audioFilePlayer), drow::AudioFileDropTarget(&_audioFilePlayer)
{
    addAndMakeVisible (playPauseButton = new ImageButton("play/pause"));
    playPauseButton->setButtonText (String::empty);
    playPauseButton->setToggleState(false, false);
    playPauseButton->setImages (false, true, true, ImageCache::getFromMemory (BinaryData::play_gif, BinaryData::play_gifSize), 1.0000f, Colours::transparentBlack,
         ImageCache::getFromMemory (BinaryData::play_gif, BinaryData::play_gifSize), 1.0000f, Colours::transparentBlack,
         ImageCache::getFromMemory (BinaryData::pause_gif, BinaryData::pause_gifSize), 1.0000f, Colours::transparentBlack);    
    playPauseButton->addButtonListener (this);

    addAndMakeVisible (stopButton = new ImageButton("stop"));
    stopButton->setButtonText (String::empty);
    stopButton->setImages (false, true, true, ImageCache::getFromMemory (BinaryData::stop_gif, BinaryData::stop_gifSize), 1.0000f, Colours::transparentBlack,
         ImageCache::getFromMemory (BinaryData::stop_gif, BinaryData::stop_gifSize), 1.0000f, Colours::transparentBlack,
         ImageCache::getFromMemory (BinaryData::stop_gif, BinaryData::stop_gifSize), 1.0000f, Colours::transparentBlack);
    stopButton->addButtonListener (this);

    audioFilePlayer.addListener(this);
}
GUI::PlayerComponent::~PlayerComponent ()
{
    audioFilePlayer.removeListener(this);
}
void GUI::PlayerComponent::resized ()
{
    if(firstCall)
    {
        firstCall = false;
    }
    playPauseButton->setBounds(proportionOfWidth(0.050f), proportionOfHeight(0.800f), proportionOfWidth(0.200f), proportionOfHeight(0.200f));
    stopButton->setBounds(playPauseButton->getRight(), proportionOfHeight(0.800f), proportionOfWidth(0.200f), proportionOfHeight(0.200f));
}
void GUI::PlayerComponent::paint (Graphics & g)
{
    // backGround Filling
    g.fillAll (Colour (0xff292929));

    if(isPlaying)
    {
        g.setColour(Colours::white);
        Font f(Font (proportionOfHeight(0.070f), Font::plain));
        g.setFont(f);
        g.drawText("Song: ", (int)proportionOfWidth(0.050f), (int)proportionOfHeight(0.100f), (int)proportionOfWidth(0.250f), (int)f.getHeight(), Justification::left, false);
        g.drawText(currentSong.name, (int)proportionOfWidth(0.250f), (int)proportionOfHeight(0.100f), getWidth() - (int)proportionOfWidth(0.250f), (int)f.getHeight(), Justification::left, true);
    }
}

void GUI::PlayerComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if(buttonThatWasClicked == playPauseButton)
    {   
        if(!playPauseButton->getToggleState())
            audioFilePlayer.start();
        else
            audioFilePlayer.pause();
        isPlaying = true;
        playPauseButton->setToggleState(!playPauseButton->getToggleState(), false);
        repaint();

    }
    else if(buttonThatWasClicked == stopButton)
    {
        audioFilePlayer.stop();
        playPauseButton->setToggleState(false, false);
        isPlaying = false;
        repaint();
    }
}

void GUI::PlayerComponent::filesDropped (const StringArray &files, int x, int y)
{
    stopButton->triggerClick();
    audioFilePlayer.setFile(files[0]);
    playPauseButton->triggerClick();
    
    currentSong.name = audioFilePlayer.getFile().getFileNameWithoutExtension();
    currentSong.duration = audioFilePlayer.getLengthInSeconds();
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
        if(!audioFilePlayer.isPlaying())
        {
            int j = 0;
        }
    }
}
