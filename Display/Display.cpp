/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-05
 * Project: Tower Defense
 * File: Display.cpp
 *
 * Brief: This class implements a Display class, containing a window and
 *        renderer as well as methods to manipulate the window and to
 *        initialize SDL.
 */

#include "Display.h"
#include <iostream>
#include <SDL_image.h>

Display::Display(int winLength, int winHeight)
{
    winMinLength = 1300;
    winMinHeight = 700;

    if(winLength > winMinLength)
    {
        this->winLength = winLength;
    }
    else
    {
        this->winLength = winMinLength;
    }

    if(winHeight > winMinHeight)
    {
        this->winHeight = winHeight;
    }
    else
    {
        this->winHeight = winMinHeight;
    }

    winName = "Tower Defense";
}

/*
 * Initializes the SDL systems, window and renderer. Exits program on failure.
 */
void Display::Init()
{
    /* Initialize SDL main system and subsystems. */
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Unable to initialize SDL: " << SDL_GetError() << "\n";
        exit(1000);
    }

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "Unable to initialize SDL_image: " << SDL_GetError()
                  << "\n";
        exit(1001);
    }

    /* Create window, renderer and check if they are initialized properly. */
    SDL_CreateWindowAndRenderer(winLength, winHeight, SDL_WINDOW_RESIZABLE,
                                &window, &renderer);

    if(window == nullptr)
    {
        std::cout << "Unable to initialize SDL_Window: " << SDL_GetError()
                  << "\n";
        exit(1002);
    }

    if(renderer == nullptr)
    {
        std::cout << "Unable to initialize SDL_Renderer: " << SDL_GetError()
                  << "\n";
        exit(1003);
    }

    SDL_SetWindowMinimumSize(window, winMinLength, winMinHeight);
}

/*
 * Sets the display mode for the game window such as resizable and fullscreen.
 */
void Display::SetWindowDisplayMode(WINDOW_MODE winMode)
{
    switch(winMode)
    {
    case WINDOW_RESIZABLE:
        SDL_SetWindowResizable(window, SDL_TRUE);
        break;
    case WINDOW_FULLSCREEN:
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        break;
    }
}

/*
 * Updates the window's length and height. Doesn't actually interact with the
 * window, simply saves the new length and height in variables.
 */
bool Display::UpdateWindowSize(int winLength, int winHeight)
{
    bool isWindowSizeUpdated = false;

    if(winLength >= 0 && winHeight >= 0)
    {
        this->winLength = winLength;
        this->winHeight = winHeight;
        isWindowSizeUpdated = true;
    }

    return isWindowSizeUpdated;
}

/*
 * Sets a new minimum size for the game window.
 */
bool Display::SetWindowMinSize(int minLength, int minHeight)
{
    bool isMinSizeChanged = false;

    if(minLength >= 0 && minHeight >= 0)
    {
        winMinLength = minLength;
        winMinHeight = minHeight;
        SDL_SetWindowMinimumSize(window, winMinLength, winMinHeight);
        isMinSizeChanged = true;
    }

    return isMinSizeChanged;
}

int Display::GetWinLength() { return winLength; }

int Display::GetWinHeight() { return winHeight; }

int Display::GetWinMinLength() { return winMinLength; }

int Display::GetWinMinHeight() { return winMinHeight; }

/*
 * Free memory.
 */
Display::~Display()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
