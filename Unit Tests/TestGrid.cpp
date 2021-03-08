/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-01-20
 * Tested class: Grid
 *
 * This file unit tests all possible scenarios for methods in the Grid
 * class.
 */

#include "../~External Libraries/catch.hpp"
#include "../Level/Grid.h"

TEST_CASE("Tests for CalculateLowestRowPlusCol", "[Grid]")
{

    Grid grid;
    grid.AddCube(2, 0, 0, 0);
    grid.AddCube(1, 0, 0, 0);

    grid.CalculateLowestRowPlusCol();

    SECTION("Test with positive coordinates.")
    {
        REQUIRE(grid.GetLowestRowPlusCol() == 1);
    }

    grid.AddCube(-3, -1, 0, 0);

    grid.CalculateLowestRowPlusCol();

    SECTION("Test with negative coordinates.")
    {
        REQUIRE(grid.GetLowestRowPlusCol() == -4);
    }
}

TEST_CASE("Tests for GetCubeByCoord", "[Grid]")
{

    Grid grid;
    Cube *cube = nullptr;
    grid.AddCube(0, 0, 0, 0);

    grid.cubes[0].dst.x = 100;
    grid.cubes[0].dst.y = 200;
    grid.cubes[0].dst.w = 204;
    grid.cubes[0].dst.h = 234;

    cube = grid.GetCubeByCoord(0, 0);

    SECTION("Test with coordinates outside of the cube.")
    {
        REQUIRE(cube == nullptr);
    }

    cube = grid.GetCubeByCoord(100 + 204 / 2, 200 + 234 / 2);

    SECTION("Test with coordinates inside bottom part of cube.")
    {
        REQUIRE(cube == nullptr);
    }

    cube = grid.GetCubeByCoord(100 + 204 / 2, 200 + 50);

    SECTION("Test with coordinates inside top part of cube.")
    {
        REQUIRE(cube != nullptr);
    }

    grid.AddCube(1, 0, 0, 0);

    grid.cubes[1].dst.x = 100;
    grid.cubes[1].dst.y = 200;
    grid.cubes[1].dst.w = 204;
    grid.cubes[1].dst.h = 234;

    cube = grid.GetCubeByCoord(100 + 204 / 2, 200 + 50);

    SECTION("Test with cubes on top of each other.")
    {
        REQUIRE(cube != nullptr);
        REQUIRE(cube->coordX == 1);
    }
}
