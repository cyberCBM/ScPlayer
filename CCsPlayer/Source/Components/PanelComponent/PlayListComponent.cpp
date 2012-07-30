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

//We need our Basic class definitions
#include "PlayListComponent.hpp"
// We need the main component
#include "../MainComponent.hpp"

GUI::PlayListComponent::PlayListComponent () : 
firstCall(true), playListBox (nullptr), browseImageButton (nullptr), 
    saveImageButton (nullptr), mainElement (nullptr)
{
	addAndMakeVisible (playListBox = new ListBox ("PlayList", this));
    playListBox->setRowHeight (15);
    playListBox->setLookAndFeel(&csLnF);
    playListBox->setColour (ListBox::backgroundColourId, Colour (0xff292929));
	playListBox->setMultipleSelectionEnabled (true);
    LookAndFeel::getDefaultLookAndFeel().setColour(TextEditor::textColourId, Colours::grey);
    setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());

	addAndMakeVisible (browseImageButton = new ImageButton());
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

	if(File::getCurrentWorkingDirectory().getChildFile ("csProp.xml").exists())
		getPlaylist ((File::getCurrentWorkingDirectory().getChildFile ("csProp.xml")).getFullPathName());

	AudioFormatManager	manager;
	manager.registerBasicFormats();
	audioFormats = manager.getWildcardForAllFormats ();
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
	g.drawRect(1, 1, getWidth() - 2, proportionOfHeight (0.06f) - 1, 1);
    g.drawRect(1, proportionOfHeight (0.06f) + 1, getWidth() - 2, proportionOfHeight (0.82f) + 15 , 1); 
	g.drawRect(1, proportionOfHeight (0.82f) + 15, getWidth() - 2, getHeight() - browseImageButton->getHeight()  , 1);
}

void GUI::PlayListComponent::resized()
{
	const int offset = 2;
	playListBox->setBounds (offset, proportionOfHeight (0.06f) + offset, getWidth() - (2 * offset), proportionOfHeight (0.82f));
    browseImageButton->setBounds(proportionOfWidth (0.10f), getHeight() - browseImageButton->getHeight(), browseImageButton->getWidth(), browseImageButton->getHeight() - offset);
	saveImageButton->setBounds(proportionOfWidth (0.70f), getHeight() - saveImageButton->getHeight(), saveImageButton->getWidth(), saveImageButton->getHeight() - offset);
}

int GUI::PlayListComponent::getNumRows()
{
	return mediaArray.size();
}

void GUI::PlayListComponent::paintListBoxItem (int rowNumber, Graphics & g, int width, int height, bool rowIsSelected)
{
    // backGround Filling
    g.fillAll (Colour (0xff292929));
    g.setColour (Colours::white);

    if (rowIsSelected)
        g.fillAll (Colours::darkgrey);

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
		for(int k = 0; k < t.size(); k++)
		{
			mediaArray.remove (t[k] - k);
		}
		playListBox->updateContent();
		playListBox->deselectAllRows();
	}
}

void GUI::PlayListComponent::returnKeyPressed (int lastRowSelected)
{
}

void GUI::PlayListComponent::listBoxItemDoubleClicked (int row, const MouseEvent & e)
{
}

void GUI::PlayListComponent::buttonClicked (Button * buttonThatWasClicked)
{
    if (buttonThatWasClicked == browseImageButton)
    {
		FileChooser fileChooser("Select Songs", File::nonexistent, String::empty);
		if(fileChooser.browseForMultipleFilesToOpen())
		{
			for(int k = 0; k < fileChooser.getResults().size(); k++)
			{
				if(isAudioFormat (fileChooser.getResults().getReference(k).getFileExtension()))
				{
					if(fileChooser.getResults().getReference(k).getFileExtension() != ".xml")
						setPlaylist (fileChooser.getResults().getReference(k).getFullPathName());
					else
						getPlaylist (fileChooser.getResults().getReference(k).getFullPathName());
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

bool GUI::PlayListComponent::isInterestedInFileDrag (const StringArray & files)
{
	return true;
}

void GUI::PlayListComponent::filesDropped (const StringArray & files, int x, int y)
{
	dropToPlayList (files, this);
}

void GUI::PlayListComponent::getPlaylist (const String & playListFile)
{
	File f(playListFile);
	XmlDocument playListDocument (f);
	mainElement = playListDocument.getDocumentElement();
	XmlElement * playlist =  mainElement->getChildByName("PlayList");
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
	XmlElement player ("CsPlayer");
	XmlElement * songList  = new XmlElement("PlayList");
	player.addChildElement (songList);
	for(int k = 0; k < mediaArray.size(); k++)
		mediaArray.getReference (k).toXml (*songList);

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

void GUI::PlayListComponent::saveDefaultPlayList()
{
	XmlElement * songList  = new XmlElement("PlayList");
	XmlDocument playListDocument (File::getCurrentWorkingDirectory().getChildFile ("csProp.xml"));
	mainElement = playListDocument.getDocumentElement();
	mainElement->removeChildElement(mainElement->getChildByName("PlayList"), true);
	mainElement->addChildElement(songList);
	
	for(int k = 0; k < mediaArray.size(); k++)
	{
		mediaArray.getReference (k).toXml (*songList);
	}
	mainElement->writeToFile (File::getCurrentWorkingDirectory().getChildFile ("csProp.xml"), String::empty);
}

bool GUI::PlayListComponent::isAudioFormat (const String & fileExtension)
{
	if(((audioFormats.contains (fileExtension)) || (!fileExtension.compare (".xml"))) && !(fileExtension == ""))
		return true;
	else
		return false;
}

void GUI::PlayListComponent::dropToPlayList (const StringArray & files, const Component * sourceComponent)
{
	for(int k = 0; k < files.size(); k++)	
	{
		Configurations::Media audio;
		String s = File(files[0]).getFileExtension();
		if(isAudioFormat (File(files[k]).getFileExtension()))
		{
			if (File(files[k]).getFileExtension() != ".xml")
			{
				setPlaylist (File((files[k])).getFullPathName());
			}
			else if (File(files[k]).getFileExtension() == ".xml")
			{
				getPlaylist (File(File(files[k])).getFullPathName());
			}
		}
	}
	playListBox->updateContent();
}