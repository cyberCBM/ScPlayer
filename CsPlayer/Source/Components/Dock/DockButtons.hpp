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

#ifndef hpp_cpp_Dockbutton_cpp_hpp
#define hpp_cpp_Dockbutton_cpp_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"

#define BUTTONSIZE 15
#define PADDINGSIZE 3
#define FADEOUTMS 180
#define TOP		0
#define BOTTOM	1
#define LEFT	2
#define RIGHT	3
#define CENTER	4
#define ZORDER_CENTER			0
#define ZORDER_LEFT				1
#define ZORDER_RIGHT			2
#define ZORDER_LEFT_BUTTON		3
#define ZORDER_RIGHT_BUTTON		4
#define ZORDER_TOP				5
#define ZORDER_BOTTOM			6
#define ZORDER_TOP_BUTTON		7
#define ZORDER_BOTTOM_BUTTON	8

namespace GUI 
{
    static DrawablePath * getDockablePath (const int type, const bool on, const bool over)
    {
        DrawablePath * drawable = new DrawablePath ();

        Path path;
        switch (type)
        {
        case TOP:
            if (on)
            {
                for (int i = 0; i < 5; ++i)
                {
                    Line<float> line (0.0f+(0.1f*i), 0.0f+(0.2f*i), 1.0f-(0.1f*i), 0.0f+(0.2f*i));
                    path.addLineSegment (line, 0.05f);
                }
            }
            else
                path.addTriangle (0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f);
            break;

        case LEFT:
            if (on)
            {
                for (int i = 0; i < 5; ++i)
                {
                    Line<float> line (0.0f+(0.2f*i), 0.0f+(0.1f*i), 0.0f+(0.2f*i), 1.0f-(0.1f*i));
                    path.addLineSegment (line, 0.05f);
                }
            }
            else
                path.addTriangle (0.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f);
            break;

        case RIGHT:
            if (on)
            {
                for (int i = 0; i < 5; ++i)
                {
                    Line<float> line (1.0f-(0.2f*i), 0.0f+(0.1f*i), 1.0f-(0.2f*i), 1.0f-(0.1f*i));
                    path.addLineSegment (line, 0.05f);
                }
            }
            else
                path.addTriangle (0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f);
            break;

        case BOTTOM:
            if (on)
            {
                for (int i = 0; i < 5; ++i)
                {
                    Line<float> line (0.0f+(0.1f*i), 1.0f-(0.2f*i), 1.0f-(0.1f*i), 1.0f-(0.2f*i));
                    path.addLineSegment (line, 0.05f);
                }
            }
            else
                path.addTriangle (0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f);
            break;
        };
        drawable->setPath (path);

        if (on)
        {
            if (over)
                drawable->setFill (FillType (Colour(0xffcccccc)));
            else
                drawable->setFill (FillType (Colour(0xff999999)));
        }
        else
        {
            if (over)
                drawable->setFill (FillType (Colour(0xff999999)));
            else
                drawable->setFill (FillType (Colour(0xff4c4c4c)));
        }
        return drawable;
    }
    static DrawableButton * getDockableButton (const String& name, const int type)
    {
        DrawableButton * const button = new DrawableButton (name, DrawableButton::ImageFitted);

        Drawable * normalImage, * overImage, * downImage, * disabledImage;
        Drawable * normalImageOn, * overImageOn, * downImageOn, * disabledImageOn;

        switch (type)
        {
        case TOP:
            normalImage = getDockablePath (TOP, false, false);
            overImage = getDockablePath (TOP, false, true);
            normalImageOn = getDockablePath (TOP, true, false);
            overImageOn = getDockablePath (TOP, true, true);
            break;
        case LEFT:
            normalImage = getDockablePath (LEFT, false, false);
            overImage = getDockablePath (LEFT, false, true);
            normalImageOn = getDockablePath (LEFT, true, false);
            overImageOn = getDockablePath (LEFT, true, true);
            break;
        case RIGHT:
            normalImage = getDockablePath (RIGHT, false, false);
            overImage = getDockablePath (RIGHT, false, true);
            normalImageOn = getDockablePath (RIGHT, true, false);
            overImageOn = getDockablePath (RIGHT, true, true);
            break;
        case BOTTOM:
            normalImage = getDockablePath (BOTTOM, false, false);
            overImage = getDockablePath (BOTTOM, false, true);
            normalImageOn = getDockablePath (BOTTOM, true, false);
            overImageOn = getDockablePath (BOTTOM, true, true);
            break;
        };

        downImage = 0; downImageOn = 0;
        disabledImage = 0; disabledImageOn = 0;

        button->setImages (normalImage, overImage, downImage, disabledImage,
            normalImageOn, overImageOn, downImageOn, disabledImageOn);

        delete normalImage; delete normalImageOn;
        delete overImage; delete overImageOn;
        delete downImage; delete downImageOn;
        delete disabledImage; delete disabledImageOn;

        return button;
    }
}
#endif // hpp_cpp_Dockbutton_cpp_hpp