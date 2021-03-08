/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-01-22
 * Project: Tower Defense
 * File: Events.cpp
 *
 * Brief: This class implements the Events class, which is a controller parent
 *        class. This class links user events to game actions such as
 *        clicking on a button, resizing the window, etc.
 */

#include "Events.h"

Events::Events()
{
    isInit = false;
    isTransitionFromDone = true;
    isTransitionToDone = true;
    transitionTimer = 0.0;
    transitionRate = 10.0;
    opacityRate = 5;
    selectedHud = -1;
    selectedButton = -1;
    isMouseButtonPressed = false;
}

/*
 * Make the black screen transition dim until it becomes invisible.
 */
bool Events::TransitionFromLastScene(Scene &scene)
{
    bool retval = true;
    scene.isTransitionDone = false;

    if(!isTransitionFromDone)
    {
        retval = false;

        if(SDL_GetTicks() - transitionTimer > transitionRate)
        {
            /* Dim the black screen. */
            scene.opacity -= opacityRate;

            if(scene.opacity <= 0)
            {
                isTransitionFromDone = true;
                scene.isTransitionDone = true;
                retval = true;
            }

            /* Update the transition timer. */
            transitionTimer = SDL_GetTicks();
        }
    }

    return retval;
}

/*
 * Increase the black screen transition opacity until it reaches 255.
 */
bool Events::TransitionToNextScene(Scene &scene)
{
    bool retval = true;
    scene.isTransitionDone = false;

    if(!isTransitionToDone)
    {
        retval = false;

        if(SDL_GetTicks() - transitionTimer > transitionRate)
        {
            /* Increase black screen opacity. */
            scene.opacity += opacityRate;

            if(scene.opacity >= 255)
            {
                isTransitionToDone = true;
                retval = true;
            }

            /* Update transition timer. */
            transitionTimer = SDL_GetTicks();
        }
    }

    return retval;
}

/*
 * Checks which buttons are hovered in a scene and highlights them.
 */
void Events::HighlightHoveredButtons(SDL_Renderer *renderer, Scene &scene,
                                     int mouseX, int mouseY, Cursor &cursor)
{
    bool val = false;
    bool cur = false;

    for(auto &i : scene.hud)
    {
        for(auto &j : i.second->buttons)
        {
            /* Test if mouse coordinates are over a button. */
            if(j.isVisible)
            {
                val = j.IsMouseOnButton(mouseX, mouseY, i.second->dst.x
                                        + j.dst.x, i.second->dst.y + j.dst.y);
                if(val && j.isHighlightable)
                {
                    cur = true;
                    j.isHovered = true;

                    /* This needs to be made a member of Button. */
                    j.borderColor = {0,120,200, 200};
                }
                else
                {
                    j.isHovered = false;

                    /* This too. */
                    j.borderColor = {200,0,122, 132};
                }
            }
        }
    }

    /*
     * Update the cursor to show a hand if hovering a button that can be
     * clicked.
     */
    if(cur)
    {
        SDL_SetCursor(cursor.cursor[1]);
    }
    else
    {
        SDL_SetCursor(cursor.cursor[0]);
    }
}

/*
 * Get the id of the button pressed in a scene.
 */
int Events::GetButtonPressed(Scene &scene, int mouseX, int mouseY)
{
    int k = -1;
    int selectedButton = -1;

    for(auto &i : scene.hud)
    {
        for(auto &j : i.second->buttons)
        {
            if(j.isVisible)
            {
                k++;
                if(j.IsMouseOnButton(mouseX,
                                     mouseY,
                                     i.second->dst.x + j.dst.x,
                                     i.second->dst.y + j.dst.y))
                {
                    j.Press();
                    selectedButton = k;
                    break;
                }
            }
        }
    }

    return selectedButton;
}

/*
 * Get the id of the button pressed in a specific HUD.
 */
int Events::GetHudButtonPressed(std::shared_ptr<Hud> &hud, int mouseX,
                                int mouseY)
{
    int j = -1;
    int selectedButton = -1;

    for(auto &i : hud->buttons)
    {
        if(i.isVisible)
        {
            j++;
            if(i.IsMouseOnButton(mouseX, mouseY,
                                 hud->dst.x + i.dst.x, hud->dst.y + i.dst.y))
            {
                i.Press();
                selectedButton = j;
                break;
            }
        }
    }

    return selectedButton;
}

/*
 * Returns the id of the HUD that is being clicked on.
 */
int Events::GetHudPressed(Scene &scene, int mouseX, int mouseY)
{
    int selectedHud = -1;

    for(const auto &i : scene.hud)
    {
        if(mouseX > i.second->dst.x && mouseX < i.second->dst.x
           + i.second->dst.w
           && mouseY > i.second->dst.y && mouseY < i.second->dst.y
           + i.second->dst.h)
        {
            selectedHud = i.first;
        }
    }

    return selectedHud;
}

/*
 * Release all buttons that are in the pressed state.
 */
void Events::ReleaseButtons(Scene &scene)
{
    for(auto &i : scene.hud)
    {
        for(auto &j : i.second->buttons)
        {
            j.Release();
        }
    }
}
