/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-01
 * Project: Tower Defense
 * File: Cursor.cpp
 *
 * Brief: This source file contains a class that loads different cursors in,
 *        which can be used to change the mouse cursor, such as turning the
 *        mouse cursor to a hand when hovering a button.
 */

#include "Cursor.h"
#include <iostream>

/*
 * Loads the different cursor textures required.
 */
Cursor::Cursor()
{
    SDL_Cursor *tempCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

    if(tempCursor == nullptr)
    {
        std::cout << SDL_GetError() << "\n";
    }

    cursor.push_back(tempCursor);

    tempCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

    if(tempCursor == nullptr)
    {
        std::cout << SDL_GetError() << "\n";
    }

    cursor.push_back(tempCursor);
}

/*
 * Frees all the cursor textures previously allocated.
 */
Cursor::~Cursor()
{
    for(auto &i : cursor)
    {
        SDL_FreeCursor(i);
    }
}
