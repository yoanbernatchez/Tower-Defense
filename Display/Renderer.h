#ifndef RENDERER_H
#define RENDERER_H

#include "Display.h"
#include "Camera.h"
#include "../Controllers/Scene.h"

/**
 * @brief This class is used for rendering all the scene objects or level
 *        objects, as well as HUD components.
 */
class Renderer
{
    public:
        int renderDelay;

        Renderer();

        /**
         * @brief Renders the elements of a scene. HUD, HUD components and
         *        black screen transition.
         *
         * @param display:  Object containing the target renderer.
         * @param scene:    Scene with the HUD elements to render.
         * @param textures: Textures object that contains sprites and textures.
         */
        void RenderSceneHud(Display &display, Scene &scene,
                            Textures &textures);

        /**
         * @brief Renders game elements such as the cubes, enemies and towers.
         *
         * @param display:  Reference to the display (window and renderer) for
         *                  rendering.
         * @param camera:   Reference to the camera.
         * @param level:    Reference to object containing cube and entity
         *                  data.
         * @param textures: Reference to object containing the textures used
         *                  in the rendering process.
         */
        void RenderLevel(SDL_Renderer *renderer, Camera &camera, Level &level,
                         Textures &textures);

        /**
         * @brief Renders the entities associated with a cube.
         *
         * @param display:  Display object containing the window and renderer.
         * @param level:    Level object containing entity and cube data.
         * @param textures: Textures object containing sprites and textures.
         * @param cubeX:    Coordinates of the parent cube in x.
         * @param cubeY:    Coordinates of the parent cube in y.
         */
        void RenderEntities(SDL_Renderer *renderer, Level &level,
                              Textures &textures, int cubeX, int cubeY);

    private:
        /**
         * @brief Updates the source coordinates for cubes and entities.
         *
         * @param level:    Level data object containing the cubes and entities
         *                  to update.
         * @param camera:   Camera object containing the position on screen and
         *                  the the zoom amount.
         * @param textures: Textures object containing sprites and textures
         *                  info.
         */
        void SetSrcPositions(Level &level, Camera &camera, Textures &textures);

        /**
         * @brief Updates the destination coordinates for cubes and entities.
         *
         * @param level:    Level data object containing the cubes and entities
         *                  to update.
         * @param camera:   Camera object containing the position on screen and
         *                  the zoom amount.
         * @param textures: Textures object containing sprites and textures
         *                  info.
         */
        void SetDstPositions(Level &level, Camera &camera, Textures &textures);

        /**
         * @brief Draws a red elliptical range indicator around a point.
         *
         * @param display: Object containing the rendering target.
         * @param camera:  Camera object with zoom and position information.
         * @param range:   Horizontal radius of the ellipse.
         * @param x:       Coordinate of the ellipse's center in x.
         * @param y:       Coordinate of the ellipse's center in y.
         */
        void DrawRange(SDL_Renderer *renderer, const Camera &camera,
                       int range, int x, int y);

        /**
         * @brief Renders a HUD and its components.
         *
         * @param display:  Display object containing the window and renderer.
         * @param hud:      The HUD to render.
         * @param textures: Textures object containing sprites and textures.
         */
        void RenderHud(SDL_Renderer *renderer, std::shared_ptr<Hud> &hud,
                       Textures &textures);
};

#endif // RENDERER_H
