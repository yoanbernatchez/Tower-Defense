/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-01-29
 * File: Path.cpp
 * Unit test file: TestPath.cpp
 *
 * This class is part of a Tower Defense game project and has dependencies with
 * other classes. If you are interested in seeing the game and the pathfinding
 * in action, contact me at yoan_bernatchez@hotmail.com
 *
 * This source file provides the user with a way to find a path between open
 * spaces and walls.
 * More precisely, when called, the findPath function finds a path
 * (when possible) by performing the A* (A star) pathfinding algorithm.
 * This algorithm promises to find the shortest path every time and is rather
 * quickly executed.
 *
 * Benchmark tests:
 * Material: AMD Ryzen 5 1600X
 * Test case 1 => Non-obstructed 5 steps path (executed 100 000 times)
 * Result: ~45ms (0.045s)
 * Todo: make more benchmark tests
 */

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "Path.h"

/**
 * @brief Returns a reference to the cube associated with the (x, y)
 *        coordinates.
 *
 * @param coordX: Coordinate in x of the cube to find.
 * @param coordY: Coordinate in y of the cube to find.
 * @param cubes:  Reference of cube vector.
 *
 * @return Pointer containing a reference to a cube or nullptr if no cube
 *         exist at the specified coordinates.
 */
static Cube *FindCube(const int coordX, const int coordY,
                      std::vector<Cube> &cubes);

/**
 * @brief Returns a reference to the next cube to process.
 *
 * @param startingPointX: Coordinate of the point in X from where we find the
 *                        next cube to process.
 * @param startingPointY: Coordinate of the point in Y from where we find the
 *                        next cube to process.
 *
 * @return Pointer to the next cube with the lowest fCost and hCost.
 */
static Cube *GetNextCube(const int startingPointX, const int startingPointY,
                         std::vector<Cube> &cubes);

/**
 * @brief Propagates to the next adjacent cubes (gives the adjacent cubes a
 *        gCost, hCost and fCost).
 *
 * @param startingPointX: Coordinate in X where the path begins.
 * @param startingPointY: Coordinate in Y where the path begins.
 * @param endingPointX:   Coordinate in X where the path ends.
 * @param endingPointY:   Coordinate in Y where the path ends.
 * @param cube:           Cube to propagate from.
 * @param cubes:          Vector containing all the possible cubes to propagate
 *                        to.
 */
static void Propagate(const int startingPointX, const int startingPointY,
                      const int endingPointX, const int endingPointY,
                      Cube *cube, std::vector<Cube> &cubes);

/**
 * @brief This function traces the path according to the child/parent relation
 *        of each cube. Path is traced from the ending point to the starting
 *        point, then reversed.
 *
 * @param startingPointX: Coordinate in X where the path begins.
 * @param startingPointY: Coordinate in Y where the path begins.
 * @param endingPointX:   Coordinate in X where the path ends.
 * @param endingPointY:   Coordinate in Y where the path ends.
 * @param cubes:          Cube vector to get the path from.
 * @param directions:     The path. Vector where we store the directions.
 */
static void CreatePath(const int startingPointX, const int startingPointY,
                       const int endingPointX, const int endingPointY,
                       std::vector<Cube> &cubes, std::vector<int> &directions);

/**
 * @brief Simple function to reverse the directions of a path.
 *        LEFT becomes RIGHT, vice versa. UP becomes DOWN, vice versa.
 */
static void ReversePath(std::vector<int> &directions);

/*
 * Finds a path between a starting point and an ending point.
 * Returns true if path is found, false otherwise.
 */
bool Path::FindPath(int startingPointX, int startingPointY,
                    int endingPointX, int endingPointY,
                    std::vector<Cube> &cubes)
{
    bool isPathFound = false;

    /* Make sure that we delete any preexisting path. */
    DeletePath();

    Cube *cube;
    cube = FindCube(startingPointX, startingPointY, cubes);

    /* Check if the startingPoint is valid. */
    if(cube == nullptr || cube->isWall)
    {
        return false;
    }
    else
    {
        cube->fCost = 0;
    }

    for(;;)
    {
        /* We propagate values to the adjacent cubes. */
        Propagate(startingPointX, startingPointY,
                  endingPointX, endingPointY,
                  cube, cubes);

        /* Then we find the next cube to be the propagator. */
        cube = GetNextCube(startingPointX, startingPointY, cubes);

        if(cube != nullptr)
        {
            cube->isVisited = true;
        }

        /* Check if the ending point has been found. */
        if(cube != nullptr &&
           cube->coordX == endingPointX && cube->coordY == endingPointY &&
           cube->isVisited)
        {
            for(auto &i : cubes)
            {
                i.isVisited = false;
            }

            /* If so, go ahead and create path.*/
            CreatePath(startingPointX, startingPointY,
                       endingPointX, endingPointY,
                       cubes, directions);

            isPathFound = true;
            break;
        }
        /*
         * When there is no remaining cubes to observe,
         * the algorithm exits.
         */
        else if(cube == nullptr)
        {
            break;
        }
    }

    /* Reset cubes for future use. */
    for(auto &i : cubes)
    {
        i.ResetCosts();
    }

    return isPathFound;
}

/*
 * Simple function to reverse the directions of a path.
 */
static void ReversePath(std::vector<int> &directions)
{
    for(auto &i : directions)
    {
        switch(i)
        {
        case DIRECTION_LEFT:
            i = DIRECTION_RIGHT;
            break;
        case DIRECTION_RIGHT:
            i = DIRECTION_LEFT;
            break;
        case DIRECTION_UP:
            i = DIRECTION_DOWN;
            break;
        case DIRECTION_DOWN:
            i = DIRECTION_UP;
            break;
        }
    }
}

/*
 * Creates a path according to the cubes' states.
 */
static void CreatePath(const int startingPointX, const int startingPointY,
                       const int endingPointX, const int endingPointY,
                       std::vector<Cube> &cubes, std::vector<int> &directions)
{
    Cube *cube = nullptr;
    int x = endingPointX;
    int y = endingPointY;
    int currentDirection = -1;

    while(x != startingPointX || y != startingPointY)
    {
        cube = FindCube(x, y, cubes);

        if(cube == nullptr)
        {
            break;
        }

        currentDirection = cube->shortestPathDir;

        switch(currentDirection)
        {
        case DIRECTION_LEFT:
            x--;
            break;
        case DIRECTION_RIGHT:
            x++;
            break;
        case DIRECTION_UP:
            y--;
            break;
        case DIRECTION_DOWN:
            y++;
            break;
        /* If the direction is not left, right, up or down, path is invalid. */
        default:
            directions.clear();
            return;
        }

        directions.push_back(currentDirection);
    }

    /*
     * Directions are currently going from the endingPoint to the
     * startingPoint so we need to reverse them and flip them.
     */
    reverse(directions.begin(), directions.end());
    ReversePath(directions);
}

/*
 * Sets the gCost, hCost and fCost for adjacent cubes to the one in parameters.
 */
static void Propagate(const int startingPointX, const int startingPointY,
                      const int endingPointX, const int endingPointY,
                      Cube *cube, std::vector<Cube> &cubes)
{
    Cube *tempCube = nullptr;
    int shortestPathDir = -1;

    /* Propagate to all adjacent cubes. */
    for(int i = 0, j = 0, k = 0; k < 4; k++)
    {
        switch(k)
        {
        case 0: /* Propagate to left adjacent cube. */
            i = -1, j = 0;
            shortestPathDir = DIRECTION_RIGHT;
            break;
        case 1: /* Propagate to right adjacent cube. */
            i = 1, j = 0;
            shortestPathDir = DIRECTION_LEFT;
            break;
        case 2: /* Propagate to up adjacent cube. */
            i = 0, j = -1;
            shortestPathDir = DIRECTION_DOWN;
            break;
        case 3: /* Propagate to down adjacent cube. */
            i = 0, j = 1;
            shortestPathDir = DIRECTION_UP;
            break;
        }

        /* Make sure that the current cube is not the starting point. */
        if(cube->coordX + i != startingPointX
           || cube->coordY + j != startingPointY)
        {
            tempCube = FindCube(cube->coordX + i, cube->coordY + j, cubes);
        }
        else
        {
            tempCube = nullptr;
        }

        /* Give gCost, hCost and fCost values for the current adjacent cube. */
        if(tempCube != nullptr && !tempCube->isVisited && !tempCube->isWall)
        {
            int add = cube->gCost;

            if(add < 0)
            {
                add = 0;
            }

            add++;

            if(add < tempCube->gCost || tempCube->gCost < 0)
            {
                tempCube->gCost = add;
                tempCube->hCost = abs(endingPointX - tempCube->coordX)
                                  + abs(endingPointY - tempCube->coordY);
                tempCube->fCost = tempCube->gCost + tempCube->hCost;
                tempCube->shortestPathDir = shortestPathDir;
            }
        }
    }
}

/*
 * Returns the next cube to process.
 */
static Cube *GetNextCube(const int startingPointX, const int startingPointY,
                         std::vector<Cube> &cubes)
{
    Cube *tempCube = nullptr;
    int lowestFCost = INT_MAX;
    int lowestHCost = INT_MAX;

    /* Find the lowest F cost. */
    for(auto &i : cubes)
    {
        if(!i.isVisited && !i.isWall
           && (i.coordX != startingPointX || i.coordY != startingPointY)
           && i.fCost < lowestFCost)
        {

            if(i.fCost >= 0)
            {
                lowestFCost = i.fCost;
            }
        }
    }

    /*
     * Find the cube with the lowest H cost between all the cubes that have an
     * F cost equal to lowestFCost.
     */
    for(auto &i : cubes)
    {
        if(!i.isVisited && !i.isWall && i.fCost == lowestFCost && i.hCost >= 0
           && i.hCost < lowestHCost)
        {
            lowestHCost = i.hCost;
            tempCube = &i;
        }
    }

    return tempCube;
}

/*
 * Returns the reference to the cube associated with the (x, y) coordinates.
 */
static Cube *FindCube(const int coordX, const int coordY,
                      std::vector<Cube> &cubes)
{
    for(auto &i : cubes)
    {
        if(i.coordX == coordX && i.coordY == coordY)
        {
            return &i;
        }
    }

    return nullptr;
}

std::vector<int> &Path::GetDirections() { return directions; }

/*
 * Empties the path.
 */
void Path::DeletePath()
{
    directions.clear();
}
