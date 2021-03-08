#ifndef CAMERA_H
#define CAMERA_H

/**
 * @brief This class implements the Camera class, used for moving the level
 *        around and zooming (useful for rendering).
 */
class Camera
{
    public:
        int x;
        int y;
        bool isCameraChanged;

        Camera();

        /**
         * @brief Move the camera in the x and y axis according to mouse
         *        coordinates.
         *
         * @param mouseX:     Current position of the mouse in the x axis.
         * @param mouseY:     Current position of the mouse in the y axis.
         * @param tempMouseX: Saved temporary position of the mouse in the x
         *                    axis.
         * @param tempMouseY: Saved temporary position of the mouse in the y
         *                    axis.
         */
        void MoveCamera(int &mouseX, int &mouseY,
                        int tempMouseX, int tempMouseY);

        /**
         * @brief Increments or decrements the zoom amount of the camera.
         *
         * @param amount: The amount to increment or decrement the zoom
         *                property. Negative to zoom out, positive to zoom in.
         */
        void Zoom(float amount);

        /* Setters. */
        /**
         * @brief Sets the zoom value for the camera.
         *
         * @param zoomVal: The zoom value.
         *
         * @return True on success, false if zoomVal is not within the zoomMin
         *         and zoomMax values.
         */
        bool SetZoom(float zoomVal);

        /**
         * @brief Sets a new value for the minimum zoom value. Updates the
         *        current zoom value (if needed) so that it remains within the
         *        min and the max.
         *
         * @param minZoom: The new minimum for the zoom value.
         *
         * @return True on success, false if minZoom is bigger than maxZoom.
         */
        bool SetMinZoom(float minZoom);

        /**
         * @brief Sets a new value for the maximum zoom value. Updates the
         *        current zoom value (if needed) so that it remains within the
         *        min and the max.
         *
         * @param maxZoom: The new maximum for the zoom value.
         *
         * @return True on success, false if maxZoom is smaller than minZoom.
         */
        bool SetMaxZoom(float maxZoom);

        /* Getters. */
        float GetZoom() const;
        float GetMinZoom() const;
        float GetMaxZoom() const;

    private:
        float zoom;
        float minZoom;
        float maxZoom;
};

#endif // CAMERA_H
