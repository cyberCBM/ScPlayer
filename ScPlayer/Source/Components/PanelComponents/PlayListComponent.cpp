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

// We need PlayListComponent definitions here.
//We need our Basic class definitions
#include "PlayListComponent.hpp"
// We need the main component
#include "../MainComponent.hpp"
// Included to get the reference object of the PlayerComponent
#include "PlayerComponent.hpp"
// This class is needed to communicate with clients out there
#include "ControlBarComponent.hpp"

GUI::PlayListComponent::PlayListComponent () : playListBox (nullptr), browseImageButton (nullptr), saveImageButton (nullptr), 
											   mainElement (nullptr), playingSongIndex (0), playerComponent (nullptr), 
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
    browseImageButton->setImages (false, true, true, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							0.7f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	browseImageButton->setTooltip ("Select Songs");
	browseImageButton->addButtonListener(this);

	addAndMakeVisible (saveImageButton = new ImageButton());
    saveImageButton->setImages (false, true, true, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize), 
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
    browseImageButton->removeButtonListener(this);
    saveImageButton->removeButtonListener(this);
}

void GUI::PlayListComponent::resized()
{
	if(!playerComponent)
        playerComponent = dynamic_cast<PlayerComponent*>(findParentComponentOfClass<MainComponent>()->getCenterPanel()->getPlayerComponent());
	
    playListBox->setBounds (4, 37, getWidth() - 8, getHeight() - 40);
    saveImageButton->setBounds(getWidth() - 30, 4, 28, 28);
    browseImageButton->setBounds(getWidth() - 60, 4, 28, 28);
}

void GUI::PlayListComponent::paint (Graphics& g)
{
	// backGround Filling
	g.fillAll (Colour (0xff292929));
    g.setColour(Colours::aquamarine);
	g.drawFittedText("Playing List", 6, 14, getWidth(), 10, juce::Justification::bottom, 1);
	g.setColour (Colours::black);
	g.drawRect(2, 2, getWidth() - 4, 32, 1);
    //Setting Lower rectangle 
	g.drawRect(2, 35, getWidth() - 4, getHeight() - 37, 1); 
}

GUI::ControlBarComponent * GUI::PlayListComponent::getControlBarComponent()
{
    return findParentComponentOfClass<GUI::MainComponent>()->getTopPanel()->getControlBarComponent();
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
	int timeinSeconds = (int)mediaArray.getReference(rowNumber).duration;
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
		offset = 0.45f;
	}
	else
	{
		time = ((mins > 9 ? (String)mins : "0"+ (String)mins) + ":" +
				       (secs > 9 ? (String)secs : "0"+ (String)secs));
		offset = 0.65f;
	}
	g.drawText (mediaArray.getReference(rowNumber).filePath.substring ( mediaArray.getReference(rowNumber).filePath.lastIndexOf("\\") + 1, mediaArray.getReference(rowNumber).filePath.length()), 0, 0, proportionOfWidth(offset), height, Justification::left, true);
	g.drawText (time, 0, 0, width, height, Justification::right, true);
}

void GUI::PlayListComponent::deleteKeyPressed (int /*rowSelected*/)
{
	if(playListBox->getNumSelectedRows())
	{
		const SparseSet <int> currentSelected = playListBox->getSelectedRows();
		int tempPlayingSongIndex = playingSongIndex;
		Array<int> indexList;
		for(int i = 0; i < currentSelected.size(); i++)
		{
            indexList.add(currentSelected[i] - i);
			// Stop the player if the currently playing song is deleted
			if((currentSelected[i] - i) == tempPlayingSongIndex)
            {
				playerComponent->signalThreadShouldExit();
				playerComponent->stopButtonClicked();
            }
            else if((currentSelected[i] - i) < tempPlayingSongIndex)
				tempPlayingSongIndex -= 1;
			
			mediaArray.remove (currentSelected[i] - i);
		}
		getControlBarComponent()->deleteInPlayListToAllClients(indexList);
		playListBox->updateContent();
		// Set the playingSongIndex to the correct index
		playingSongIndex = tempPlayingSongIndex >= mediaArray.size() ? 0 : tempPlayingSongIndex;
		playListBox->deselectAllRows();
        playerComponent->setCurrentSong(getSongPathAtPlayingIndex());
        getControlBarComponent()->sendPlayingIndexToAllClients(playingSongIndex);
        playerComponent->repaint();
	}
}

void GUI::PlayListComponent::returnKeyPressed (int lastRowSelected)
{
    songPlayedByClick(lastRowSelected);
}

void GUI::PlayListComponent::listBoxItemDoubleClicked (int row, const MouseEvent & /*e*/)
{
    songPlayedByClick(row);
}

void GUI::PlayListComponent::songPlayedByClick(const int index)
{
    playListBox->deselectAllRows();
    playerComponent->signalThreadShouldExit();
	playerComponent->stopButtonClicked();
	playingSongIndex = index;
	playerComponent->playPauseButtonClicked();
    playListBox->repaint();
    getControlBarComponent()->sendPlayingIndexToAllClients(playingSongIndex);
}

void GUI::PlayListComponent::buttonClicked (Button * buttonThatWasClicked)
{
    if (buttonThatWasClicked == browseImageButton)
    {
		const int currentNumOfElements = mediaArray.size();
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
			XmlElement songList("PlayList");
			for(int i = currentNumOfElements; i < mediaArray.size(); i++)
				mediaArray.getReference(i).toXml(songList); 
			String playList ;
			playList = songList.createDocument(playList, true, false);
			getControlBarComponent()->addInPlayListToAllClients(playList);
		}
	}
	else if (buttonThatWasClicked == saveImageButton)
	{
		savePlayList();
	}
}

bool GUI::PlayListComponent::isInterestedInFileDrag (const StringArray & /*filesNamesArray*/)
{
	return true;
}

void GUI::PlayListComponent::filesDropped (const StringArray & filesNamesArray, int /*x*/, int /*y*/)
{
	dropToPlayList (filesNamesArray, this);
}

var GUI::PlayListComponent::getDragSourceDescription(const SparseSet<int>& selectedRows)
{
    String desc;
	for (int i = 0; i < selectedRows.size(); ++i)
        desc << (selectedRows [i] + 1) << " ";
	playListBox->updateContent();
	return desc.trim();
}

void GUI::PlayListComponent::itemDropped (const SourceDetails & dragSourceDetails)
{
	int x = dragSourceDetails.localPosition.getX() - 2;
	int y =  dragSourceDetails.localPosition.getY() - proportionOfHeight (0.11f) - 2;
	int z1 = playListBox->getInsertionIndexForPosition (x, y);
	
	String s = dragSourceDetails.description.toString();
	int i = s.getIntValue() - 1;
	
	if(z1 == mediaArray.size())
		z1 = mediaArray.size();
	
	
	
	if(z1 >= i)
	{
		if(z1 != -1)
		{
			mediaArray.insert (z1, mediaArray.getReference(i));
			playListBox->updateContent();
			repaint();
			mediaArray.remove (i);
			playListBox->selectRow (z1-1);
			playListBox->updateContent();
			repaint();
		}
	}
	else 
	{
		if(z1 != -1)
		{
			mediaArray.remove (i);
			playListBox->updateContent();
			repaint();
			mediaArray.insert (z1, mediaArray.getReference(i));
			playListBox->selectRow (z1-1);
			playListBox->updateContent();
			repaint();
		}
	}
}

bool GUI::PlayListComponent::isInterestedInDragSource (const SourceDetails & /*dragSourceDetails*/)
{
	return true;
}


void GUI::PlayListComponent::getPlaylist (const String & playListFile)
{
	File f(playListFile);
	XmlDocument playListDocument (f);
	mainElement = playListDocument.getDocumentElement();
	XmlElement * playlist =  mainElement->getChildByName("PlayList");
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
	mainElement = playListDocument.getDocumentElement();
	mainElement->removeChildElement(mainElement->getChildByName("PlayList"), true);
	mainElement->addChildElement(songList);
	
	for(int i = 0; i < mediaArray.size(); i++)
		mediaArray.getReference (i).toXml (*songList);
	mainElement->writeToFile (File::getCurrentWorkingDirectory().getChildFile ("csPlayer.xml"), String::empty);
}

String GUI::PlayListComponent::getSongPathAtPlayingIndex(int index)
{   
	if(playingSongIndex == 0 && index == -1)
        index = mediaArray.size() - 1;
    else if(playingSongIndex == (mediaArray.size() - 1) && index == 1)
        playingSongIndex = index = 0;
    // To focus the current playing song on the display of the listbox
	playListBox->scrollToEnsureRowIsOnscreen (playingSongIndex);
    playListBox->repaint();
	return mediaArray.size() ? mediaArray.getReference(playingSongIndex += index).filePath : String::empty;
}

void GUI::PlayListComponent::dropToPlayList (const StringArray & filesNamesArray, const Component * sourceComponent)
{
	const int currentNumOfElements = mediaArray.size();
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
	XmlElement songList("PlayList");
	for(int i = currentNumOfElements; i < mediaArray.size(); i++)
		mediaArray.getReference(i).toXml(songList); 
    String playList ;
    playList = songList.createDocument(playList, true, false);
    getControlBarComponent()->addInPlayListToAllClients(playList);
}

// Communication related methods ...
String GUI::PlayListComponent::getPlayListFromMediaArray()
{
    if(mediaArray.size())
    {
        XmlElement songList("PlayList");
	    for(int i = 0; i < mediaArray.size(); i++)
		    mediaArray.getReference(i).toXml(songList); 
        
        String playList = songList.createDocument(playList, true, false);
        return playList;
    }
    else
        return "";
}

void GUI::PlayListComponent::addInPlayListFromClient(const String & playListInString)
{
    XmlDocument playlist(playListInString);
    mainElement =  playlist.getDocumentElement();
    if(mainElement == nullptr)
        return;
    XmlElement *  mediaNode = mainElement->getChildByName("Media");
	// Fill data from String
    while(mediaNode)
	{
		Configurations::Media tempMedia;
		tempMedia.fromXml(mediaNode);
		mediaArray.add(tempMedia);
		mediaNode = mediaNode->getNextElementWithTagName("Media");
	}
    playListBox->updateContent();
}

void GUI::PlayListComponent::deleteInPlayListFromClient(const Array<int> & indexList)
{
    // delete those rows from mediaArray
    int tempPlayingSongIndex = playingSongIndex;
	for(int i = 0; i < indexList.size(); i++)
	{
		// Stop the player if the currently playing song is deleted
		if((indexList[i]) == tempPlayingSongIndex)
        {
			playerComponent->signalThreadShouldExit();
			playerComponent->stopButtonClicked();
        }
        else if((indexList[i]) < tempPlayingSongIndex)
			tempPlayingSongIndex -= 1;
		mediaArray.remove (indexList[i]);
	}
		
	playListBox->updateContent();
	// Set the playingSongIndex to the correct index
	playingSongIndex = tempPlayingSongIndex >= mediaArray.size() ? 0 : tempPlayingSongIndex;
	playListBox->deselectAllRows();
	playerComponent->setCurrentSong(getSongPathAtPlayingIndex());
    playerComponent->repaint();

	
	
/*	for(int i = 0; i < indexList.size(); i++)
		mediaArray.remove (indexList[i]);
		
    playListBox->updateContent();
	playListBox->deselectAllRows();
    playerComponent->repaint();*/
    // When deleted from 
}