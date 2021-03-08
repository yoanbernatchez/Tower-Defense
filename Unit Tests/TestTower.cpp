/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-02-06
 * Tested class: Path
 *
 * This file unit tests all possible scenarios for methods in the Path
 * class.
 */

#include "../~External Libraries/catch.hpp"
#include <math.h>
#include "../Entities/Tower.h"
#include "../Entities/Unit.h"

TEST_CASE("Tests for ChangeDirection", "[Tower]")
{
    Tower tower(0, 0, 0);
    float fifteenCos = (sqrt(6.0f) + sqrt(2.0f)) / 4.0f;
    float fifteenSin = (sqrt(6.0f) - sqrt(2.0f)) / 4.0f;

    SECTION("Test with orientation 0.")
    {
        /* Max value. */
        tower.ChangeDirection(0, 0, fifteenCos, fifteenSin);
        REQUIRE(tower.orientation == 0);
        /* Min value. */
        tower.ChangeDirection(0, 0, fifteenCos, -fifteenSin + 0.01f);
        REQUIRE(tower.orientation == 0);
    }

    SECTION("Test with orientation 1.")
    {
        /* Max value. */
        tower.ChangeDirection(0, 0, fifteenCos - 0.01f, -fifteenSin);
        REQUIRE(tower.orientation == 1);
        /* Min value. */
        tower.ChangeDirection(0, 0, 1.0f / 2.0f + 0.01f, -sqrt(3.0f) / 2.0f);
        REQUIRE(tower.orientation == 1);
    }

    SECTION("Test with orientation 2.")
    {
        /* Max value. */
        tower.ChangeDirection(0, 0, 1.0f / 2.0f, -sqrt(3.0f) / 2);
        REQUIRE(tower.orientation == 2);
        /* Min value. */
        tower.ChangeDirection(0, 0, -1.0f / 2.0f + 0.01f, -sqrt(3.0f) / 2.0f);
        REQUIRE(tower.orientation == 2);
    }

    SECTION("Test with orientation 3.")
    {
        /* Max value. */
        tower.ChangeDirection(0, 0, -1.0f / 2.0f, -sqrt(3.0f) / 2.0f);
        REQUIRE(tower.orientation == 3);
        /* Min value. */
        tower.ChangeDirection(0, 0, -fifteenCos + 0.01f, -fifteenSin);
        REQUIRE(tower.orientation == 3);
    }

    SECTION("Test with orientation 4.")
    {
        /* Max value. */
        tower.ChangeDirection(0, 0, -fifteenCos - 0.01f, fifteenSin);
        REQUIRE(tower.orientation == 4);
        /* Min value. */
        tower.ChangeDirection(0, 0, -fifteenCos, -fifteenSin);
        REQUIRE(tower.orientation == 4);
    }

    SECTION("Test with orientation 5.")
    {
        /* Max value. */
        tower.ChangeDirection(0, 0, -fifteenCos, fifteenSin);
        REQUIRE(tower.orientation == 5);
        /* Min value. */
        tower.ChangeDirection(0, 0, -1.0f / 2.0f, sqrt(3.0f) / 2.0f - 0.01f);
        REQUIRE(tower.orientation == 5);
    }

    SECTION("Test with orientation 6.")
    {
        /* Max value. */
        tower.ChangeDirection(0, 0, -1.0f / 2.0f, sqrt(3.0f) / 2.0f);
        REQUIRE(tower.orientation == 6);
        /* Min value. */
        tower.ChangeDirection(0, 0, 1.0f / 2.0f, sqrt(3.0f) / 2.0f + 0.01f);
        REQUIRE(tower.orientation == 6);
    }

    SECTION("Test with orientation 7.")
    {
        /* Max value. */
        tower.ChangeDirection(0, 0, 1.0f / 2.0f, sqrt(3.0f) / 2.0f);
        REQUIRE(tower.orientation == 7);
        /* Min value. */
        tower.ChangeDirection(0, 0, fifteenCos, fifteenSin + 0.01f);
        REQUIRE(tower.orientation == 7);
    }
}

TEST_CASE("Tests for TargetUnit", "[Tower]")
{
    Tower tower(0, 0, 0);
    /* Set tower position. */
    tower.dst.x = 200;
    tower.dst.y = 200;
    tower.dst.w = 200;
    tower.dst.h = 200;
    tower.range = 400;

    std::vector<Unit> units;
    Unit unit(0, 0, 0, 0, 0);
    unit.isVisible = true;

    /* Set unit positions. */
    unit.id = 3;
    unit.dst.x = 100;
    unit.dst.y = 100;
    unit.dst.w = 64;
    unit.dst.h = 64;

    units.push_back(unit);

    tower.TargetUnit(units, 200);

    SECTION("Test with only one unit.")
    {
        REQUIRE(tower.targetUnit != nullptr);
    }

    tower.targetUnit = nullptr;

    /* Setup a new unit. */
    units.push_back(unit);
    units[1].id = 1;
    units[1].dst.x = 220;
    units[1].dst.y = 220;
    units[1].dst.w = 64;
    units[1].dst.h = 64;
    tower.TargetUnit(units, 200);

    SECTION("Test between two units (target retention).")
    {
        REQUIRE(tower.targetUnit != nullptr);
        REQUIRE(tower.targetUnit->id == 3);
    }

    tower.targetUnit = nullptr;

    units.at(0).dst.x = 1000;
    tower.TargetUnit(units, 200);

    SECTION("Test between two units (target switch).")
    {
        REQUIRE(tower.targetUnit != nullptr);
        REQUIRE(tower.targetUnit->id == 1);
    }
}
