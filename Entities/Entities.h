#ifndef ENTITIES_H
#define ENTITIES_H

#include <string>
#include <SDL.h>

/**
 * [NOT COMPLETE]
 * @brief This class implements the Entities parent class.
 */
class Entities
{
    public:
        std::string name;
        int cubeX;
        int cubeY;
        int id;
        int frame;
        bool isRendered;
        int orientation;
        SDL_Rect src, dst;
};

#endif // ENTITIES_H
