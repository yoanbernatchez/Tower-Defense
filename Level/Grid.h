#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cube.h"

/**
 * @brief This class contains an implementation of a grid containing cubes.
 */
class Grid
{
    public:
        std::vector<Cube> cubes;

        Grid();

        /**
         * @brief Adds a cube to the grid at the specified coordinates.
         *
         * @param x:  Coordinates of the cube in x.
         * @param y:  Coordinates of the cube in y.
         * @param z:  Coordinates of the cube in z.
         * @param id: Id of the cube.
         */
        void AddCube(int x, int y, int z, int id);

        /**
         * @brief Moves a cube to the specified coordinates.
         *
         * @param cube: Cube to move.
         * @param x:    Coordinate in x where to move the cube.
         * @param y:    Coordinate in y where to move the cube.
         * @param z:    Coordinate in z where to move the cube.
         */
        void MoveCube(Cube cube, int x, int y, int z);

        /**
         * @brief Finds if there is a cube at the x and y coordinates and
         *        returns it.
         *
         * @param x: Coordinate of the cube to find in x.
         * @param y: Coordinate of the cube to find in y.
         *
         * @return Point to the cube found.
         */
        Cube *GetCubeByCoord(int x, int y);

        /**
         * @brief Calculates the lowest row + column between all cubes
         *        (used for rendering).
         */
        void CalculateLowestRowPlusCol();

        int GetLowestRowPlusCol();

    private:
        int lowestRowPlusCol;
};

#endif // GRID_H
