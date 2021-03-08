#ifndef BUTTON_H
#define BUTTON_H

#include <memory>
#include <vector>
#include "HudComponent.h"
#include "Text.h"

/**
 * @brief This class implements a Button that can be interacted with.
 */
class Button : public HudComponent
{
    public:
        std::vector<std::shared_ptr<Text>> texts;
        bool isHovered;
        bool isHighlightable;
        SDL_Color highlightColor;
        bool isPressable;

        Button(int borderSize, SDL_Color borderColor,
               SDL_Color backgroundColor, int width, int height);

        /**
         * @brief Sets a button to pressed.
         */
        void Press();

        /**
         * @brief Sets a button to not pressed.
         */
        void Release();

        /**
         * @brief Returns whether the mouse coordinates are in a button.
         *
         * @param mouseX: Mouse coordinate in x.
         * @param mouseY: Mouse coordinate in y.
         * @param x:      Right destination coordinate of the button on screen.
         * @param y:      Bottom destination coordinate of the button
         *                on screen.
         *
         * @return True if the mouse coordinates are in the button, false
         *         otherwise.
         */
        bool IsMouseOnButton(int mouseX, int mouseY, int x, int y);

        /**
         * @brief Centers a button's text in the middle of the button.
         *
         * @param id: Id of the text to center.
         */
        void CenterTextById(int id);

        /**
         * @brief Safely changes the press depth of the button.
         *
         * @param depth: New depth for the button.
         */
        void SetPressDepth(int depth);

        /**
         * @brief Adds a text component to the button.
         *
         * @param renderer: Rendering target.
         * @param text:     String for the new text component.
         * @param fontSize: Font size of the new text component.
         * @param color:    Font color of the new text component.
         * @param fontName: Font of the new text component.
         */
        void AddText(SDL_Renderer *renderer, std::string text, int fontSize,
                     SDL_Color color, FONT fontName);

        /* Getters. */
        std::string GetLabel();

    private:
        int pressDepth;
        bool isPressed;
        std::string label;
};

#endif // BUTTON_H
