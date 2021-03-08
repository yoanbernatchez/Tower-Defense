#ifndef UNIT_H
#define UNIT_H

#include "Entities.h"
#include "../Level/Path.h"

/**
 * @brief This class implements units (enemies) that can find a path that they
 *        can walk on.
 */
class Unit : public Entities
{
    public:
        Path path;
        int hp;
        int movSpeed;
        int goldValue;
        int spawnTime;
        float x;
        float y;
        bool isVisible;

        Unit(int id, int hp, int movSpeed, int goldValue, int spawnTime);

        /**
         * @brief Finds a path between two points (if the path exists) and
         *        assigns it to the unit.
         *
         * @param startingPointX: Starting coordinate of the path in x.
         * @param startingPointY: Starting coordinate of the path in y.
         * @param endingPointX:   Ending coordinate of the path in x.
         * @param endingPointY:   Ending coordinate of the path in x.
         * @param cubes:          Vector of cubes used to find a path.
         */
        void GetPath(int startingPointX, int startingPointY, int endingPointX,
                     int endingPointY, std::vector<Cube> &cubes);

        /**
         * @brief Checks if a path exists between two points without assigning
         *        it to the unit.
         *
         * @param startingPointX: Starting coordinate of the path in x.
         * @param startingPointY: Starting coordinate of the path in y.
         * @param endingPointX:   Ending coordinate of the path in x.
         * @param endingPointY:   Ending coordinate of the path in x.
         * @param cubes:          Vector of cubes used to find a path.
         *
         * @return True if path exists, false otherwise.
         */
        bool TestPath(int startingPointX, int startingPointY, int endingPointX,
                      int endingPointY, std::vector<Cube> &cubes);

        /**
         * @brief Makes the unit move in a direction.
         *
         * @param direction:  Direction to walk in.
         * @param cubeLength: Length of a cube.
         */
        void Walk(int directionType, int cubeLength);

        /**
         * @brief Makes the unit move with the directions of its path.
         *
         * @param cubeLength: Length of a cube.
         */
        void WalkWithPath(int cubeLength);

    private:
        bool isNewPath;
        bool isInNewCube;
        int quadrant;
        int direction;
};

#endif // UNIT_H
