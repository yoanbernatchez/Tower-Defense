/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-03
 * Project: Tower Defense
 * File: Hud.cpp
 *
 * Brief: This class is a container containing HUD components.
 */

#include "Hud.h"
#include "../Template Helpers/THudCompHelper.h"
#include <iostream>

Hud::Hud(SDL_Rect dst, bool hasBorder, SDL_Color borderColor, int borderSize,
         bool hasBackground, SDL_Color backgroundColor)
{
    SetDst(dst.x, dst.y, dst.w, dst.h);
    isVisible = true;

    moveTimerBegin = 0.0;
    isInMovement = false;

    this->hasBorder = hasBorder;
    this->borderColor.r = borderColor.r;
    this->borderColor.g = borderColor.g;
    this->borderColor.b = borderColor.b;
    this->borderColor.a = borderColor.a;
    this->borderSize = borderSize;

    this->hasBackground = hasBackground;
    this->backgroundColor.r = backgroundColor.r;
    this->backgroundColor.g = backgroundColor.g;
    this->backgroundColor.b = backgroundColor.b;
    this->backgroundColor.a = backgroundColor.a;
}

/*
 * Sets the destination on screen of the HUD.
 */
void Hud::SetDst(int x, int y, int w, int h)
{
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
}

/*
 * Adds a text component to the HUD.
 */
void Hud::AddText(SDL_Renderer *renderer, std::string text, int fontSize,
                     SDL_Color color, FONT fontName)
{
    std::shared_ptr<Text> tempText(new Text(renderer, text, fontSize, color,
                                            fontName));
    texts.push_back(std::move(tempText));
}

/*
 * Adds an image to the HUD.
 */
void Hud::AddImage(int imgId, int x, int y, int w, int h)
{
    Image tempImage(imgId, x, y, w, h);
    images.push_back(tempImage);
}

/*
 * Adds an image to the HUD.
 */
void Hud::AddImage(int imgId, int x, int y)
{
    Image tempImage(imgId, x, y);
    images.push_back(tempImage);
}

/*
 * Removes a component by index from the HUD.
 */
void Hud::RemoveComponentAtIndex(HUD_COMPONENT_TYPE type, unsigned int index)
{
    switch(type)
    {
    case COMPONENT_BUTTON:
        HudCompHelper::RemoveComponentAtIndex(buttons, index);
        break;
    case COMPONENT_TEXT:
        HudCompHelper::RemoveComponentAtIndex(texts, index);
        break;
    case COMPONENT_PORTRAIT:
        /* To be implemented. */
        break;
    }
}

/*
 * Move the HUD from point A to point B in a defined time frame.
 */
bool Hud::MoveComponent(SDL_Rect src, SDL_Rect dst, double timeInterval)
{
    bool isOperationDone = false;

    /* Initialize operation and make sure that there is no division by zero. */
    if(!isInMovement && timeInterval != 0)
    {
        moveTimerBegin = SDL_GetTicks();
        isInMovement = true;
    }

    if(isInMovement)
    {
        double progress = (SDL_GetTicks() - moveTimerBegin) / timeInterval;

        /* Move the component. */
        this->dst.x = dst.x + (1.0 - progress) * abs(src.x - dst.x);
        this->dst.y = dst.y + (1.0 - progress) * abs(src.y - dst.y);

        /* Conclude operation, once progress has reached 100%. */
        if(progress >= 1.0)
        {
            progress = 1.0;
            isInMovement = false;
            isOperationDone = true;
        }

        std::cout << progress << "%\n";
    }

    return isOperationDone;
}

/* [Deprecated]
void Hud::AddPortraitWidget(Entities *entity, int borderSize,
                            SDL_Color borderColor,
                            SDL_Color backgroundColor, int w, int h)
{
    std::shared_ptr<PortraitWidget>
    tempWidget(new PortraitWidget(entity, borderSize, borderColor,
                                  backgroundColor, w, h));
    portraitWidgets.push_back(std::move(tempWidget));
}
*/

/* [Deprecated]
void Hud::RemoveComponentByLabel(HUD_COMPONENT_TYPE type, std::string label)
{
    switch(type)
    {
    case COMPONENT_BUTTON:
        HudCompHelper::RemoveComponentByLabel(buttons, label);
        break;
    case COMPONENT_TEXT:
        HudCompHelper::RemoveComponentByLabel(texts, label);
        break;
    case COMPONENT_PORTRAIT:
        // To be implemented.
        break;
    }
}
*/
