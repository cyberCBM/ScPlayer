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


GUI::PlayListComponent::PlayListComponent () : listBox (nullptr), browseButton(nullptr), saveButton(nullptr)
{
    setLookAndFeel(&csLnF);
	addAndMakeVisible (listBox = new ListBox ("PlayList", this));
    listBox->setRowHeight (15);
    listBox->setColour (ListBox::backgroundColourId, Colour (0xff292929));
	listBox->setMultipleSelectionEnabled (true);

	addAndMakeVisible (browseButton	= new ImageButton());
    browseButton->setImages (false, true, false, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
    browseButton->addButtonListener(this);

	addAndMakeVisible (saveButton = new ImageButton());
    saveButton->setImages (false, true, false, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize), 
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize),
							1.0f, Colours::transparentBlack, ImageCache::getFromMemory(BinaryData::save_gif, BinaryData::save_gifSize),
							1.0f, Colours::transparentBlack, 0.0f);
	saveButton->addButtonListener(this);
}

GUI::PlayListComponent::~PlayListComponent()
{
	removeChildComponent (listBox);
	/*removeChildComponent (browseButton);
	removeChildComponent (saveButton);*/
}

void GUI::PlayListComponent::paint (Graphics& g)
{
	// backGround Filling
    g.fillAll (Colour (0xff292929));
}

void GUI::PlayListComponent::resized()
{
	listBox->setBounds (0, 0, getWidth(), getHeight() - proportionOfHeight(0.10f) - 1);
	browseButton->setBounds(5, getHeight() - proportionOfHeight(0.10f) - 1, proportionOfWidth(0.20f), proportionOfHeight(0.10f));
	saveButton->setBounds(10 + proportionOfWidth(0.20f), getHeight() - proportionOfHeight(0.10f) - 1, proportionOfWidth(0.20f), proportionOfHeight(0.10f));
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
    
	g.drawText (listOfFiles.getReference(rowNumber).fileName.dropLastCharacters (((listOfFiles.getReference(rowNumber).fileName.length()>13) ? (listOfFiles.getReference(rowNumber).fileName.length() - 13) : 0)),
				0, 0, width, height, Justification::left, true);
	g.drawText (listOfFiles.getReference(rowNumber).duration, 0, 0, width, height, Justification::right, true);
}

//var PlayListComponent::getDragSourceDescription(const SparseSet<int>& selectedRows)
//{
//    String desc;
//
//    for (int i = 0; i < selectedRows.size(); ++i)
//        desc << (selectedRows [i] + 1) << " ";
//
//	listBox->updateContent();
//    return desc.trim();
//}

void GUI::PlayListComponent::buttonClicked (Button * buttonThatWasClicked)
{
    if (buttonThatWasClicked == browseButton)
    {
		FileChooser fileChooser("Select Songs", File ("D:\Songs"), String::empty);
		if(fileChooser.browseForMultipleFilesToOpen())
		{
			for(int k = 0; k < fileChooser.getResults().size(); k++)
			{
				struct Audio audio;
				drow::AudioFilePlayerExt fileDuration;
				if(fileChooser.getResults().getReference(k).getFileExtension() == ".mp3")
				{
					audio.filePath = fileChooser.getResults().getReference(k).getFullPathName();
					audio.fileName = fileChooser.getResults().getReference(k).getFileName();
					fileDuration.setFile (File(audio.filePath));
					audio.duration = String (fileDuration.getLengthInSeconds()/60, 2);
					listOfFiles.add (audio);
				}
			}
			listBox->updateContent();
		}
	}
	else if (buttonThatWasClicked == saveButton)
	{
		XmlElement songList ("PLAYLIST");
		for(int k = 0; k < listOfFiles.size(); k++)
		{
			XmlElement * mainElement = new XmlElement ("audiosong");
			mainElement->setAttribute ("pathname", listOfFiles.getReference(k).filePath);
			mainElement->setAttribute ("duration", listOfFiles.getReference(k).duration);
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
		if(File(files[k]).getFileExtension() == ".mp3")
		{
			drow::AudioFilePlayerExt fileDuration;
			audio.filePath = File(files[k]).getFullPathName();
			audio.fileName = File(files[k]).getFileName();
			fileDuration.setFile (File(files[k]));
			audio.duration = String (fileDuration.getLengthInSeconds()/60, 2);
			listOfFiles.add (audio);
		}			
	}
	listBox->updateContent();
}
