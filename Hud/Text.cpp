/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-03
 * Project: Tower Defense
 * File: Text.cpp
 *
 * Brief: This class contains an implementation of "Text" used to make text
 *        appear on screen. This class uses TTF which is a part of SDL to
 *        create text textures.
 */

#include "Text.h"
#include <iostream>

/**
 * @brief Returns a pointer to a TTF_Font.
 *
 * @param fontName: Name of the font to find.
 * @param fontSize: Font size to load.
 */
static TTF_Font *GetFont(FONT fontName, int fontSize);

/**
 * @brief Creates a text texture with TTF and returns its reference.
 *
 * @param renderer:   Rendering target.
 * @param text:       String to transform into a texture.
 * @param renderType: Rendering type, blended, solid or wrapped.
 * @param fontSize:   Font size of the text.
 * @param color:      Font color of the text.
 * @param fontName:   Font of the text.
 * @param wrapLength: Wrap length (max length of the texture).
 *
 * @return Pointer to the newly create texture.
 */
static SDL_Texture *CreateTexture(SDL_Renderer *renderer, std::string text,
                                  TTF_RENDER_TYPE renderType, int fontSize,
                                  SDL_Color color, FONT fontName,
                                  int wrapLength);

Text::Text(SDL_Renderer *renderer, std::string text, int fontSize,
           SDL_Color color, FONT fontName)
{
    texture = nullptr;
    shadowTexture = nullptr;
    wrapLength = -1;
    renderType = TTF_RENDER_BLENDED;
    isShadowEnabled = false;
    shadowOffsetX = 1;
    shadowOffsetY = 1;
    shadowColor = {0, 0, 0};
    src = {0, 0, 0, 0};
    dst = {0, 0, 0, 0};
    savedDst = {0, 0, 0, 0};
    isVisible = true;
    opacity = 255;

    SetText(renderer, text, renderType, fontSize, color, fontName);
}

/*
 * Creates textures ready to use for the text and shadow.
 */
void Text::SetText(SDL_Renderer *renderer, std::string text,
                   TTF_RENDER_TYPE renderType, int fontSize, SDL_Color color,
                   FONT fontName)
{
    this->text = text;
    this->fontSize = fontSize;
    this->color = color;
    this->fontName = fontName;

    /* Free previously allocated memory. */
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }

    /* Create new text texture. */
    texture = CreateTexture(renderer, text, renderType, fontSize, color,
                            fontName, wrapLength);

    /* Free previous shadow texture. */
    if(shadowTexture != nullptr)
    {
        SDL_DestroyTexture(shadowTexture);
    }

    /* Create new shadow texture. */
    if(isShadowEnabled)
    {
        shadowTexture = CreateTexture(renderer, text, renderType, fontSize,
                                      shadowColor, fontName, wrapLength);
    }

    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
    dst.w = src.w;
    dst.h = src.h;
}

/*
 * Wraps a text's texture (sets a max length for the text and inserts a line
 * feed where the text exceed the max length).
 */
void Text::Wrap(SDL_Renderer *renderer, int wrapLength)
{
    this->wrapLength = wrapLength;
    renderType = TTF_RENDER_WRAPPED;
    SetText(renderer, text, renderType, fontSize, color, fontName);
}

/*
 * Unwraps a text (erases the max length of the text's texture).
 */
void Text::Unwrap(SDL_Renderer *renderer, TTF_RENDER_TYPE renderType)
{
    this->renderType = renderType;
    SetText(renderer, text, renderType, fontSize, color, fontName);
}

/*
 * Changes the render type of a text.
 */
void Text::ChangeRenderType(SDL_Renderer *renderer, TTF_RENDER_TYPE renderType)
{
    this->renderType = renderType;
    SetText(renderer, text, renderType, fontSize, color, fontName);
}

/*
 * Hides the text's shadow when rendering.
 */
void Text::DisableShadow()
{
    isShadowEnabled = false;
}

/*
 * Create a shadow texture and shows the text's shadow when rendering.
 */
void Text::EnableShadow(SDL_Renderer *renderer, int shadowOffsetX,
                        int shadowOffsetY, SDL_Color color)
{
    isShadowEnabled = true;
    this->shadowOffsetX = shadowOffsetX;
    this->shadowOffsetY = shadowOffsetY;
    shadowColor = color;

    /* Free previous shadow texture. */
    if(shadowTexture != nullptr)
    {
        SDL_DestroyTexture(shadowTexture);
    }

    /* Create a new shadow texture. */
    if(isShadowEnabled)
    {
        shadowTexture = CreateTexture(renderer, text, renderType, fontSize,
                                      shadowColor, fontName, wrapLength);
    }
}

/*
 * Creates a text texture with TTF and returns its reference.
 */
static SDL_Texture *CreateTexture(SDL_Renderer *renderer, std::string text,
                                  TTF_RENDER_TYPE renderType, int fontSize,
                                  SDL_Color color, FONT fontName,
                                  int wrapLength)
{
    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;

    /* Get font. */
    TTF_Font *font = GetFont(fontName, fontSize);

    if(font == nullptr)
    {
        return nullptr;
    }

    /* Create surface with render type. */
    switch(renderType)
    {
    case TTF_RENDER_SOLID:
        surface = TTF_RenderText_Solid(font, text.c_str(), color);
        break;
    /* [Deprecated]
    case TTF_RENDER_SHADED:
        surface = TTF_RenderText_Shaded(font, text.c_str(), color, shadeColor);
        break;
    */
    case TTF_RENDER_BLENDED:
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
        break;
    case TTF_RENDER_WRAPPED:
        surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color,
                                                 wrapLength);
        break;
    default:
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
        break;
    }

    TTF_CloseFont(font);

    if(surface == nullptr)
    {
        std::cout << SDL_GetError() << " L: " << __LINE__ << " F: " << __FILE__
                  << "\n";
        return nullptr;
    }

    /* Create the texture. */
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if(texture == nullptr)
    {
        std::cout << SDL_GetError() << " L: " << __LINE__ << " F: " << __FILE__
                  << "\n";
        return nullptr;
    }

    SDL_FreeSurface(surface);

    return texture;
}

/*
 * Changes the font of a text (erases previous texture and create a new one).
 */
void Text::ChangeFont(SDL_Renderer *renderer, FONT fontName)
{
    this->fontName = fontName;
    SetText(renderer, text, renderType, fontSize, color, fontName);
}

/*
 * Changes the font size of a text (erases previous texture and create a new
 * one).
 */
void Text::ChangeFontSize(SDL_Renderer *renderer, int fontSize)
{
    this->fontSize = fontSize;
    SetText(renderer, text, renderType, fontSize, color, fontName);
}

/*
 * Changes the font color of a text (erases previous texture and create a new
 * one).
 */
void Text::ChangeColor(SDL_Renderer *renderer, SDL_Color color)
{
    this->color = color;
    SetText(renderer, text, renderType, fontSize, color, fontName);
}

/*
 * Changes the text (erases previous texture and create a new one).
 */
void Text::ChangeText(SDL_Renderer *renderer, std::string text)
{
    this->text = text;
    SetText(renderer, text, renderType, fontSize, color, fontName);
}

/*
 * Returns a pointer to a TTF_Font.
 */
static TTF_Font *GetFont(FONT fontName, int fontSize)
{
    std::string fontStr;

    switch(fontName)
    {
    case FONT_TIMES:
        fontStr = "fonts/times.ttf";
        break;
    case FONT_CALIBRI_REGULAR:
        fontStr = "fonts/Calibri Regular.ttf";
        break;
    case FONT_AGENCY_FB_REGULAR:
        fontStr = "fonts/agencyfb-regular.ttf";
        break;
    case FONT_AGENCY_FB_BOLD:
        fontStr = "fonts/agencyfb-boldcondensed.ttf";
        break;
    }

    TTF_Font *font = TTF_OpenFont(fontStr.c_str(), fontSize);

    if(font == nullptr)
    {
        std::cout << SDL_GetError() << " L: " << __LINE__ << " F: " << __FILE__
                  << "\n";
    }

    return font;
}

std::string Text::GetLabel() { return text; }

SDL_Texture *Text::GetTexture() { return texture; }

SDL_Texture *Text::GetShadowTexture() { return shadowTexture; }

bool Text::GetIsShadowEnabled() { return isShadowEnabled; }

/*
 * Free allocated memory.
 */
Text::~Text()
{
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }

    if(shadowTexture != nullptr)
    {
        SDL_DestroyTexture(shadowTexture);
    }
}
