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
*A copy of the license is included in the CsPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

// custom LoolAndFeel and Grpahics info
#include "CsLookAndFeel.hpp"

GUI::CsPlayerLookAndFeel::CsPlayerLookAndFeel()
{

}

GUI::CsPlayerLookAndFeel::~CsPlayerLookAndFeel()
{

}

void GUI::CsPlayerLookAndFeel::drawTableHeaderBackground (Graphics & g, TableHeaderComponent & header)
{
    g.fillAll (Colours::black);
}

void GUI::CsPlayerLookAndFeel::drawTableHeaderColumn (Graphics & g, const String & columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags)
{
    g.setColour(Colour (61, 61, 61));
    g.drawRect(0, 0, width, height, 1);
    if (isMouseOver)
        g.setColour (Colour (255,255,255));
    else
        g.setColour (Colour (194,194,194));

    int rightOfText = width - 3;

    if ((columnFlags & (TableHeaderComponent::sortedForwards | TableHeaderComponent::sortedBackwards)) != 0)
    {
        const float top = height * ((columnFlags & TableHeaderComponent::sortedForwards) != 0 ? 0.35f : (1.0f - 0.35f));
        const float bottom = height - top;
        const float w = height * 0.5f;
        const float x = rightOfText - (w * 1.25f);
        rightOfText = (int) x;
        Path sortArrow;
        sortArrow.addTriangle (x, bottom, x + w * 0.5f, top, x + w, bottom);
        g.fillPath (sortArrow);

    }

    Font defaultFont = LookAndFeel::getDefaultLookAndFeel().getAlertWindowFont();
    defaultFont.setHeight(defaultFont.getHeight() + 3);
    g.setFont (defaultFont);
    const int textX = 3;
    g.drawFittedText (columnName, textX, 0, rightOfText - textX, (int)defaultFont.getHeight() * 2, Justification::left, 1);
}


void GUI::CsPlayerLookAndFeel::drawScrollbarButton(Graphics & g, ScrollBar & scrollbar,int width, int height, int buttonDirection, bool /*isScrollbarVertical*/, bool isMouseOverButton, bool isButtonDown)
{
    ColourGradient gradient(Colour(66,66,66), 0.0f, 0.0f, Colour(76,76,76), (float)width, 0.0f, false);
    FillType fill(gradient);
    g.setFillType(fill);
    g.fillAll();
    Path p;
    if(buttonDirection == 0) // UP
        p.addTriangle (0.5f, 0.25f, 1.0f, 1.0f, 0.0f, 1.0f);
    else
        if (buttonDirection == 1) // RIGHT
            p.addTriangle (0.0f, 0.0f, 0.75f, 0.5f, 0.0f, 1.0f);
        else
            if (buttonDirection == 2) // DOWN
                p.addTriangle (0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.75f);
            else
                if (buttonDirection == 3) // LEFT
                    p.addTriangle (1.0f, 0.0f, 1.0f, 1.0f, 0.25f, 0.5f);

    if(isButtonDown)
        g.setColour(Colour(26,26,26));
    else
        if(isMouseOverButton)
            g.setColour(Colour(204,204,204));
        else
            g.setColour(Colour(128,128,128));
    p.applyTransform(p.getTransformToScaleToFit((float)width/4, (float)height/4, (float)width/2, (float)height/2, true, Justification::centred));
    if (buttonDirection == 0 || buttonDirection == 2)
    {
        if (isButtonDown)
            g.fillPath (p, AffineTransform::identity.translation (1.5f, 1.0f));
        else
            g.fillPath (p, AffineTransform::identity.translation (0.5f, 0.0f));
    }
    else
    {
        if (isButtonDown)
            g.fillPath (p, AffineTransform::identity.translation (1.0f, 1.5f));
        else
            g.fillPath (p, AffineTransform::identity.translation (0.0f, 0.5f));
    }
}

void GUI::CsPlayerLookAndFeel::drawScrollbar (Graphics & g, ScrollBar & scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown)
{
    if(isMouseOver || isMouseDown)
        g.setColour(Colour(204,204,204));
    else
        g.setColour(Colour(128,128,128));

    if(isScrollbarVertical)
    {
        int w = width / 2;
        g.fillRoundedRectangle((float)x + 1.0f, (float)thumbStartPosition, (float)w * 1.7f, (float)thumbSize, (float)w/2);
    }
    else
    {
        int h = height / 2;
        g.fillRoundedRectangle((float)thumbStartPosition, (float)y + 1.0f, (float)thumbSize, (float)h * 1.7f, (float)h/2);
    }
} 
