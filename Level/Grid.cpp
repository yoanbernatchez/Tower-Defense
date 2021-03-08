/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-01-20
 * Project: Tower Defense
 * File: Cube.cpp
 *
 * Brief: This class contains an implementation of a grid containing cubes.
 *        Provides the function to add cubes, move cubes, find a cube using
 *        x and y screen coordinates.
 */

#include "Grid.h"
#include <iostream>
#include <math.h>

Grid::Grid()
{
    lowestRowPlusCol = 0;
}

/*
 * Adds a cube to the grid at the specified coordinates.
 */
void Grid::AddCube(int x, int y, int z, int id)
{
    Cube cube(x, y, z, id);
    cubes.push_back(cube);

    CalculateLowestRowPlusCol();
}

/*
 * Moves a cube to the specified coordinates.
 */
void Grid::MoveCube(Cube cube, int x, int y, int z)
{
    cube.coordX = x;
    cube.coordY = y;
    cube.coordZ = z;

    CalculateLowestRowPlusCol();
}

/*
 * Calculates the lowest row + column between all cubes (used for rendering).
 */
void Grid::CalculateLowestRowPlusCol()
{
    bool isFirstIteration = true;

    for(auto const &i : cubes)
    {
        if(isFirstIteration)
        {
            lowestRowPlusCol = i.coordX + i.coordY;
            isFirstIteration = false;
        }
        else if(i.coordX + i.coordY < lowestRowPlusCol)
        {
            lowestRowPlusCol = i.coordX + i.coordY;
        }
    }
}

/*
 * Finds if there is a cube at the x and y coordinates and returns it.
 */
Cube *Grid::GetCubeByCoord(int x, int y)
{
    Cube *cube = nullptr;
    double var = sqrt(3)/3;

    for(auto &i : cubes)
    {
        /*
         * Isometric search (we only test if the x and y coordinates are
         * within the top part of a cube).
         */
        if(y > (i.dst.x + i.dst.w/2)*var + i.dst.y - x*var
           && y < (i.dst.x + i.dst.w/2)*var + i.dst.y + i.dst.h/2 - x*var
           && y > -(i.dst.x + i.dst.w/2)*var + i.dst.y + x*var
           && y < -(i.dst.x + i.dst.w/2)*var + i.dst.y + i.dst.h/2 + x*var)
        {
            if(cube == nullptr)
            {
                cube = &i;
            }
            else if(i.coordX + i.coordY > cube->coordX + cube->coordY)
            {
                cube = &i;
            }
        }
    }

    return cube;
}

int Grid::GetLowestRowPlusCol() { return lowestRowPlusCol; }
