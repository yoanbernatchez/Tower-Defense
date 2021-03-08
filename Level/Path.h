#ifndef PATH_H
#define PATH_H

#include <vector>
#include "Cube.h"

/**
 * @brief Constants for all the possible directions in which an adjacent tile
 *        can be.
 */
enum DIRECTION{DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_UP, DIRECTION_DOWN,
               DIRECTION_MIDDLE};

/**
 * @brief This class gives you the method findPath to find a path between
 *        two points if the path exists and stores it into a vector.
 */
class Path
{
    public:
        /**
         * @return The vector containing the directions of the path.
         */
        std::vector<int> &GetDirections();

        /**
         * @brief When called, uses A* (A star) algorithm to find the shortest
         *        path from the starting point to the ending point and stores
         *        the path in the directions vector.
         *
         * @param startingPointX: Coordinate in X where the path begins.
         * @param startingPointY: Coordinate in Y where the path begins.
         * @param endingPointX:   Coordinate in X where the path ends.
         * @param endingPointY:   Coordinate in Y where the path ends.
         * @param cubes:          Vector of cubes the extract the path from.
         *
         * @return True if path is found, false otherwise.
         *
         * @note All case scenarios have been unit tested. This function is
         *       also somewhat benchmarked.
         */
        bool FindPath(int startingPointX, int startingPointY,
                      int endingPointX, int endingPointY,
                      std::vector<Cube> &cubes);
        /**
         * @brief Empties out the data in the directions vector.
         */
        void DeletePath();

    private:
        std::vector<int> directions;
};

#endif // PATH_H
