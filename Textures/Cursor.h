#ifndef CURSOR_H
#define CURSOR_H

#include <vector>
#include <SDL.h>

/**
 * @brief The different cursors that can be used.
 */
enum CURSOR{CURSOR_ARROW, CURSOR_HAND};

/**
 * @brief This class loads all the required cursors that can be used in the
 *        project.
 */
class Cursor
{
    public:
        std::vector<SDL_Cursor*> cursor;

        /**
         * @brief Loads the different cursor textures required.
         */
        Cursor();

        /**
         * @brief Frees all the cursor textures previously allocated.
         */
        virtual ~Cursor();
};

#endif // CURSOR_H
