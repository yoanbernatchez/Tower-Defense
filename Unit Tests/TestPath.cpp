/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-01-29
 * Tested class: Path
 *
 * This file unit tests all possible scenarios for the methods in the Path
 * class.
 */

#include <vector>
#include "../~External Libraries/catch.hpp"
#include "../Level/Path.h"
#include "../Entities/Unit.h"

TEST_CASE("Tests for CreatePath", "[Pathfinder]")
{
    Unit unit(0, 0, 0, 0, 0);
    std::vector<Cube> cubes;

    /*
     * This is the pattern emulated for the tests.
     * o represents walkable areas.
     * x represents walls.
     * Spaces represent empty grid cells.
     *
     * Grid setup:
     * o oo
     * oxox
     * oooo
     */

    /* Setting up 4th collumn. */
    Cube tempCube(0, 0, 0, 0);
    cubes.push_back(tempCube);
    tempCube.coordX++;
    tempCube.isWall = true;
    cubes.push_back(tempCube);
    tempCube.coordX++;
    tempCube.isWall = false;
    cubes.push_back(tempCube);
    tempCube.coordX = 0;
    tempCube.coordY = 1;

    /* Setting up 3rd collumn. */
    for(int i = 0; i < 3; i++)
    {
        cubes.push_back(tempCube);
        tempCube.coordX++;
    }

    /* Setting up 2nd collumn. */
    tempCube.coordX = 1;
    tempCube.coordY = 2;
    tempCube.isWall = true;
    cubes.push_back(tempCube);
    tempCube.coordX++;
    tempCube.isWall = false;
    cubes.push_back(tempCube);

    /* Setting up 1st collumn. */
    tempCube.coordX = 0;
    tempCube.coordY = 3;

    for(int i = 0; i < 3; i++)
    {
        cubes.push_back(tempCube);
        tempCube.coordX++;
    }

    SECTION("Test GetPath with starting point same as ending point")
    {
        REQUIRE(unit.path.FindPath(0, 0, 0, 0, cubes) == false);
        REQUIRE(unit.path.GetDirections().size() == 0);
    }

    SECTION("Test GetPath with non-existing starting point")
    {
        REQUIRE(unit.path.FindPath(-5, -5, 0, 0, cubes) == false);
        REQUIRE(unit.path.GetDirections().size() == 0);
    }

    SECTION("Test GetPath with non-existing ending point")
    {
        REQUIRE(unit.path.FindPath(0, 0, -5, -5, cubes) == false);
        REQUIRE(unit.path.GetDirections().size() == 0);
    }

    SECTION("Test GetPath with starting point in a wall")
    {
        REQUIRE(unit.path.FindPath(1, 0, 0, 0, cubes) == false);
        REQUIRE(unit.path.GetDirections().size() == 0);
    }

    SECTION("Test GetPath with ending point in a wall")
    {
        REQUIRE(unit.path.FindPath(0, 0, 1, 0, cubes) == false);
        REQUIRE(unit.path.GetDirections().size() == 0);
    }

    SECTION("Test GetPath with existing path (1 step)")
    {
        REQUIRE(unit.path.FindPath(0, 0, 0, 1, cubes) == true);
        REQUIRE(unit.path.GetDirections().size() == 1);
    }

    SECTION("Test GetPath with path navigating through obstacles"
            "(example case 1)")
    {
        REQUIRE(unit.path.FindPath(0, 0, 0, 3, cubes) == true);
        REQUIRE(unit.path.GetDirections().size() == 7);
        REQUIRE(unit.path.GetDirections().at(0) == DIRECTION_DOWN);
        REQUIRE(unit.path.GetDirections().at(1) == DIRECTION_RIGHT);
        REQUIRE(unit.path.GetDirections().at(2) == DIRECTION_RIGHT);
        REQUIRE(unit.path.GetDirections().at(3) == DIRECTION_DOWN);
        REQUIRE(unit.path.GetDirections().at(4) == DIRECTION_DOWN);
        REQUIRE(unit.path.GetDirections().at(5) == DIRECTION_LEFT);
        REQUIRE(unit.path.GetDirections().at(6) == DIRECTION_LEFT);
    }

    SECTION("Test GetPath with path navigating through obstacles"
            "(example case 2)")
    {
        REQUIRE(unit.path.FindPath(2, 3, 1, 1, cubes) == true);
        REQUIRE(unit.path.GetDirections().size() == 3);
        REQUIRE(unit.path.GetDirections().at(0) == DIRECTION_UP);
        REQUIRE(unit.path.GetDirections().at(1) == DIRECTION_UP);
        REQUIRE(unit.path.GetDirections().at(2) == DIRECTION_LEFT);
    }
}

TEST_CASE("Tests for DeletePath", "[Pathfinder]")
{
    Unit unit(0, 0, 0, 0, 0);
    std::vector<Cube> cubes;
    Cube tempCube(0, 0, 0, 0);

    SECTION("Test DeletePath with non-empty path (size > 0)")
    {
        /*
         * Setting up some cubes in a line.
         */
        for(int i = 0; i < 5; i++)
        {
            cubes.push_back(tempCube);
            tempCube.coordX++;
        }

        REQUIRE(unit.path.FindPath(0, 0, 4, 0, cubes) == true);
        REQUIRE(unit.path.GetDirections().size() == 4);

        unit.path.DeletePath();
        REQUIRE(unit.path.GetDirections().size() == 0);
    }

    SECTION("Test DeletePath with empty path (size == 0)")
    {
        unit.path.DeletePath();
        REQUIRE(unit.path.GetDirections().size() == 0);
    }
}
