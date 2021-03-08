#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>
#include "../Display/Display.h"
#include "../Display/Camera.h"
#include "../Textures/Cursor.h"
#include "../Controllers/Scene.h"
#include "../Entities/Player.h"

/**
 * @brief This parent class links rendering, user events and game actions
 *        together such as clicking on a button, resizing the window, etc.
 */
class Events
{
    public:
        Events();

        /**
         * @brief Handles all SDL events (mouse, keyboard and window events).
         *
         * @param display: Display object containing window and renderer
         *                 information.
         * @param event:   SDL_Event handle.
         * @param scene:   Scene to handle mouse events on.
         * @param player:  Player object containing saves and currency data.
         * @param camera:  Camera object containing position and zoom of the
         *                 screen.
         * @param cursor:  Cursor object that defines which cursor is being
         *                 used.
         */
        virtual void HandleEvents(Display &display, SDL_Event &event,
                                  Scene &scene, Player &player, Camera &camera,
                                  Cursor &cursor) = 0;
    protected:
        bool isInit;
        bool isTransitionFromDone;
        bool isTransitionToDone;
        double transitionTimer;
        double transitionRate;
        int opacityRate;
        int selectedHud;
        int selectedButton;
        bool isMouseButtonPressed;

        /*------------------ Pure virtual methods ---------------------------*/
        virtual void Init(Scene &scene) = 0;

        /**
         * @brief Executes actions based on window events (window movement,
         *        window resize, etc).
         */
        virtual void HandleWindowEvents(Display &display, SDL_Event &event,
                                        Scene &scene, Player &player,
                                        Camera &camera, Cursor &cursor) = 0;

        /**
         * @brief Executes actions based on keyboard events (key press, key
         *        release).
         */
        virtual void HandleKeyboardEvents(Display &display, SDL_Event &event,
                                          Scene &scene, Player &player,
                                          Camera &camera, Cursor &cursor) = 0;

        /**
         * @brief Executes actions based on mouse events (mouse movement,
         *        button press, button release, etc).
         */
        virtual void HandleMouseEvents(Display &display, SDL_Event &event,
                                       Scene &scene, Player &player,
                                       Camera &camera, Cursor &cursor) = 0;

        /**
         * @brief Repositions the HUDs, useful for when the window is resized.
         *
         * @param display: Display object containing window and renderer
         *                 information.
         * @param scene:   Scene to reposition the HUDs of.
         */
        virtual void RepositionHud(Display &display, Scene &scene) = 0;

        /*----------------------- Virtual methods ---------------------------*/
        /**
         * @brief Make the black screen transition dim until it becomes
         *        invisible.
         *
         * @param scene: Scene affected by the transition.
         *
         * @return True if the operation is completed, false otherwise.
         */
        virtual bool TransitionFromLastScene(Scene &scene);

        /**
         * @brief Increase the black screen transition opacity until it reaches
         *        255.
         *
         * @param scene: Scene affected by the transition.
         *
         * @return True if the operation is completed, false otherwise.
         */
        virtual bool TransitionToNextScene(Scene &scene);

        /**
         * @brief Checks which buttons are hovered in a scene and highlights
         *        them.
         *
         * @param renderer: Rendering target.
         * @param scene:    Scene to test the buttons from.
         * @param mouseX:   Coordinate of the mouse in x.
         * @param mouseY:   Coordinate of the mouse in y.
         * @param cursor:   Cursor object used to define the currently used
         *                  cursor.
         */
        virtual void HighlightHoveredButtons(SDL_Renderer *renderer,
                                             Scene &scene, int mouseX,
                                             int mouseY, Cursor &cursor);

        /**
         * @brief Get the id of the button pressed in a specific HUD.
         *
         * @param hud:    HUD to fetch the clicked button from.
         * @param mouseX: Coordinate of the mouse in x on click.
         * @param mouseY: Coordinate of the mouse in y on click.
         *
         * @return The id of the button in the HUD.
         */
        virtual int GetHudButtonPressed(std::shared_ptr<Hud> &hud, int mouseX,
                                        int mouseY);

        /**
         * @brief Get the id of the button pressed in a scene.
         *
         * @param scene:  Scene to fetch which button was pressed from.
         * @param mouseX: Coordinate of the mouse in x on click.
         * @param mouseY: Coordinate of the mouse in y on click.
         *
         * @return The id of the button in the scene.
         */
        virtual int GetButtonPressed(Scene &scene, int mouseX, int mouseY);

        /**
         * @brief Returns the id of the HUD that is being clicked on.
         *
         * @param scene:  Scene containing the HUD to test if they were
         *                clicked.
         * @param mouseX: Mouse position in x upon click.
         * @param mouseY: Mouse position in y upon click.
         *
         * @return The id of the HUD clicked on.
         */
        virtual int GetHudPressed(Scene &scene, int mouseX, int mouseY);

        /**
         * @brief Release all buttons that are in the pressed state.
         *
         * @param scene: Scene containing the buttons to release.
         */
        virtual void ReleaseButtons(Scene &scene);
};

#endif // EVENTS_H
