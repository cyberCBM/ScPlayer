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
        ScopedPointer<Label>            csPlayerDetailLabel;
        ScopedPointer<Label>            csTeamLabel;
        ScopedPointer<Label>            csLicenceLabel;
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
            int height = csPlayerLabel->getHeight() + 20 + csPlayerSite->getHeight() + (offset*2);
            csPlayerGroupComponent->setBounds(0, height, getWidth(), 90);
            csTeamgroupComponent->setBounds(0, height+90, getWidth(), 90);
            csLicencegroupComponent->setBounds(0, height+180, getWidth(), 90);
            
            /*csPlayerDetailLabel->
            csTeamLabel->
            csLicenceLabel-> */
            
            
            
        }

        // Constructor & Destructor
    public:
        AboutUsComponent() : 
          csPlayerLabel(nullptr), csPlayerDetailLabel(nullptr), csTeamLabel(nullptr), csLicenceLabel(nullptr),
              csPlayerSource(nullptr), csPlayerSite(nullptr), 
              csPlayerGroupComponent(nullptr), csTeamgroupComponent(nullptr), csLicencegroupComponent(nullptr)
          {
              addAndMakeVisible (csPlayerLabel = new Label ("csPlayer", "Client-Server Audio Player"));
              csPlayerLabel->setFont (Font (20.0000f, Font::bold));
              csPlayerLabel->setJustificationType (Justification::centredLeft);
              csPlayerLabel->setEditable (false, false, false);
              csPlayerLabel->setColour (TextEditor::textColourId, Colours::aqua);
              csPlayerLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

              addAndMakeVisible (csPlayerGroupComponent = new GroupComponent ("new group", "CsPlayer"));
              addAndMakeVisible (csPlayerDetailLabel = new Label ("new labe", "Write about CsTeam\n"));
              csPlayerDetailLabel->setFont (Font (15.0000f, Font::plain));
              csPlayerDetailLabel->setJustificationType (Justification::centredLeft);
              csPlayerDetailLabel->setEditable (false, false, false);
              csPlayerDetailLabel->setColour (TextEditor::textColourId, Colours::black);
              csPlayerDetailLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

              addAndMakeVisible (csTeamgroupComponent = new GroupComponent ("new group", "CsTeam"));
              addAndMakeVisible (csTeamLabel = new Label ("new labe", "Provide licence details\n"));
              csTeamLabel->setFont (Font (15.0000f, Font::plain));
              csTeamLabel->setJustificationType (Justification::centredLeft);
              csTeamLabel->setEditable (false, false, false);
              csTeamLabel->setColour (TextEditor::textColourId, Colours::black);
              csTeamLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

              addAndMakeVisible (csLicencegroupComponent = new GroupComponent ("new group", "Licence"));
              addAndMakeVisible (csLicenceLabel = new Label ("new labe", "Provide licence details\n"));
              csLicenceLabel->setFont (Font (15.0000f, Font::plain));
              csLicenceLabel->setJustificationType (Justification::centredLeft);
              csLicenceLabel->setEditable (false, false, false);
              csLicenceLabel->setColour (TextEditor::textColourId, Colours::black);
              csLicenceLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

              addAndMakeVisible (csPlayerSite = new HyperlinkButton ("Read Csplayer Wiki", URL ("https://github.com/cyberCBM/CsPlayer/wiki")));
              csPlayerSite->setFont(Font (16.0000f, Font::bold), false, Justification::centred);
              addAndMakeVisible (csPlayerSource = new HyperlinkButton ("Get CsPlayer Source Code", URL ("https://github.com/cyberCBM/CsPlayer")));
              csPlayerSource->setFont(Font (16.0000f, Font::bold), false, Justification::centred);

          }
          ~AboutUsComponent()
          {

          }

    };

}

#endif // hpp_cpp_AboutUsComponent_cpp_hpp