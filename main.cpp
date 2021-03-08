/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-1-20
 * Project: Tower Defense
 * File: main.cpp
 *
 * Project description:
 * This is a work in progress Tower Defense game.
 * It features algorithms such as the A* (A star) pathfinding algorithm for
 * units, unit targeting for towers, 2D rendering, level loading from files,
 * HUD interface and UI (buttons).
 *
 * The project is divided following the MVC (Model - View - Controller) way of
 * working. The View classes are contained within the "Hud" folder, the
 * Controller classes are contained within the "Controller" folder (except
 * (for the main) and the Model classes are located in every other folder.
 *
 * There is a Unit Tests folder where the unit tests are done. Testing is done
 * with the Catch library.
 */

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Display/Renderer.h"
#include "Controllers/Events.h"
#include "Controllers/GameEvents.h"
#include "Controllers/MenuEvents.h"
#include "Controllers/LevelSelectEvents.h"

/* Catch library configuration used for unit testing. */
#define CATCH_CONFIG_RUNNER
#include "~External Libraries/catch.hpp"

int main(int argc, char * argv[])
{
    int result = Catch::Session().run( argc, argv );

    Display display(1300, 700);
    display.Init();
    TTF_Init();

    /*
     * This will have a different implementation in the future so that we don't
     * need to create 3 different objects, but only one event object.
     */
    GameEvents events;
    MenuEvents mevents;
    LevelSelectEvents levents;

    Renderer renderer;
    Camera camera;
    Player player;
    Cursor cursor;

    Scene scene(display.renderer, SCENE_MAIN_MENU, display.GetWinLength(),
                display.GetWinHeight());

    /* Temporary implementation of a star background (this will be moved). */
    SDL_Rect starsRect = {0, 0, 1920, 1080};
    SDL_Surface *surf = IMG_Load("stars.png");
    SDL_Texture *text = SDL_CreateTextureFromSurface(display.renderer, surf);
    if(surf == nullptr)
    {
        std::cout << SDL_GetError() << " L: " << __LINE__ << " F " << __FILE__
                  << "\n";
    }
    else
    {
        SDL_FreeSurface(surf);
    }

    if(text == nullptr)
    {
        std::cout << SDL_GetError() << " L: " << __LINE__ << " F " << __FILE__
                  << "\n";
    }

    /* Game loop. */
    SDL_Event event;
    while(true)
    {
        SDL_Delay(renderer.renderDelay);
        SDL_PollEvent(&event);

        /* Clear screen. */
        SDL_RenderClear(display.renderer);

        /* Handle events. */
        switch(scene.sceneId)
        {
        case SCENE_LEVEL:
            events.HandleEvents(display, event, scene, player, camera, cursor);
            break;
        case SCENE_MAIN_MENU:
            mevents.HandleEvents(display, event, scene, player, camera,
                                 cursor);
            break;
        case SCENE_LEVEL_SELECTION:
            levents.HandleEvents(display, event, scene, player, camera,
                                 cursor);
            break;
        case SCENE_SETTINGS:
            /* Not implemented yet. */
            break;
        }

        /* Render everything. */
        SDL_RenderCopy(display.renderer, text, &starsRect, &starsRect);

        if(scene.sceneId == SCENE_LEVEL)
        {
            renderer.RenderLevel(display.renderer, camera, scene.level,
                                 scene.textures);
        }

        renderer.RenderSceneHud(display, scene, scene.textures);

        SDL_RenderPresent(display.renderer);
    }

    return result;
}
