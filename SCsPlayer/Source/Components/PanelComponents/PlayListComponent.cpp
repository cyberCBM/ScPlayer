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
// We need PlayListComponent definitions here.
//We need our Basic class definitions
#include "PlayListComponent.hpp"
// We need the main component
#include "../MainComponent.hpp"

GUI::PlayListComponent::PlayListComponent () : playListBox (nullptr), browseImageButton (nullptr), saveImageButton (nullptr), 
											   playListElement (nullptr), playingSongIndex (0), playerComponent (nullptr), 
                                               audioSourceReader(nullptr), audioFormatReader(nullptr)
{
	addAndMakeVisible (playListBox = new ListBox ("PlayList", this));
    playListBox->setLookAndFeel(&csLnF);
    playListBox->setRowHeight (15);
    playListBox->setColour (ListBox::backgroundColourId, Colour (0xff292929));
	playListBox->setMultipleSelectionEnabled (true);
    LookAndFeel::getDefaultLookAndFeel().setColour(TextEditor::textColourId, Colours::grey);
    setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());

	addAndMakeVisible (browseImageButton	= new ImageButton());
    browseImageButton->setImages (true, false, true, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							0.7f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	browseImageButton->setTooltip ("Select Songs");
	browseImageButton->addButtonListener(this);

	addAndMakeVisible (saveImageButton = new ImageButton());
    saveImageButton->setImages (true, false, true, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize),
							0.7f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	saveImageButton->setTooltip ("Save PlayList");
	saveImageButton->addButtonListener(this);
	// Read the default playlist
	if(File::getCurrentWorkingDirectory().getChildFile ("csPlayer.xml").exists())
		getPlaylist ((File::getCurrentWorkingDirectory().getChildFile ("csPlayer.xml")).getFullPathName());
    audioFormatManager.registerBasicFormats();
}

GUI::PlayListComponent::~PlayListComponent()
{
	saveDefaultPlayList();
}

void GUI::PlayListComponent::paint (Graphics& g)
{
	// backGround Filling
	g.fillAll (Colour (0xff292929));
    g.setColour(Colours::white);
	g.drawImage (ImageCache::getFromMemory (BinaryData::playlist_gif, BinaryData::playlist_gifSize), 1, 1, 30, 30, 0, 0, 
											ImageCache::getFromMemory (BinaryData::playlist_gif, BinaryData::playlist_gifSize).getWidth(), 
											ImageCache::getFromMemory (BinaryData::playlist_gif , BinaryData::playlist_gifSize).getHeight());
	g.drawFittedText("Play List", 34, 14, getWidth(), 10, juce::Justification::bottom, 1);
	g.setColour (Colours::black);
	g.drawRect(1, 1, getWidth() - 2, proportionOfHeight (0.11f) - 1, 1);
	g.drawRect(1, proportionOfHeight (0.11f) + 1, getWidth() - 2, proportionOfHeight(0.71) + 2, 1); 
	g.drawRect(1, getHeight() - browseImageButton->getHeight() - 1, getWidth() - 2, saveImageButton->getHeight(), 1); 
}

void GUI::PlayListComponent::resized()
{
	if(!playerComponent)
        playerComponent = dynamic_cast<PlayerComponent*>(findParentComponentOfClass<MainComponent>()->getCenterPanel()->getPlayerComponent());
	
    playListBox->setBounds (2, proportionOfHeight (0.12f), getWidth() - 4, proportionOfHeight(0.71));
	browseImageButton->setBounds(proportionOfWidth (0.10f), getHeight() - browseImageButton->getHeight(), browseImageButton->getWidth(), browseImageButton->getHeight()-1);
	saveImageButton->setBounds(proportionOfWidth (0.60f), getHeight() - saveImageButton->getHeight(), saveImageButton->getWidth(), saveImageButton->getHeight()-1);
}

int GUI::PlayListComponent::getNumRows()
{
	return mediaArray.size();
}

void GUI::PlayListComponent::paintListBoxItem (int rowNumber, Graphics & g, int width, int height, bool rowIsSelected)
{
    // backGround Filling
    g.fillAll (Colour (0xff292929));
   
    if(rowNumber == playingSongIndex)
    {
        g.fillAll (Colours::black);
        g.setColour (Colours::white);
    }
    else
        g.setColour (Colours::lightgrey);

	if (rowIsSelected)
	{
        g.fillAll (Colours::darkgrey);
        g.setColour (Colours::white);
	}    
	// To display the time in hrs:min:sec format
	int timeinSeconds = mediaArray.getReference(rowNumber).duration;
	int hours = timeinSeconds/3600;
    int mins = (timeinSeconds - (hours * 3600))/60;
    int secs = (timeinSeconds - (hours * 3600) - (mins * 60));
	float offset = 0;
	String time;
	if(hours != 0)
	{
		time = ((hours > 9 ? (String)hours : "0"+ (String)hours) + ":" +
			                        (mins > 9 ? (String)mins : "0"+ (String)mins) + ":" +
				                    (secs > 9 ? (String)secs : "0"+ (String)secs));
		offset = 0.45;
	}
	else
	{
		time = ((mins > 9 ? (String)mins : "0"+ (String)mins) + ":" +
				       (secs > 9 ? (String)secs : "0"+ (String)secs));
		offset = 0.65;
	}
	g.drawText (mediaArray.getReference(rowNumber).filePath.substring ( mediaArray.getReference(rowNumber).filePath.lastIndexOf("\\") + 1, mediaArray.getReference(rowNumber).filePath.length()), 0, 0, proportionOfWidth(offset), height, Justification::left, true);
	g.drawText (time, 0, 0, width, height, Justification::right, true);
}

void GUI::PlayListComponent::deleteKeyPressed (int rowSelected)
{
	if(playListBox->getNumSelectedRows())
	{
		const SparseSet <int> t = playListBox->getSelectedRows();
		int tempPlayingSongIndex = playingSongIndex;
		for(int i = 0; i < t.size(); i++)
		{
			// Stop the player if the currently playing song is deleted
			if((t[i] - i) == tempPlayingSongIndex)
            {
                playerComponent->signalThreadShouldExit();
				playerComponent->stopButtonClicked();
            }
            else if((t[i] - i) < tempPlayingSongIndex)
				tempPlayingSongIndex -= 1;
			
			mediaArray.remove (t[i] - i);
		}
		playListBox->updateContent();
		// Set the playingSongIndex to the correct index
		playingSongIndex = tempPlayingSongIndex >= mediaArray.size() ? 0 : tempPlayingSongIndex;
		playListBox->deselectAllRows();
        playerComponent->setCurrentSong(getSongPathAtPlayingIndex());
	}
}

void GUI::PlayListComponent::returnKeyPressed (int lastRowSelected)
{
    playerComponent->signalThreadShouldExit();
	playerComponent->stopButtonClicked();
	playingSongIndex = lastRowSelected;
	playerComponent->playPauseButtonClicked();
    playListBox->repaint();
}

void GUI::PlayListComponent::listBoxItemDoubleClicked (int row, const MouseEvent & e)
{
    playListBox->deselectAllRows();
    playerComponent->signalThreadShouldExit();
	playerComponent->stopButtonClicked();
	playingSongIndex = row;
	playerComponent->playPauseButtonClicked();
    playListBox->repaint();
}

void GUI::PlayListComponent::buttonClicked (Button * buttonThatWasClicked)
{
    if (buttonThatWasClicked == browseImageButton)
    {
        String audioFormats = audioFormatManager.getWildcardForAllFormats();
		FileChooser fileChooser("Select media files", File::nonexistent, "*.xml;" + audioFormats);
		if(fileChooser.browseForMultipleFilesToOpen())
		{
			for(int i = 0; i < fileChooser.getResults().size(); i++)
			{
                AudioTransportSource audioSource;
                audioFormatReader = audioFormatManager.createReaderFor(fileChooser.getResults().getReference(i).getFullPathName());
                // If file is from our registered format then only it is added 
                // (Otherwise it could be XMl file only)
                if(audioFormatReader)
                {
                    audioSourceReader = new AudioFormatReaderSource(audioFormatManager.createReaderFor(fileChooser.getResults().getReference(i).getFullPathName()), true);
                    audioSource.setSource(audioSourceReader);
                
                    Configurations::Media media;
                    media.filePath = fileChooser.getResults().getReference(i).getFullPathName();
                    media.duration = audioSource.getLengthInSeconds();
                    mediaArray.add (media);
                }
                else
                {
                    // If it is xml file - check and get your mediaArray filled here
                    if(fileChooser.getResults().getReference(i).getFileExtension().equalsIgnoreCase(".xml"))
                        getPlaylist (fileChooser.getResults().getReference(i).getFullPathName());
                }
			}
			playListBox->updateContent();
		}
	}
	else if (buttonThatWasClicked == saveImageButton)
	{
		savePlayList();
	}
}

bool GUI::PlayListComponent::isInterestedInFileDrag (const StringArray & filesNamesArray)
{
	return true;
}

void GUI::PlayListComponent::filesDropped (const StringArray & filesNamesArray, int x, int y)
{
	dropToPlayList (filesNamesArray, this);
}

void GUI::PlayListComponent::getPlaylist (const String & playListFile)
{
	File f(playListFile);
	XmlDocument playListDocument (f);
	playListElement = playListDocument.getDocumentElement();
	XmlElement * playlist =  playListElement->getChildByName("PlayList");
	if(playlist)
	{
		XmlElement * audioNode =  playlist->getChildByName("Media");
		while(audioNode)
		{
			Configurations::Media temp;
			temp.fromXml(audioNode);
			mediaArray.add(temp);
			audioNode = audioNode->getNextElementWithTagName("Media");
		}
		delete audioNode;
	}
	playListBox->updateContent();
}

void GUI::PlayListComponent::setPlaylist (const String & playListFile)
{
	Configurations::Media audio;
	drow::AudioFilePlayerExt fileDuration;

	audio.filePath = File(playListFile).getFullPathName();
	fileDuration.setFile (File(audio.filePath));
	audio.duration = fileDuration.getLengthInSeconds();
	mediaArray.add (audio);
}

void GUI::PlayListComponent::savePlayList()
{
	if(mediaArray.size())
    {
	    XmlElement player ("CsPlayer");
	    XmlElement * songList = new XmlElement("PlayList");
	    player.addChildElement (songList);
	    for(int i = 0; i < mediaArray.size(); i++)
		    mediaArray.getReference (i).toXml (*songList);

	    FileChooser fileSaver("Save PlayList", File::nonexistent, "*.xml");
	    if(fileSaver.browseForFileToSave  (true))
	    {
		    String s = fileSaver.getResult().getFullPathName();
		    if(fileSaver.getResult().getFileName().contains("."))
			    s = s.dropLastCharacters (s.length() - s.indexOf("."));
		    s.append(".xml", 4);			
		    player.writeToFile (File::getCurrentWorkingDirectory().getChildFile (s), String::empty);	
	    }
    }
}

void GUI::PlayListComponent::saveDefaultPlayList()
{
	XmlElement * songList  = new XmlElement("PlayList");
	XmlDocument playListDocument (File::getCurrentWorkingDirectory().getChildFile ("csPlayer.xml"));
	playListElement = playListDocument.getDocumentElement();
	playListElement->removeChildElement(playListElement->getChildByName("PlayList"), true);
	playListElement->addChildElement(songList);
	
	for(int i = 0; i < mediaArray.size(); i++)
		mediaArray.getReference (i).toXml (*songList);
	playListElement->writeToFile (File::getCurrentWorkingDirectory().getChildFile ("csPlayer.xml"), String::empty);
}

String GUI::PlayListComponent::getSongPathAtPlayingIndex(int index)
{   
	if(playingSongIndex == 0 && index == -1)
        index = mediaArray.size() - 1;
    else if(playingSongIndex == (mediaArray.size() - 1) && index == 1)
        playingSongIndex = index = 0;

    playListBox->repaint();
	return mediaArray.size() ? mediaArray.getReference(playingSongIndex += index).filePath : String::empty;
}

void GUI::PlayListComponent::dropToPlayList (const StringArray & filesNamesArray, const Component * sourceComponent)
{
    String audioFormats = audioFormatManager.getWildcardForAllFormats();
	for(int i = 0; i < filesNamesArray.size(); i++)	
	{
        File tempFile(filesNamesArray[i]);
		AudioTransportSource audioSource;
        audioFormatReader = audioFormatManager.createReaderFor(tempFile);
        // If file is from our registered format then only it is added 
        // (Otherwise it could be XMl file only)
        if(audioFormatReader)
        {
            audioSourceReader = new AudioFormatReaderSource(audioFormatManager.createReaderFor(tempFile), true);
            audioSource.setSource(audioSourceReader);
                
            Configurations::Media media;
            media.filePath = tempFile.getFullPathName();
            media.duration = audioSource.getLengthInSeconds();
            mediaArray.add (media);
        }
        else
        {
            // If it is xml file - check and get your mediaArray filled here
            if(tempFile.getFileExtension().equalsIgnoreCase(".xml"))
                getPlaylist (tempFile.getFullPathName());
        }
	}
	if(sourceComponent == playerComponent)
		playingSongIndex = mediaArray.size() - filesNamesArray.size();    
	playListBox->updateContent();
}

// Communication related methods ...
String GUI::PlayListComponent::getPlayListFromMediaArray()
{
    if(mediaArray.size())
    {
        XmlElement songList("PlayList");
	    for(int i = 0; i < mediaArray.size(); i++)
		    mediaArray.getReference(i).toXml(songList); 
        String playList; 
        playList = songList.createDocument(playList, true, false);
        return playList;
    }
    else
        return "";
}