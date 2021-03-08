#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL.h>

/**
 * @brief Possible window display modes for the SDL window.
 */
enum WINDOW_MODE{WINDOW_RESIZABLE, WINDOW_FULLSCREEN};

/**
 * @brief This class implements a window and renderer as well as methods to
 *        manipulate the window and to initialize SDL.
 */
class Display
{
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;

        Display(int winLength, int winHeight);

        /**
         * @brief Free memory.
         */
        virtual ~Display();

        /**
         * @brief Initializes the SDL systems, window and renderer. Exits
         *        program on failure.
         */
        void Init();

        /**
         * @brief Sets the display mode for the game window such as resizable
         *        and fullscreen.
         *
         * @param winMode: The new display mode for the game window.
         */
        void SetWindowDisplayMode(WINDOW_MODE winMode);

        /**
         * @brief Updates the window's length and height. Doesn't actually
         *        interact with the window, simply saves the new length and
         *        height in variables.
         *
         * @param winLength: New window length.
         * @param winHeight: New window height.
         *
         * @return True on success, false if winLength or winHeight is
         *         negative.
         */
        bool UpdateWindowSize(int winLength, int winHeight);

        /**
         * @brief Sets a new minimum size for the game window.
         *
         * @param minLength: New minimum length for the window.
         * @param minHeight: New minimum height for the window.
         *
         * @return True on success, false if minLength or minHeight is
         *         negative.
         */
        bool SetWindowMinSize(int minLength, int minHeight);

        /* Getters. */
        int GetWinLength();
        int GetWinHeight();
        int GetWinMinLength();
        int GetWinMinHeight();

    private:
        std::string winName;
        int winLength;
        int winHeight;
        int winMinLength;
        int winMinHeight;
};

#endif // DISPLAY_H
