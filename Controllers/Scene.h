#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <memory>
#include "Hud/Hud.h"
#include "Level/Level.h"
#include "Textures/Textures.h"

/**
 * @brief Contains all the different HUDs in the Main Menu scene.
 */
enum HUD_PRESETS_MENU{HUD_BUTTONS};

/**
 * @brief Contains all the different HUDs in the Level Selection scene.
 */
enum HUD_PRESETS_LEVEL_SELECT{HUD_PLANET, HUD_PLANET_INFO, HUD_ZONE1,
                              HUD_ZONE2};

/**
 * @brief Contains all the different HUDs in the Level (game) scene.
 */
enum HUD_PRESETS_LEVEL{HUD_INFO, HUD_TOWER, HUD_COMS, HUD_STATUS, HUD_WAVE,
                       HUD_ERROR};

/**
 * @brief Enumeration of all the possible scenes in the game.
 */
enum SCENE{SCENE_MAIN_MENU, SCENE_SETTINGS, SCENE_LEVEL_SELECTION,
           SCENE_LEVEL};


/**
 * @brief This class implements the Scene class, which acts as a container
 *        for graphical and level data.
 */
class Scene
{
    public:
        SCENE sceneId;
        Level level;
        std::map<const int, std::shared_ptr<Hud>> hud;
        Textures textures;
        int opacity;
        bool isTransitionDone;

        Scene(SDL_Renderer *renderer, SCENE sceneId, int winSizeX,
              int winSizeY);

        /**
         * @brief Loads a scene preset.
         *
         * @param renderer: Rendering target.
         * @param sceneId:  Id of the scene to load.
         * @param winSizeX: Size of the application window in x.
         * @param winSizeY: Size of the application window in y.
         */
        void LoadScenePreset(SDL_Renderer *renderer, SCENE sceneId,
                             int winSizeX, int winSizeY);

    private:
        /**
         * @brief Loads the Main Menu scene presets.
         *
         * @param renderer: Rendering target.
         * @param winSizeX: Size of the application window in x.
         * @param winSizeY: Size of the application window in y.
         */
        void LoadSceneMainMenu(SDL_Renderer *renderer, int winSizeX,
                               int winSizeY);

        /**
         * @brief Loads the Level Selection scene presets.
         *
         * @param renderer: Rendering target.
         * @param winSizeX: Size of the application window in x.
         * @param winSizeY: Size of the application window in y.
         */
        void LoadSceneLevelSelection(SDL_Renderer *renderer, int winSizeX,
                                     int winSizeY);

        /**
         * @brief Loads the Level scene presets.
         *
         * @param renderer: Rendering target.
         * @param winSizeX: Size of the application window in x.
         * @param winSizeY: Size of the application window in y.
         */
        void LoadSceneLevel(SDL_Renderer *renderer, int winSizeX,
                            int winSizeY);
};

#endif // SCENE_H
