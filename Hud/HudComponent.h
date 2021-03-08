#ifndef HUDCOMPONENT_H
#define HUDCOMPONENT_H

#include <SDL.h>
#include <string>

/**
 * @brief All possible component types that can inherit from HudComponent.
 */
enum HUD_COMPONENT_TYPE{COMPONENT_BUTTON, COMPONENT_TEXT, COMPONENT_PORTRAIT};

/**
 * @brief Parent class that stores basic HUD component information.
 */
class HudComponent
{
    public:
        SDL_Rect src, dst, savedDst;
        int borderSize;
        SDL_Color borderColor;
        SDL_Color backgroundColor;
        double moveTimerBegin;
        bool isInMovement;
        unsigned int opacity;
        bool isVisible;

        HudComponent();

        /**
         * @brief Moves a HUD component from point A to point B in a specific
         *        amount of time.
         *
         * @param src:          Source (point A).
         * @param dst:          Destination (point B).
         * @param timeInterval: Amount of time to complete the movement.
         *
         * @return True if operation is completed, false otherwise.
         */
        virtual bool MoveComponent(SDL_Rect src, SDL_Rect dst,
                                   double timeInterval);

        /**
         * @brief Saves a rendering destination.
         */
        virtual void SaveDst();

        virtual std::string GetLabel() = 0;
};

#endif // HUDCOMPONENT_H
