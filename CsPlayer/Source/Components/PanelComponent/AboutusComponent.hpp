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


#ifndef hpp_cpp_AboutUsComponent_cpp_hpp
#define hpp_cpp_AboutUsComponent_cpp_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"

namespace GUI
{
    class AboutUsComponent : public Component
    {
        // Members
    private:
        /** Labels for showing about information */
        ScopedPointer<Label>            csPlayerLabel;
        ScopedPointer<TextEditor>       csPlayerDetailTE;
        ScopedPointer<TextEditor>       csTeamTE;
        ScopedPointer<TextEditor>       csLicenceTE;
        /** Link buttons to open links from about page */
        ScopedPointer<HyperlinkButton>  csPlayerSource;
        ScopedPointer<HyperlinkButton>  csPlayerSite;
        /** Group Component to show information */
        ScopedPointer<GroupComponent>   csPlayerGroupComponent;
        ScopedPointer<GroupComponent>   csTeamgroupComponent;
        ScopedPointer<GroupComponent>   csLicencegroupComponent;


        // Methods
    public:
        void paint(Graphics & g)
        {
            Image img = ImageCache::getFromMemory(BinaryData::icon_gif, BinaryData::icon_gifSize);
            g.drawImageAt(img, 2, 2, false);
        }

        void resized()
        {
            Font font = csPlayerLabel->getFont();
            int width = font.getStringWidth(csPlayerLabel->getText());
            const int offset = 5, fontOffset = 2;
            csPlayerLabel->setBounds(proportionOfWidth(0.17f), proportionOfWidth(0.04f), width, (int)font.getHeight() );
            font.setHeight(16.0000f);
            csPlayerSite->setBounds(0, csPlayerLabel->getHeight() + 20, getWidth(), font.getHeight() + fontOffset);
            csPlayerSource->setBounds(0, csPlayerLabel->getHeight() + 20 + csPlayerSite->getHeight(), getWidth(), font.getHeight() + fontOffset);
            int height = csPlayerLabel->getHeight() + 25 + csPlayerSite->getHeight() + (offset*2);
            csPlayerGroupComponent->setBounds(0, height, getWidth(), 90);
            csPlayerDetailTE->setBounds(fontOffset, height + offset + fontOffset, getWidth() - offset, 80);
            csTeamgroupComponent->setBounds(0, height + 90, getWidth(), 90);
            csTeamTE->setBounds(fontOffset, height + 90 + offset + fontOffset, getWidth() - offset, 80);
            csLicencegroupComponent->setBounds(0, height + 180, getWidth(), 90);
            csLicenceTE->setBounds(fontOffset, height + 180 + offset + fontOffset, getWidth() - offset, 80);
        }

        // Constructor & Destructor
    public:
        AboutUsComponent() : 
          csPlayerLabel(nullptr), csPlayerDetailTE(nullptr), csTeamTE(nullptr), csLicenceTE(nullptr),
              csPlayerSource(nullptr), csPlayerSite(nullptr), 
              csPlayerGroupComponent(nullptr), csTeamgroupComponent(nullptr), csLicencegroupComponent(nullptr)
          {
              LookAndFeel::getDefaultLookAndFeel().setColour(TextEditor::textColourId, Colours::grey);
              setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());
              addAndMakeVisible (csPlayerLabel = new Label ("scPlayer", "Server-Client Audio Player"));
              csPlayerLabel->setFont (Font (20.0000f, Font::bold));
              csPlayerLabel->setJustificationType (Justification::centredLeft);
              csPlayerLabel->setEditable (false, false, false);
              csPlayerLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
              
              addAndMakeVisible (csPlayerGroupComponent = new GroupComponent ("ScPlayer group", "ScPlayer"));
              addAndMakeVisible (csPlayerDetailTE = new TextEditor ("scPlayer Details"));
              csPlayerDetailTE->setFont (Font (13.30f, Font::plain));
              csPlayerDetailTE->setReadOnly (true);
              csPlayerDetailTE->setMultiLine(true, true);
              csPlayerDetailTE->setText("ScPlayer \"Server Client Audio Player\" is C++ based "
                                        "Music player built using Juce and DrowAudio for Network "
                                        "teams to play their server placed "
                                        "music in the network. CsPlayer is Server "
                                        "Audio Player and Client player Manager kind of application.");
              csPlayerDetailTE->setColour (TextEditor::outlineColourId, Colour (0x0));
              csPlayerDetailTE->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
              csPlayerDetailTE->setColour (TextEditor::shadowColourId, Colour (0x0));
              csPlayerDetailTE->setColour (TextEditor::textColourId, Colours::grey);
              csPlayerDetailTE->setColour (TextEditor::backgroundColourId, Colour (0x0));

              addAndMakeVisible (csTeamgroupComponent = new GroupComponent ("ScTeam group", "ScTeam"));
              addAndMakeVisible (csTeamTE = new TextEditor ("scTeam Details"));
              csTeamTE->setFont (Font (13.0000f, Font::plain));
              csTeamTE->setMultiLine(true, true);
              csTeamTE->setText("ScTeam is group of people willingly developes ScPlayer. "
                  "CyberCBM Owns most rights (Though GPUV2 Licence) and responsible for work inside ScPlayer. "
                                "Other helping Members in ScTeam are NREZ, Hammer, PD, Vrushabh.");
              csTeamTE->setReadOnly (true);
              csTeamTE->setColour (TextEditor::outlineColourId, Colour (0x0));
              csTeamTE->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
              csTeamTE->setColour (TextEditor::shadowColourId, Colour (0x0));
              csTeamTE->setColour (TextEditor::textColourId, Colours::grey);
              csTeamTE->setColour (TextEditor::backgroundColourId, Colour (0x0));

              addAndMakeVisible (csLicencegroupComponent = new GroupComponent ("Licence group", "Licence: GPU-V2"));
              addAndMakeVisible (csLicenceTE = new TextEditor ("scLicence Details"));
              csLicenceTE->setFont (Font (13.0000f, Font::plain));
              csLicenceTE->setMultiLine(true, true);
              csLicenceTE->setText("This program is free software; you can redistribute it and/or modify "
                                    "it under the terms of the GNU General Public License as published by "
                                    "the Free Software Foundation; either version 2 of the License, or "
                                    "(at your option) any later version.\n\n"
                                    "This program is distributed in the hope that it will be useful, "
                                    "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                                    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  "
                                    "See the GNU General Public License for more details. ");
              csLicenceTE->setReadOnly (true);
              csLicenceTE->setColour (TextEditor::outlineColourId, Colour (0x0));
              csLicenceTE->setColour (TextEditor::focusedOutlineColourId, Colour (0x0));
              csLicenceTE->setColour (TextEditor::shadowColourId, Colour (0x0));
              csLicenceTE->setColour (TextEditor::outlineColourId, Colour (0x0));
              csLicenceTE->setColour (TextEditor::textColourId, Colours::grey);
              csLicenceTE->setColour (TextEditor::backgroundColourId, Colour (0x0));

              addAndMakeVisible (csPlayerSite = new HyperlinkButton ("ScPlayer", URL ("https://cybercbm.github.com/ScPlayer")));
              csPlayerSite->setFont(Font (16.0000f, Font::bold), false, Justification::centred);
              addAndMakeVisible (csPlayerSource = new HyperlinkButton ("Get ScPlayer Source Code", URL ("https://github.com/cyberCBM/ScPlayer")));
              csPlayerSource->setFont(Font (16.0000f, Font::bold), false, Justification::centred);

          }
          ~AboutUsComponent()
          {

          }

    };

}

#endif // hpp_cpp_AboutUsComponent_cpp_hpp