/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-02-05
 * Tested class: Camera
 *
 * This file unit tests all possible scenarios for the methods in the Camera
 * class.
 */

#include "../~External Libraries/catch.hpp"
#include "../Display/Camera.h"

TEST_CASE("Tests for MoveCamera", "[Camera]")
{
    Camera camera;

    int savedMouseX = 5;
    int savedMouseY = 2;
    int currMouseX = 0;
    int currMouseY = 0;

    camera.MoveCamera(savedMouseX, savedMouseY, currMouseX, currMouseY);

    SECTION("Test MoveCamera with negative movement.")
    {
        REQUIRE(camera.x == -5);
        REQUIRE(camera.y == -2);
    }

    savedMouseX = -2;
    savedMouseY = -1;
    currMouseX = 2;
    currMouseY = 5;

    camera.MoveCamera(savedMouseX, savedMouseY, currMouseX, currMouseY);

    SECTION("Test MoveCamera with positive movement.")
    {
        REQUIRE(camera.x == -1);
        REQUIRE(camera.y == 4);
    }
}

TEST_CASE("Tests for Zoom", "[Camera]")
{
    Camera camera;
    camera.SetMinZoom(0.5f);
    camera.SetMaxZoom(2.0f);
    camera.SetZoom(1.0f);

    SECTION("Test for zoom within min and max.")
    {
        camera.Zoom(-0.2f);
        REQUIRE(camera.GetZoom() == 0.8f);
    }

    SECTION("Test for zoom lower than minimum.")
    {
        camera.Zoom(-4.0f);
        REQUIRE(camera.GetZoom() == 1.0f);
    }

    SECTION("Test for zoom higher than maximum.")
    {
        camera.Zoom(4.0f);
        REQUIRE(camera.GetZoom() == 1.0f);
    }
}

TEST_CASE("Tests for SetZoom", "[Camera]")
{
    Camera camera;
    camera.SetMinZoom(0.5f);
    camera.SetMaxZoom(2.0f);

    SECTION("Test for zoomValue within min and max.")
    {
        REQUIRE(camera.SetZoom(1.2f));
        REQUIRE(camera.GetZoom() == 1.2f);
    }

    SECTION("Test for zoomValue lower than minimum.")
    {
        REQUIRE(!camera.SetZoom(0.4f));
        REQUIRE(camera.GetZoom() == 1.0f);
    }

    SECTION("Test for zoomValue higher than maximum.")
    {
        REQUIRE(!camera.SetZoom(2.1f));
        REQUIRE(camera.GetZoom() == 1.0f);
    }
}

TEST_CASE("Tests for SetMinZoom", "[Camera]")
{
    Camera camera;
    float baseMinZoom = camera.GetMinZoom();
    float baseMaxZoom = camera.GetMaxZoom();

    SECTION("Test SetMinZoom with min greater than max.")
    {
        REQUIRE(!camera.SetMinZoom(baseMaxZoom + 0.1f));
        REQUIRE(camera.GetMinZoom() == baseMinZoom);
    }

    SECTION("Test SetMinZoom with min smaller or equal to max.")
    {
        REQUIRE(camera.SetMinZoom(baseMaxZoom));
        REQUIRE(camera.GetMinZoom() == baseMaxZoom);
    }
}

TEST_CASE("Tests for SetMaxZoom", "[Camera]")
{
    Camera camera;
    float baseMinZoom = camera.GetMinZoom();
    float baseMaxZoom = camera.GetMaxZoom();

    SECTION("Test SetMaxZoom with max smaller than min.")
    {
        REQUIRE(!camera.SetMaxZoom(baseMinZoom - 0.1f));
        REQUIRE(camera.GetMaxZoom() == baseMaxZoom);
    }

    SECTION("Test SetMaxZoom with max greater or equal to min.")
    {
        REQUIRE(camera.SetMaxZoom(baseMinZoom));
        REQUIRE(camera.GetMaxZoom() == baseMinZoom);
    }
}
