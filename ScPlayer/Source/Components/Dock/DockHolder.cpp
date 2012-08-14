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

//We need our basic class definitions
#include "DockHolder.hpp"
//We need Dock buttons 
#include "DockButtons.hpp"
// we need manager to manage this component
#include "DockManager.hpp"
// we need panel to display all the panels
#include "DockPanel.hpp"

GUI::DockHolder::DockHolder(DockManager * parent, DockPanel * p, const int type)
: manager (parent),panel (p),orientation (type),docked (true),
open (false),inside (false),resizable (0), constrainer (0), lockAutomaticAnimation(false)
{
    initConstrainer ();
}
GUI::DockHolder::~DockHolder ()
{
    deleteAllChildren ();
    delete constrainer;
}

void GUI::DockHolder::initConstrainer ()
{
    switch (orientation)
    {
    case CENTER:
        setSize (manager->getWidth(), manager->getHeight());
        break;
    case TOP:
        setSize (manager->getWidth(), 60);
        break;
    case LEFT:
        constrainer = new ComponentBoundsConstrainer ();
        constrainer->setMinimumWidth (150);
        constrainer->setMaximumWidth (250);
        addAndMakeVisible (resizable = new ResizableBorderComponent (this, constrainer));
        resizable->setBorderThickness (BorderSizeInt (0, 0, 0, PADDINGSIZE));
        setSize (150, manager->getHeight());
        break;
    case RIGHT:
        constrainer = new ComponentBoundsConstrainer ();
        constrainer->setMinimumWidth (150);
        constrainer->setMaximumWidth (250);
        addAndMakeVisible (resizable = new ResizableBorderComponent (this, constrainer));
        resizable->setBorderThickness (BorderSizeInt (0, PADDINGSIZE, 0, 0));
        setSize (150, manager->getHeight());
        break;
    }
}
void GUI::DockHolder::paint (Graphics & g)
{
    g.fillAll (Colours::black);

    const int button = BUTTONSIZE;
    const int padding = PADDINGSIZE;

    const int width = getWidth();
    const int height = getHeight();

    if (orientation == CENTER)
    {
        {
            const float left = 0.0f;
            const float right = left + width;
            const float top = 0.0f;
            const float bottom = top + height;
            const int x1 = juce::roundFloatToInt(left);
            const int x2 = juce::roundFloatToInt(right-1);
            const int y1 = juce::roundFloatToInt(top);
            const int y2 = juce::roundFloatToInt(bottom-1);

            g.setColour (Colour(0xff333333));
            g.drawHorizontalLine (y1, left, right);
            g.drawHorizontalLine (y2, left, right);
            if (!manager->isDocked (LEFT))
                g.drawVerticalLine (x1, top, bottom);
            if (!manager->isDocked (RIGHT))
                g.drawVerticalLine (x2, top, bottom);
        }
    }
    else
        if (orientation == TOP)
        {
            if (!isDocked())
            {
                const float left = 0.0f + button;
                const float right = left + (width-(button*2));
                const float top = 0.0f + height - padding;
                const float bottom = top + padding;
                const int y  = height - padding;
                const int x1 = button;
                const int x2 = width-(button+1);

                g.setColour (Colour(0xff333333));
                g.drawHorizontalLine (y, left, right);
                g.drawVerticalLine  (x1, top, bottom);
                g.drawVerticalLine  (x2, top, bottom);
            }
        }
        else
            if (orientation == LEFT)
            {
                {
                    const float left = 0.0f;
                    const float right = left + width;
                    const float top = 0.0f;
                    const float bottom = top + height;
                    const int x = 0;
                    const int y1 = 0;
                    const int y2 = height - 1;

                    g.setColour (Colour(0xff333333));
                    g.drawVerticalLine    (x, top, bottom);
                    g.drawHorizontalLine (y1, left, right);
                    g.drawHorizontalLine (y2, left, right);
                }
            }
            else
                if (orientation == RIGHT)
                {
                    {
                        const float left = 0.0f;
                        const float right = left + width;
                        const float top = 0.0f;
                        const float bottom = top + height;
                        const int x = width - 1;
                        const int y1 = 0;
                        const int y2 = height - 1;

                        g.setColour (Colour(0xff333333));
                        g.drawVerticalLine    (x, top, bottom);
                        g.drawHorizontalLine (y1, left, right);
                        g.drawHorizontalLine (y2, left, right);
                    }
                }
}
const juce::Rectangle<int> GUI::DockHolder::getContentBounds ()
{
    const int pad = PADDINGSIZE;
    const int width = getWidth();
    const int height = getHeight();

    switch (orientation)
    {
    case CENTER:
        {
            const int y = pad;
            const int h = height-(pad*2);
            int x = 0;
            int w = width-(x*2);
            if (!manager->isDocked (LEFT))
            {
                x += pad; 
                w -= pad;
            }
            if (!manager->isDocked (RIGHT))
            {
                w -= pad;
            }
            return RectangleInt (x, y, w, h);
        }
        break;
    case LEFT:
        {
            const int x = pad;
            const int y = pad;
            const int w = width-((pad*2)-1);
            const int h = height-(pad*2);
            return RectangleInt (x, y, w, h);
        }
        break;
    case RIGHT:
        {
            const int x = pad-1;
            const int y = pad;
            const int w = width-((pad*2)-1);
            const int h = height-(pad*2);
            return RectangleInt (x, y, w, h);
        }
        break;
    case TOP:
        {
            return RectangleInt (0, 0, width, height-pad);
        }
        break;
    default:
        {
            return RectangleInt (0, 0, width, height);
        }
        break;
    }
    return RectangleInt ();
}
void GUI::DockHolder::resized ()
{
    if (resizable)
        resizable->setBounds (0, 0, getWidth(), getHeight());
}
void GUI::DockHolder::mouseEnter (const MouseEvent & e)
{
    if(!lockAutomaticAnimation)
    {
        if (docked)
            return;
        setVisible (true);
        if (panel)
            panel->content->setVisible (true);
        inside = true;
    }
}
void GUI::DockHolder::mouseMove (const MouseEvent & e)
{
    manager->mousePropagation (e, orientation);
}
void GUI::DockHolder::mouseExit (const MouseEvent &e)
{
    if(!lockAutomaticAnimation)
    {
        const int x = e.getEventRelativeTo (this).x;
        const int y = e.getEventRelativeTo (this).y;
        const int w = getWidth ();
        const int h = getHeight ();

        if (!docked && open)
        {
            switch (orientation)
            {
            case TOP:
                if (y > h			&&
                    (x > 0			||
                    x < w))
                    open = false;
                break;
            case LEFT:
                if (x > w			||
                    y < 0			||
                    y > h)
                    open = false;
                break;
            case RIGHT:
                if (x < 0			||
                    y < 0			||
                    y > h)
                    open = false;
                break;
            }
        }
        if (!docked)
        {
            if (!open)
            {
                animator.fadeOut (this, FADEOUTMS);
                if (panel)
                    animator.fadeOut (panel->content, FADEOUTMS);
            }
        }
        else
        {
            if (inside)
            {
                animator.fadeOut (this, FADEOUTMS);
                if (panel)
                    animator.fadeOut (panel->content, FADEOUTMS);
            }
        }
        inside = false;
    }
}