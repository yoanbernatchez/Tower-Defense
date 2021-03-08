#ifndef HUD_H
#define HUD_H

#include <SDL.h>
#include "Button.h"
#include "Text.h"
#include "Image.h"

/**
 * @brief This class is a container containing HUD components.
 */
class Hud
{
    public:
        std::vector<Button> buttons;
        std::vector<Image> images;
        std::vector<std::shared_ptr<Text>> texts;
        SDL_Rect dst;
        bool hasBorder;
        SDL_Color borderColor;
        int borderSize;
        bool hasBackground;
        SDL_Color backgroundColor;
        bool isVisible;

        Hud(SDL_Rect dst, bool hasBorder, SDL_Color borderColor,
            int borderSize, bool hasBackground, SDL_Color backgroundColor);

        /**
         * @brief Sets the destination on screen of the HUD.
         *
         * @param x: Coordinate in x of the HUD's position on screen.
         * @param y: Coordinate in y of the HUD's position on screen.
         * @param w: Width of the HUD on screen.
         * @param h: Height of the HUD on screen.
         */
        void SetDst(int x, int y, int w, int h);

        /**
         * @brief Removes a component by index from the HUD.
         *
         * @param type:  Component type to remove.
         * @param index: Component index to remove.
         */
        void RemoveComponentAtIndex(HUD_COMPONENT_TYPE type,
                                    unsigned int index);

        /**
         * @brief Adds a text component to the HUD.
         *
         * @param renderer: Rendering target.
         * @param text:     String to make a texture from.
         * @param fontSize: Font size of the text.
         * @param color:    Font color of the text.
         * @param fontName: Font of the text.
         */
        void AddText(SDL_Renderer *renderer, std::string text, int fontSize,
                     SDL_Color color, FONT fontName);

        /**
         * @brief Adds an image to the HUD.
         *
         * @param imgId: Id of the image to add.
         * @param x:     Coordinate in x relative to the HUD for rendering.
         * @param y:     Coordinate in y relative to the HUD for rendering.
         * @param w:     Width of the image to render.
         * @param h:     Height of the image to render.
         */
        void AddImage(int imgId, int x, int y, int w, int h);

        /**
         * @brief Adds an image to the HUD.
         *
         * @param imgId: Id of the image to add.
         * @param x:     Coordinate in x relative to the HUD for rendering.
         * @param y:     Coordinate in y relative to the HUD for rendering.
         */
        void AddImage(int imgId, int x, int y);

        /**
         * @brief Move the HUD from point A to point B in a defined time frame.
         *
         * @param src:          Coordinates of the point A on screen.
         * @param dst:          Coordinates of the point B on screen.
         * @param timeInterval: Time required to go from point A to point B.
         *
         * @return True if the move operation is over, false otherwise.
         */
        bool MoveComponent(SDL_Rect src, SDL_Rect dst, double timeInterval);

    private:
        double moveTimerBegin;
        bool isInMovement;
};

#endif // HUD_H
