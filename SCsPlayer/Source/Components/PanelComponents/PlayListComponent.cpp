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

#include "PlayListComponent.hpp"

GUI::PlayListComponent::PlayListComponent () : 
listBox (nullptr), browseButton(nullptr), saveButton(nullptr), mainElement(nullptr)
{
	addAndMakeVisible (listBox = new ListBox ("PlayList", this));
    listBox->setRowHeight(15);
    listBox->setColour (ListBox::backgroundColourId, Colour (0xff292929));
	listBox->setMultipleSelectionEnabled (true);

	addAndMakeVisible (browseButton	= new ImageButton());
    browseButton->setImages (true, false, true, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							0.7f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	browseButton->setTooltip ("Select Songs");
	browseButton->addButtonListener(this);

	addAndMakeVisible (saveButton = new ImageButton());
    saveButton->setImages (true, false, true, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize),
							0.7f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	saveButton->setTooltip ("Save PlayList");
	saveButton->addButtonListener(this);
    
    XmlDocument playListDocument (File(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "defaultPlayList.xml"));
	mainElement = playListDocument.getDocumentElement();
	getPlaylist ();

	AudioFormatManager	manager;
	AudioFormat *		format;
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
    g.setColour (Colours::black);
	g.drawRect (0.0f, (float)listBox->getBottom() + 1.0f, (float)getWidth(), 3.0f, 1.0f);
}

void GUI::PlayListComponent::resized()
{
	listBox->setBounds (0, 0, getWidth(), getHeight() - proportionOfHeight (0.21f));
	browseButton->setBounds(proportionOfWidth (0.10f), getHeight() - browseButton->getHeight(), browseButton->getWidth(), browseButton->getHeight());
	saveButton->setBounds(proportionOfWidth (0.60f), getHeight() - saveButton->getHeight(), saveButton->getWidth(), saveButton->getHeight());
}

int GUI::PlayListComponent::getNumRows()
{
	return listOfFiles.size();
}

void GUI::PlayListComponent::paintListBoxItem (int rowNumber, Graphics & g, int width, int height, bool rowIsSelected)
{
    // backGround Filling
    g.fillAll (Colour (0xff292929));
	if (rowIsSelected)
	{
        g.fillAll (Colours::darkgrey);
        g.setColour (Colours::white);
	}
    else
    {
        g.setColour (Colours::lightgrey);
    }

	int timeinSeconds = listOfFiles.getReference(rowNumber).duration;
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
	g.drawText (listOfFiles.getReference(rowNumber).fileName, 0, 0, proportionOfWidth(offset), height, Justification::left, true);
	g.drawText (time, 0, 0, width, height, Justification::right, true);
}

void GUI::PlayListComponent::deleteKeyPressed (int rowSelected)
{
	if(listBox->getNumSelectedRows())
	{
		const SparseSet <int> t = listBox->getSelectedRows();
		for(int k = 0; k < t.size(); k++)
		{
			listOfFiles.remove (t[k] - k);
		}
		listBox->deselectAllRows();
		listBox->updateContent();
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
    if (buttonThatWasClicked == browseButton)
    {
		FileChooser fileChooser("Select Songs", File::nonexistent, String::empty);
		if(fileChooser.browseForMultipleFilesToOpen())
		{
			for(int k = 0; k < fileChooser.getResults().size(); k++)
			{
				if(isAudioFormat (fileChooser.getResults().getReference(k).getFileExtension()))
				{
					if(fileChooser.getResults().getReference(k).getFileExtension() != ".xml")
					{
						setPlaylist (fileChooser.getResults().getReference(k));
					}
					else
					{
						getPlaylist ();
					}
				}
			}
			listBox->updateContent();
		}
	}
	else if (buttonThatWasClicked == saveButton)
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
	for(int k = 0; k < files.size(); k++)	
	{
		struct Audio audio;
		String s = File(files[0]).getFileExtension();
		if(isAudioFormat (File(files[k]).getFileExtension()))
		{
			if (File(files[k]).getFileExtension() != ".xml")
			{
				setPlaylist (File((files[k])).getFullPathName());
			}
			else if (File(files[k]).getFileExtension() == ".xml")
			{
                getPlaylist ();
			}
		}
	}
	listBox->updateContent();
}

void GUI::PlayListComponent::getPlaylist ()
{
	struct Audio audio;
	
	drow::AudioFilePlayerExt fileDuration;

	if(mainElement == nullptr)
	{
		String error = "parsing error";
	}
	else
	{
		if(mainElement->hasTagName ("PlayList"))
		{
			forEachXmlChildElement (*mainElement, e)
			{
				if(e->hasTagName ("Media"))
				{
					audio.filePath = e->getStringAttribute ("path");
					audio.fileName = File (audio.filePath).getFileName();
					fileDuration.setFile (File(audio.filePath));
					audio.duration = fileDuration.getLengthInSeconds();
					listOfFiles.add (audio);
				}
			}
		}
		listBox->updateContent();
	}
}

void GUI::PlayListComponent::setPlaylist (File playListFile)
{
	struct Audio audio;
	drow::AudioFilePlayerExt fileDuration;

	audio.filePath = playListFile.getFullPathName();
	audio.fileName = playListFile.getFileName();
	fileDuration.setFile (File(audio.filePath));
	audio.duration = fileDuration.getLengthInSeconds();
	listOfFiles.add (audio);
}

void GUI::PlayListComponent::savePlayList()
{
	XmlElement songList ("PlayList");
	for(int k = 0; k < listOfFiles.size(); k++)
	{
		XmlElement * mainElement = new XmlElement ("Media");
		mainElement->setAttribute ("path", listOfFiles.getReference(k).filePath);
		songList.addChildElement (mainElement);
	}
	FileChooser fileSaver("Save PlayList", File::nonexistent, "*.xml");
	if(fileSaver.browseForFileToSave  (true))
	{
		String s = fileSaver.getResult().getFullPathName();
		if(fileSaver.getResult().getFileName().contains("."))
		{
			s = s.dropLastCharacters (s.length() - s.indexOf("."));
		}
		s.append(".xml", 4);			
		songList.writeToFile (File::getCurrentWorkingDirectory().getChildFile (s), String::empty);	
	}
}

void GUI::PlayListComponent::saveDefaultPlayList()
{
	XmlElement songList ("PlayList");
	for(int k = 0; k < listOfFiles.size(); k++)
	{
		XmlElement * mainElement = new XmlElement ("Media");
		mainElement->setAttribute ("path", listOfFiles.getReference(k).filePath);
		songList.addChildElement (mainElement);
	}
	songList.writeToFile (File::getCurrentWorkingDirectory().getChildFile ("defaultPlayList.xml"), String::empty);	
}

bool GUI::PlayListComponent::isAudioFormat (String fileExtension)
{
	if(((audioFormats.contains (fileExtension)) || (!fileExtension.compare (".xml"))) && !(fileExtension == ""))
		return true;
	else
		return false;
}