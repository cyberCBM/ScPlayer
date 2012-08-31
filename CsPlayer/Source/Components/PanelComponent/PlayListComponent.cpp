/*                                                                                  
*=====================================================================================
*ScPlayer - Server-Client Player ()													 |
*Music file player that plays Network stored songs                                   |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com                                                          |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
* ScPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the ScPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

//We need our Basic class definitions
#include "PlayListComponent.hpp"
// We need the main component
#include "../MainComponent.hpp"
//We need our Basic class definitions for controller 
#include "ClientControlComponent.hpp"


GUI::PlayListComponent::PlayListComponent () : 
firstCall(true), playListBox (nullptr), browseImageButton (nullptr), saveImageButton (nullptr), 
    mainElement (nullptr), clientControlComponent(nullptr), playingSongIndex(0)
{
	addAndMakeVisible (playListBox = new ListBox ("PlayList", this));
    playListBox->setRowHeight (15);
    playListBox->setLookAndFeel(&csLnF);
    playListBox->setColour (ListBox::backgroundColourId, Colour (0xff292929));
	playListBox->setMultipleSelectionEnabled (true);
    LookAndFeel::getDefaultLookAndFeel().setColour(TextEditor::textColourId, Colours::grey);
    setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());

	addAndMakeVisible (browseImageButton = new ImageButton());
    browseImageButton->setImages (false, true, true, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							0.7f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	browseImageButton->setTooltip ("Select Songs");
	browseImageButton->addListener(this);

	addAndMakeVisible (saveImageButton = new ImageButton());
    saveImageButton->setImages (false, true, true, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize),
							0.7f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	saveImageButton->setTooltip ("Save PlayList");
	saveImageButton->addListener(this);

    // Currently no need to read data from the saved defaultPlayList as 
    // We are not saving defaultPlayList in any file
	/*if(File::getCurrentWorkingDirectory().getChildFile ("csProp.xml").exists())
		getPlaylist ((File::getCurrentWorkingDirectory().getChildFile ("csProp.xml")).getFullPathName());*/

	audioFormatManager.registerBasicFormats();
}

GUI::PlayListComponent::~PlayListComponent()
{
    // Do not update default playlist as in csProp.xml file (Not needed for a now.)
    // So currently Commented
	/*saveDefaultPlayList();*/
}

void GUI::PlayListComponent::resized()
{
    if(!clientControlComponent)
        clientControlComponent = findParentComponentOfClass<MainComponent>()->getLeftPanel()->getClientControlComponent();

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
	g.drawRect(2, 35, getWidth() - 4, getHeight() - 37, 1); 
}

int GUI::PlayListComponent::getNumRows()
{
	return mediaArray.size();
}

void GUI::PlayListComponent::paintListBoxItem (int rowNumber, Graphics & g, int width, int height, bool rowIsSelected)
{
    // backGround Filling
    if(rowNumber == playingSongIndex)
    {
        g.fillAll (Colours::black);
        g.setColour (Colours::white);
    }
    else
	{
		g.fillAll (Colour (0xff292929));
        g.setColour (Colours::lightgrey);
	}

    if (rowIsSelected)
	{
        g.fillAll (Colours::darkgrey);
        g.setColour (Colours::white);
	}  
	//To get the time in hrs:min:sec format
	int timeinSeconds = (int)mediaArray.getReference(rowNumber).duration;
	int hours = timeinSeconds/3600;
    int mins = (timeinSeconds - (hours * 3600))/60;
    int secs = (timeinSeconds - (hours * 3600) - (mins * 60));
	float offset = 0.0f;
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
    if(browseImageButton->isEnabled())
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
                    // @to do : Here i have to send stop to all clients also......
                    clientControlComponent->sendStopToServer();
                }
                else if((currentSelected[i] - i) < tempPlayingSongIndex)
				    tempPlayingSongIndex -= 1;
			
			    mediaArray.remove (currentSelected[i] - i);
		    }
		    playListBox->updateContent();
			clientControlComponent->deleteInPlayListToServer(indexList);
		    playListBox->updateContent();
		    // Set the playingSongIndex to the correct index
		    playingSongIndex = tempPlayingSongIndex >= mediaArray.size() ? 0 : tempPlayingSongIndex;
		    playListBox->deselectAllRows();
	    }
    }
}

void GUI::PlayListComponent::returnKeyPressed (int lastRowSelected)
{
    if(browseImageButton->isEnabled())
    {
        playingSongIndex = lastRowSelected;
        clientControlComponent->songDoubleClickedPlay(lastRowSelected);
        repaint();
    }
}

void GUI::PlayListComponent::listBoxItemDoubleClicked (int row, const MouseEvent & /*e*/)
{
    if(browseImageButton->isEnabled())
    {
        playingSongIndex = row;
        clientControlComponent->songDoubleClickedPlay(row);
        playListBox->deselectRow(row);
        repaint();
    }
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
			clientControlComponent->addInPlayListToServer(playList);
		}
	}
	else if (buttonThatWasClicked == saveImageButton)
	{
		savePlayList();
	}
}

int GUI::PlayListComponent::getCurrentSelectedIndex()
{
    if(playListBox->getLastRowSelected() == -1)
        return 0; 
    else
        return playListBox->getLastRowSelected(); 
}

bool GUI::PlayListComponent::isInterestedInFileDrag (const StringArray & /*files*/)
{
	return true;
}

void GUI::PlayListComponent::filesDropped (const StringArray & files, int /*x*/, int /*y*/)
{
    // If it is allowed then only let it drop files on it.... 
    // it means if it has lock or when disconnected(Not connected to server) it can modify
    if(browseImageButton->isEnabled())
        dropToPlayList (files, this);
}

bool GUI::PlayListComponent::isInterestedInDragSource (const SourceDetails & /*dragSourceDetails*/)
{
	if(browseImageButton->isEnabled())
        return true;
    else
        return false;
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
	int x = dragSourceDetails.localPosition.getX() - 4;
	int y =  dragSourceDetails.localPosition.getY() - 37;
	int insertionIndex = playListBox->getInsertionIndexForPosition (x, y);
	Array<int> sourceIndices;
	String sourceIndexString = dragSourceDetails.description.toString();
	
	clientControlComponent->sendDragDropIndexToServer(sourceIndexString, String(insertionIndex));

	while(sourceIndexString.length())
	{
		sourceIndices.add(sourceIndexString.upToFirstOccurrenceOf (" ", false, false).getIntValue() - 1);	
		sourceIndexString = sourceIndexString.fromFirstOccurrenceOf (" ", false, false);
	}
	if(insertionIndex == mediaArray.size())
		insertionIndex = mediaArray.size();

	if(insertionIndex != -1)
	{
		int temp = 0;
		for(int i = 0; i < sourceIndices.size(); i++)
		{
			if (insertionIndex >= sourceIndices.getReference(i))
			{
				mediaArray.insert (insertionIndex, mediaArray.getReference(sourceIndices.getReference(i) - i));
				mediaArray.remove (sourceIndices.getReference(i) - i);
				playListBox->selectRow (insertionIndex - 1);
				if(sourceIndices.getReference(i)-temp == playingSongIndex)
				{
					playingSongIndex = insertionIndex - 1;
					temp++;
				}
				else if ((sourceIndices.getReference(i)-temp < playingSongIndex) && (insertionIndex > playingSongIndex))
				{
					playingSongIndex = playingSongIndex - 1;
					temp++;
				}
				else if ((sourceIndices.getReference(i)-temp > playingSongIndex) && (insertionIndex <= playingSongIndex))
				{
					playingSongIndex = playingSongIndex + 1;
					temp++;
				}
			}
			else
			{
				if(sourceIndices.getReference(i) == mediaArray.size() - 1)
					mediaArray.insert (insertionIndex, mediaArray.getLast());
				else
					mediaArray.insert (insertionIndex, mediaArray.getReference(sourceIndices.getReference(i)+1));
				mediaArray.remove (sourceIndices.getReference(i) + 1);
				playListBox->selectRow (insertionIndex);
				if(sourceIndices.getReference(i)+temp == playingSongIndex)
				{
					playingSongIndex = insertionIndex;
					temp++;
				}				
				else if ((sourceIndices.getReference(i)+temp < playingSongIndex) && (insertionIndex > playingSongIndex))
				{
					playingSongIndex = playingSongIndex - 1;
					temp++;
				}
				else if ((sourceIndices.getReference(i)+temp > playingSongIndex) && (insertionIndex <= playingSongIndex))
				{
					playingSongIndex = playingSongIndex + 1;
					temp++;
				}
			}
			playListBox->updateContent();
			repaint();
		}
	}
}

void GUI::PlayListComponent::getPlaylist (const String & playListFile)
{
	File f(playListFile);
	XmlDocument playListDocument (f);
	mainElement = playListDocument.getDocumentElement();
	XmlElement * playlist =  mainElement->getChildByName("PlayList");
    if(!playlist)
        return;
	XmlElement * audioNode =  playlist->getChildByName("Media");
	while(audioNode)
	{
		Configurations::Media temp;
		temp.fromXml(audioNode);
		mediaArray.add(temp);
		audioNode = audioNode->getNextElementWithTagName("Media");
	}
	delete audioNode;
	playListBox->updateContent();
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
	XmlElement * songList = new XmlElement("PlayList");
	if(File::getCurrentWorkingDirectory().getChildFile ("csProp.xml").exists())
	{
		XmlDocument playListDocument (File::getCurrentWorkingDirectory().getChildFile ("csProp.xml"));
		mainElement = playListDocument.getDocumentElement();
		if (mainElement->getChildByName("PlayList"))
			mainElement->removeChildElement(mainElement->getChildByName("PlayList"), true);
	}
	else
	{
		mainElement  = new XmlElement("CsPlayer");
	}
	mainElement->addChildElement(songList);
	
	for(int i = 0; i < mediaArray.size(); i++)
	{
		mediaArray.getReference (i).toXml (*songList);
	}
	mainElement->writeToFile (File::getCurrentWorkingDirectory().getChildFile ("csProp.xml"), String::empty);
}

void GUI::PlayListComponent::dropToPlayList (const StringArray & filesNamesArray, const Component * /*sourceComponent*/)
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
	playListBox->updateContent();
    XmlElement songList("PlayList");
	for(int i = currentNumOfElements; i < mediaArray.size(); i++)
		mediaArray.getReference(i).toXml(songList); 
    String playList ;
    playList = songList.createDocument(playList, true, false);
    clientControlComponent->addInPlayListToServer(playList);
}

// Communication related functions 

void GUI::PlayListComponent::updatePlayListFromServer(const String & playListInString)
{
    browseImageButton->setEnabled(false);
    saveImageButton->setEnabled(false);
    mediaArray.clear();
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
    playListBox->repaint();
}

void GUI::PlayListComponent::addInPlayListFromServer(const String & playListInString)
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

void GUI::PlayListComponent::deleteInPlayListFromServer(const Array<int> & indexList)
{
    // delete those rows from mediaArray
    for(int i = 0; i < indexList.size(); i++)
		mediaArray.remove (indexList[i]);
		
    playListBox->updateContent();
	playListBox->deselectAllRows();
}

void GUI::PlayListComponent::allowPlayListModification(bool allow)
{
    browseImageButton->setEnabled(allow);
    saveImageButton->setEnabled(allow);
}

void GUI::PlayListComponent::itemDroppedFromServer (String dragIndexInString, const String dropIndexInString)
{
	int insertionIndex = dropIndexInString.getIntValue();
	Array<int> sourceIndices;
	
	while(dragIndexInString.length())
	{
		sourceIndices.add(dragIndexInString.upToFirstOccurrenceOf (" ", false, false).getIntValue() - 1);	
		dragIndexInString = dragIndexInString.fromFirstOccurrenceOf (" ", false, false);
	}
	if(insertionIndex == mediaArray.size())
		insertionIndex = mediaArray.size();

	if(insertionIndex != -1)
	{
		int temp = 0;
		for(int i = 0; i < sourceIndices.size(); i++)
		{
			if (insertionIndex >= sourceIndices.getReference(i))
			{
				mediaArray.insert (insertionIndex, mediaArray.getReference(sourceIndices.getReference(i) - i));
				mediaArray.remove (sourceIndices.getReference(i) - i);
				playListBox->selectRow (insertionIndex - 1);
				if(sourceIndices.getReference(i)-temp == playingSongIndex)
				{
					playingSongIndex = insertionIndex - 1;
					temp++;
				}
				else if ((sourceIndices.getReference(i)-temp < playingSongIndex) && (insertionIndex > playingSongIndex))
				{
					playingSongIndex = playingSongIndex - 1;
					temp++;
				}
				else if ((sourceIndices.getReference(i)-temp > playingSongIndex) && (insertionIndex <= playingSongIndex))
				{
					playingSongIndex = playingSongIndex + 1;
					temp++;
				}
			}
			else
			{
				if(sourceIndices.getReference(i) == mediaArray.size() - 1)
					mediaArray.insert (insertionIndex, mediaArray.getLast());
				else
					mediaArray.insert (insertionIndex, mediaArray.getReference(sourceIndices.getReference(i)+1));
				mediaArray.remove (sourceIndices.getReference(i) + 1);
				playListBox->selectRow (insertionIndex);
				if(sourceIndices.getReference(i)+temp == playingSongIndex)
				{
					playingSongIndex = insertionIndex;
					temp++;
				}				
				else if ((sourceIndices.getReference(i)+temp < playingSongIndex) && (insertionIndex > playingSongIndex))
				{
					playingSongIndex = playingSongIndex - 1;
					temp++;
				}
				else if ((sourceIndices.getReference(i)+temp > playingSongIndex) && (insertionIndex <= playingSongIndex))
				{
					playingSongIndex = playingSongIndex + 1;
					temp++;
				}
			}
			playListBox->updateContent();
			repaint();
		}
	}
}
