/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-05
 * Project: Tower Defense
 * File: Camera.cpp
 *
 * Brief: This class implements the Camera class, used for moving the level
 *        around and zooming (useful for rendering).
 */

#include "Camera.h"
#include "../~External Libraries/catch.hpp"

Camera::Camera()
{
    x = 0;
    y = 0;
    zoom = 1.0f;
    this->minZoom = 0.5f;
    this->maxZoom = 2.0f;
    isCameraChanged = true;
}

/*
 * Move the camera in the x and y axis according to mouse coordinates.
 */
void Camera::MoveCamera(int &mouseX, int &mouseY,
                        int tempMouseX, int tempMouseY)
{
    x -= mouseX - tempMouseX;
    y -= mouseY - tempMouseY;

    mouseX = tempMouseX;
    mouseY = tempMouseY;

    isCameraChanged = true;
}

/*
 * Increments or decrements the zoom amount of the camera.
 */
void Camera::Zoom(float amount)
{
    float tempZoom = zoom + amount;

    SetZoom(tempZoom);
}

/*
 * Sets the zoom value for the camera.
 */
bool Camera::SetZoom(float zoomVal)
{
    bool isZoomChanged = false;

    if(zoomVal >= minZoom && zoomVal <= maxZoom)
    {
        zoom = zoomVal;
        isCameraChanged = true;
        isZoomChanged = true;
    }

    return isZoomChanged;
}

/*
 * Sets a new value for the minimum zoom value. Updates the current zoom value
 * (if needed) so that it remains within the min and the max.
 */
bool Camera::SetMinZoom(float minZoom)
{
    bool isMinChanged = false;

    if(minZoom <= maxZoom)
    {
        this->minZoom = minZoom;

        if(zoom < minZoom)
        {
            zoom = minZoom;
        }

        isMinChanged = true;
    }

    return isMinChanged;
}

/*
 * Sets a new value for the maximum zoom value. Updates the current zoom value
 * (if needed) so that it remains within the min and the max.
 */
bool Camera::SetMaxZoom(float maxZoom)
{
    bool isMaxChanged = false;

    if(maxZoom >= minZoom)
    {
        this->maxZoom = maxZoom;

        if(zoom > maxZoom)
        {
            zoom = maxZoom;
        }

        isMaxChanged = true;
    }

    return isMaxChanged;
}

float Camera::GetZoom() const { return zoom; }

float Camera::GetMinZoom() const { return minZoom; }

float Camera::GetMaxZoom() const { return maxZoom; }
