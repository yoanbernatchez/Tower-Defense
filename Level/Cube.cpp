/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-01-20
 * Project: Tower Defense
 * File: Cube.cpp
 *
 * Brief: This class contains an implementation of "cubes" for the grid. They
 *        are used to path find, for rendering and for unit placement.
 */

#include "Cube.h"

Cube::Cube(int x, int y, int z, int id)
{
    coordX = x;
    coordY = y;
    coordZ = z;
    SetId(id);
    src = {0, 0, 0, 0};
    dst = {0, 0, 0, 0};
    isRendered = false;
    isWall = false;
    isHighlighted = false;
    ResetCosts();
}

/*
 * Resets the pathfinding attributes (should only be used by Path.cpp).
 */
void Cube::ResetCosts()
{
    gCost = -1;
    hCost = -1;
    fCost = -1;
    shortestPathDir = -1;
    isVisited = false;
}

/*
 * Sets the id of the cube.
 */
void Cube::SetId(int id)
{
    if(id >= 0)
    {
        this->id = id;
    }
    else
    {
        this->id = 0;
    }
}

int Cube::GetId() { return id; }
