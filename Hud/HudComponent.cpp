/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-03
 * Project: Tower Defense
 * File: HudComponent.cpp
 *
 * Brief: This parent class stores basic HUD component information such as
 *        rendering destination, borders, opacity and such.
 */

#include "HudComponent.h"

HudComponent::HudComponent()
{
    moveTimerBegin = 0.0;
    isInMovement = false;
}

/*
 * Moves a HUD component from point A to point B in a specific amount of time.
 */
bool HudComponent::MoveComponent(SDL_Rect src, SDL_Rect dst,
                                 double timeInterval)
{
    bool isOperationDone = false;

    /* Initialize operation and make sure that there is no division by zero. */
    if(!isInMovement && timeInterval != 0)
    {
        moveTimerBegin = SDL_GetTicks();
        isInMovement = true;
    }

    /* Move the HUD component. */
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
    }

    return isOperationDone;
}

/*
 * Saves a rendering destination.
 */
void HudComponent::SaveDst()
{
    savedDst.x = dst.x;
    savedDst.y = dst.y;
    savedDst.w = dst.w;
    savedDst.h = dst.h;
}
