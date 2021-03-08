#ifndef CUBE_H
#define CUBE_H

#include <SDL.h>

/**
 * @brief This class contains cubes used to path find, for rendering and for
 *        unit placement.
 */
class Cube
{
    public:
        SDL_Rect src, dst;
        int coordX, coordY, coordZ;
        int gCost, hCost, fCost, shortestPathDir;
        bool isVisited;
        bool isWall;
        bool isRendered;
        bool isHighlighted;

        Cube(int x, int y, int z, int id);

        /**
         * @brief Resets the pathfinding attributes (should only be used by
         *        Path.cpp).
         */
        void ResetCosts();

        /**
         * @brief Sets the id of the cube.
         *
         * @param Id: New id to assign to the cube.
         */
        void SetId(int id);

        /* Getters. */
        int GetId();

    private:
        int id;
};

#endif // CUBE_H
