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

#include "BusyWheel.hpp"

GUI::BusyWheel::BusyWheel(const Style wheelStyle, const int number, const juce::Colour colour) 
: petalNumber(number), petalStyle(wheelStyle), petalIterator(0), petalColour(colour)
{
    setBufferedToImage(true);
}

GUI::BusyWheel::~BusyWheel()
{
    deleteAllChildren();
}

void GUI::BusyWheel::paint(Graphics & g)
{
    for (int i = 0; i < petalNumber; i++)
    {
        // The further the index from the iterator, the greyer
        float amountToFade = 1.0f - (float)abs(abs(i - petalIterator) - (petalNumber / 2)) / (float)(petalNumber / 2);
        Colour baseColor = petalColour.withRotatedHue((1.0f - amountToFade) / (petalNumber / 2));
        // The colour below use what seem to give the best results
        g.setColour(baseColor.withSaturation(amountToFade * amountToFade * amountToFade).withBrightness(0.9f).withAlpha(amountToFade * 0.6f + 0.4f));// - amountToFade * 0.6f));

        g.fillPath(petalPath, getTransform(i));
    }
}

void GUI::BusyWheel::resized()
{
    // Compute the petal path, bounding box and rectangle
    petalWidth = (float)getWidth() / 3;
    petalHeight = (float)getHeight() / 6;
    x = 2 * (float)getWidth() / 3;
    y = (float)(getHeight() - petalHeight) / 2;

    petalPath.clear();
    if (petalStyle == UZIGradient)
    {
        petalPath.startNewSubPath(x , y + petalHeight * 0.4600f);
        petalPath.quadraticTo(x + petalWidth * 0.3300f, y, x + petalWidth * 0.5877f, y);
        petalPath.quadraticTo(x + petalWidth, y, x + petalWidth, y + petalHeight / 2);
        petalPath.quadraticTo(x + petalWidth, y + petalHeight, x + petalWidth * 0.5877f, y + petalHeight);
        petalPath.quadraticTo(x + petalWidth * .3300f, y + petalHeight, x, y + petalHeight * .5400f);
        petalPath.closeSubPath();
    }
    else petalPath.addEllipse(x, y + petalHeight / 2, petalWidth + (0.02f * getWidth()), petalWidth + (0.02f * getWidth()));
}

void GUI::BusyWheel::visibilityChanged()
{
    if (isVisible())    startTimer(30);
    else                stopTimer();   
}

void GUI::BusyWheel::timerCallback()
{
    petalIterator = (petalIterator + 1) % petalNumber;
    repaint();
}

const GUI::BusyWheel::AffineTransform GUI::BusyWheel::getTransform(int index) const
{
    return AffineTransform::rotation((juce::float_Pi * 2.0f * index) / (float)petalNumber , getWidth() * 0.5f, getHeight() * 0.5f);
}