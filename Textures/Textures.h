#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL.h>
#include <vector>

/**
 * @brief All the possible texture types, used to differentiate them while
 *        loading or getting textures.
 */
enum TEXTURETYPE {TEXTURE_CUBE, TEXTURE_TOWER, TEXTURE_UNIT, TEXTURE_HUD};

/**
 * @brief Texture structure used to associate each texture with a type and id.
 *
 * @param textureType: Type of the texture.
 * @param id:          Id associated with the texture.
 * @param text:        The texture.
 */
typedef struct Texture{
    int textureType;
    int id;
    SDL_Texture *text;
} Texture;

/**
 * @brief This class provides methods to load textures and unload them
 *        automatically
 */
class Textures
{
    public:
        std::vector<Texture> textures;
        int imgNbCubesLength;
        int imgNbCubesHeight;
        int cubeSrcLength;
        int cubeSrcHeight;
        int nbTowersPerTexture;
        int nbTowerEvoPerTexture;
        int towerSrcLength;
        int towerSrcHeight;
        int nbUnitsPerTexture;
        int unitSrcLength;
        int unitSrcHeight;

        /**
         * @brief Frees all the textures previously allocated.
         */
        Textures();
        virtual ~Textures();

        /**
         * @brief Returns the texture associated with a texture type and object
         *        id.
         *
         * @param renderer:    Rendering target.
         * @param textureType: Type of the sprite/texture to load.
         * @param textureId:   The id of the object we want the sprite/texture
         *                     of.
         *
         * @return The sprite/texture associated with the object id and type.
         */
        SDL_Texture *GetTexture(SDL_Renderer *renderer, int textureType,
                                int objectId);

        /* Getters. */
        int GetImgNbCubesLength();
        int GetImgNbCubesHeight();
        int GetCubeSrcLength();
        int GetCubeSrcHeight();

    private:
        /**
         * @brief Loads a sprite/texture according to the texture type and id.
         *
         * @param renderer:    Rendering target.
         * @param textureType: Type of the sprite/texture to load.
         * @param textureId:   The id of the sprite/texture image to load.
         */
        void LoadTexture(SDL_Renderer *renderer, int textureType,
                         int textureId);
};

#endif // TEXTURES_H
