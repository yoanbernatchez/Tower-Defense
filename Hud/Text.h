#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "HudComponent.h"

/*
 * Some colors used for TTF fonts.
 */
#define SDL_COLOR_BLACK {0, 0, 0, 255}
#define SDL_COLOR_LIGHT_WHITE {200, 200, 200, 185}
#define SDL_COLOR_WHITE {235, 235, 235, 255}
#define SDL_COLOR_LIGHT_GREY {183, 183, 183, 255}
#define SDL_COLOR_GREY {112, 112, 112, 255}
#define SDL_COLOR_RED {255, 50, 50, 255}
#define SDL_COLOR_GREEN {0, 255, 0, 255}
#define SDL_COLOR_BLUE {0, 0, 255, 255}
#define SDL_COLOR_YELLOW {255, 240, 17, 255}
#define SDL_COLOR_FUSHIA {200, 0, 122, 132}
#define SDL_COLOR_DARK_RED {200, 0, 0, 62}

/**
 * @brief Font type of a text.
 */
enum FONT{FONT_TIMES, FONT_CALIBRI_REGULAR, FONT_AGENCY_FB_REGULAR,
          FONT_AGENCY_FB_BOLD};

/**
 * @brief Rendering type of a text.
 */
enum TTF_RENDER_TYPE{TTF_RENDER_SOLID, TTF_RENDER_BLENDED, TTF_RENDER_WRAPPED};

/**
 * @brief This class is used to make text textures to use for rendering.
 */
class Text : public HudComponent
{
    public:
        int shadowOffsetX;
        int shadowOffsetY;

        Text(SDL_Renderer *renderer, std::string text, int fontSize,
             SDL_Color color, FONT fontName);

        /**
         * @brief Free allocated memory.
         */
        virtual ~Text();

        /**
         * @brief Creates textures ready to use for the text and shadow.
         *
         * @param renderer:   Rendering target.
         * @param text:       String to make a texture of.
         * @param renderType: Render type, blended, solid or wrapped.
         * @param fontSize:   Font size of the text.
         * @param color:      Font color of the text.
         * @param fontName:   Font name of the text and shadow.
         */
        void SetText(SDL_Renderer *renderer, std::string text,
                     TTF_RENDER_TYPE renderType, int fontSize,
                     SDL_Color color, FONT fontName);

        /**
         * @brief Changes the font of a text (erases previous texture and
         *        create a new one).
         *
         * @param renderer: Rendering target.
         * @param fontName: New font to use to make the texture.
         */
        void ChangeFont(SDL_Renderer *renderer, FONT fontName);

        /**
         * @brief Changes the font size of a text (erases previous texture and
         *        create a new one).
         *
         * @param renderer: Rendering target.
         * @param fontSize: New font size to use to make the texture.
         */
        void ChangeFontSize(SDL_Renderer *renderer, int fontSize);

        /**
         * @brief Changes the render type of a text.
         *
         * @param renderer:   Rendering target.
         * @param renderType: New render type, blended, solid or wrapped.
         */
        void ChangeRenderType(SDL_Renderer *renderer,
                              TTF_RENDER_TYPE renderType);

        /**
         * @brief Changes the font coor of a text (erases previous texture and
         *        create a new one).
         *
         * @param renderer: Rendering target.
         * @param color:    New font color to use to make the texture.
         */
        void ChangeColor(SDL_Renderer *renderer, SDL_Color color);

        /**
         * @brief Changes the text (erases previous texture and create a new
         *        one).
         *
         * @param renderer: Rendering target.
         * @param text:     New string to use to make the texture.
         */
        void ChangeText(SDL_Renderer *renderer, std::string text);

        /**
         * @brief Wraps a text's texture (sets a max length for the text and
         *        inserts a line feed where the text exceed the max length).
         *
         * @param renderer:   Rendering target.
         * @param wrapLength: Max length of the text's texture.
         */
        void Wrap(SDL_Renderer *renderer, int wrapLength);

        /**
         * @brief Unwraps a text (erases the max length of the text's texture).
         *
         * @param renderer:      Rendering target.
         * @param newRenderType: Render type, blended, solid or wrapped.
         */
        void Unwrap(SDL_Renderer *renderer, TTF_RENDER_TYPE renderType);

        /**
         * @brief Create a shadow texture and shows the text's shadow when
         *        rendering.
         *
         * @param renderer:      Rendering target.
         * @param shadowOffsetX: The offset in x of the shadow's texture when
         *                       rendering in relation to the text's texture.
         * @param shadowOffsetY: The offset in y of the shadow's texture when
         *                       rendering in relation to the text's texture.
         * @param color:         Rendering color of the shadow.
         */
        void EnableShadow(SDL_Renderer *renderer, int shadowOffsetX,
                          int shadowOffsetY, SDL_Color color);

        /**
         * @brief Hides the text's shadow when rendering.
         */
        void DisableShadow();

        /* Getters. */
        SDL_Texture *GetTexture();
        SDL_Texture *GetShadowTexture();
        bool GetIsShadowEnabled();
        std::string GetLabel();

    private:
        int fontSize;
        FONT fontName;
        TTF_RENDER_TYPE renderType;
        SDL_Color color;
        SDL_Color shadowColor;
        bool isShadowEnabled;
        bool isWrapped;
        int wrapLength;
        std::string text;
        SDL_Texture *texture;
        SDL_Texture *shadowTexture;
};

#endif // TEXT_H
