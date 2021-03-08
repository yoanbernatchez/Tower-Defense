/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-06
 * Project: Tower Defense
 * File: Unit.cpp
 *
 * Brief: This class implements units (enemies) that can find a path that they
 *        can walk on.
 */

#include "Unit.h"
#include <math.h>

Unit::Unit(int id, int hp, int movSpeed, int goldValue, int spawnTime)
{
    src = {0, 0, 0, 0};
    dst = {0, 0, 0, 0};
    orientation = 0;
    isRendered = false;
    frame = 0;
    this->id = id;
    this->hp = hp;
    this->movSpeed = movSpeed;
    this->goldValue = goldValue;
    this->spawnTime = spawnTime;
    cubeX = 0;
    cubeY = 0;
    x = 0.0f;
    y = 0.0f;
    quadrant = DIRECTION_MIDDLE;
    direction = -1;
    isInNewCube = false;
    isNewPath = true;
    isVisible = false;
}

/*
 * Finds a path between two points (if the path exists) and assigns it
 * to the unit.
 */
void Unit::GetPath(int startingPointX, int startingPointY, int endingPointX,
                   int endingPointY, std::vector<Cube> &cubes)
{
    isInNewCube = false;
    path.FindPath(startingPointX, startingPointY, endingPointX, endingPointY,
                  cubes);
}

/*
 * Checks if a path exists between two points without assigning it to the unit.
 */
/* This should probably be transfered to Path.cpp. */
bool Unit::TestPath(int startingPointX, int startingPointY, int endingPointX,
                    int endingPointY, std::vector<Cube> &cubes)
{
    bool isPathValid = true;
    Path testPath;
    testPath.FindPath(startingPointX, startingPointY,
                      endingPointX, endingPointY, cubes);

    if(testPath.GetDirections().size() == 0)
    {
        isPathValid = false;
    }

    return isPathValid;
}

/*
 * Makes the unit move with the directions of its path.
 */
void Unit::WalkWithPath(int cubeLength)
{
    if(path.GetDirections().size() > 0)
    {
        Walk(path.GetDirections().at(0), cubeLength);
    }
}

/*
 * Makes the unit move in a direction.
 */
void Unit::Walk(int direction, int cubeLength)
{
    /* Define what direction to move in. */
    if(quadrant == direction || quadrant == DIRECTION_MIDDLE)
    {
        this->direction = direction;
    }
    else
    {
        this->direction = DIRECTION_MIDDLE;
    }

    /* Move in defined direction. */
    if(this->direction == DIRECTION_MIDDLE)
    {
        switch(quadrant)
        {
        case DIRECTION_LEFT:
            this->direction = DIRECTION_RIGHT;
            break;
        case DIRECTION_RIGHT:
            this->direction = DIRECTION_LEFT;
            break;
        case DIRECTION_UP:
            this->direction = DIRECTION_DOWN;
            break;
        case DIRECTION_DOWN:
            this->direction = DIRECTION_UP;
            break;
        }
    }

    switch(this->direction)
    {
    case DIRECTION_LEFT:
        x--;
        y = (sqrt(3)/3) * x;
        break;
    case DIRECTION_RIGHT:
        x++;
        y = (sqrt(3)/3) * x;
        break;
    case DIRECTION_UP:
        x++;
        y = -(sqrt(3)/3) * x;
        break;
    case DIRECTION_DOWN:
        x--;
        y = -(sqrt(3)/3) * x;
        break;
    }

    /* Define new quadrant. */
    if(x == 0.0f && y == 0.0f)
    {
        quadrant = DIRECTION_MIDDLE;
    }
    else if(x > 0.0f && y > 0.0f)
    {
        quadrant = DIRECTION_RIGHT;
    }
    else if(x > 0.0f && y < 0.0f)
    {
        quadrant = DIRECTION_UP;
    }
    else if(x < 0.0f && y > 0.0f)
    {
        quadrant = DIRECTION_DOWN;
    }
    else
    {
        quadrant = DIRECTION_LEFT;
    }

    /* Update the unit's cubeX and cubeY if they enter a new cube. */
    if(x > cubeLength * 0.25)
    {
        if(quadrant == DIRECTION_RIGHT)
        {
            cubeX++;
            quadrant = DIRECTION_LEFT;
        }
        if(quadrant == DIRECTION_UP)
        {
            cubeY--;
            quadrant = DIRECTION_DOWN;
        }

        x = -cubeLength * 0.25;

        isInNewCube = true;
    }
    else if(x < -cubeLength * 0.25)
    {
        if(quadrant == DIRECTION_LEFT)
        {
            cubeX--;
            quadrant = DIRECTION_RIGHT;
        }
        if(quadrant == DIRECTION_DOWN)
        {
            cubeY++;
            quadrant = DIRECTION_UP;
        }

        x = cubeLength * 0.25;

        isInNewCube = true;
    }

    /* Updates the y values of a unit if they are in a new cube. */
    if(isInNewCube
       && (quadrant == DIRECTION_LEFT || quadrant == DIRECTION_RIGHT))
    {
        y = (sqrt(3)/3) * x;
    }
    else if(isInNewCube)
    {
        y = -(sqrt(3)/3) * x;
    }

    if(isInNewCube && quadrant == DIRECTION_MIDDLE)
    {
        path.GetDirections().erase(path.GetDirections().begin());
        isInNewCube = false;
    }
}
