/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-01-30
 * Project: Tower Defense
 * File: Textures.cpp
 *
 * Brief: This source file provides methods to load textures and unload them
 *        automatically. This system loads only the required textures, which
 *        helps with RAM usage.
 */

#include "Textures.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

Textures::Textures()
{
    imgNbCubesLength = 3;
    imgNbCubesHeight = 3;
    cubeSrcLength = 204;
    cubeSrcHeight = 234;
    nbTowersPerTexture = 1;
    nbTowerEvoPerTexture = 4;
    towerSrcLength = 200;
    towerSrcHeight = 200;
    nbUnitsPerTexture = 4;
    unitSrcLength = 64;
    unitSrcHeight = 64;
}

/*
 * Returns the texture associated with a texture type and object id.
 */
SDL_Texture *Textures::GetTexture(SDL_Renderer *renderer, int textureType,
                                   int objectId)
{
    int textureId = -1;

    /* Define the id of the texture to fetch/load. */
    switch(textureType)
    {
    case TEXTURE_CUBE:
        textureId = objectId / (imgNbCubesLength * imgNbCubesHeight);
        break;
    case TEXTURE_TOWER:
        textureId = objectId / nbTowersPerTexture;
        break;
    case TEXTURE_UNIT:
        textureId = objectId / nbUnitsPerTexture;
        break;
    case TEXTURE_HUD:
        textureId = objectId;
        break;
    }

    /* Find and return the texture. */
    for(auto const &i : textures)
    {
        if(i.textureType == textureType && i.id == textureId)
        {
            return i.text;
        }
    }

    /* If the texture wasn't loaded, load it and return it. */
    LoadTexture(renderer, textureType, textureId);

    for(auto const &i : textures)
    {
        if(i.textureType == textureType && i.id == textureId)
        {
            return i.text;
        }
    }

    return NULL;
}

/*
 * Loads a sprite/texture according to the texture type and id.
 */
void Textures::LoadTexture(SDL_Renderer *renderer, int textureType,
                           int textureId)
{
    SDL_Surface *surf = nullptr;
    Texture text;
    std::string fileName;

    /* Define the file's location. */
    switch(textureType)
    {
    case TEXTURE_CUBE:
        fileName = "assets/cubes/";
        break;
    case TEXTURE_TOWER:
        fileName = "assets/towers/";
        break;
    case TEXTURE_UNIT:
        fileName = "assets/units/";
        break;
    case TEXTURE_HUD:
        fileName = "assets/hud/";
    }

    /* Define the file's name. */
    text.textureType = textureType;
    text.id = textureId;
    text.text = nullptr;

    fileName.append(std::to_string(textureId));
    fileName.append(".png");

    /* Load sprite/texture. */
    surf = IMG_Load(fileName.c_str());

    if(surf == nullptr)
    {
        std::cout << SDL_GetError() << " L: " << __LINE__ << " F: "
                  << __FILE__ << "\n";
    }

    text.text = SDL_CreateTextureFromSurface(renderer, surf);

    if(text.text == nullptr)
    {
        std::cout << SDL_GetError() << " L: " << __LINE__ << " F: "
                  << __FILE__ << "\n";
    }

    textures.push_back(text);

    SDL_FreeSurface(surf);
}

int Textures::GetImgNbCubesLength() { return imgNbCubesLength; }

int Textures::GetImgNbCubesHeight() { return imgNbCubesHeight; }

int Textures::GetCubeSrcLength() { return cubeSrcLength; }

int Textures::GetCubeSrcHeight() { return cubeSrcHeight; }

/*
 * Frees all the textures previously allocated.
 */
Textures::~Textures()
{
    for(auto &i : textures)
    {
        SDL_DestroyTexture(i.text);
    }
}
