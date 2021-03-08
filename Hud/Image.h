#ifndef IMAGE_H
#define IMAGE_H

#include "HudComponent.h"

/**
 * @brief This class stores information about an image (source position of
 *        the image on a file and which file the image is in).
 */
class Image : public HudComponent
{
    public:
        SDL_Rect src;

        Image(int imgId, int x, int y);
        Image(int imgId, int x, int y, int w, int h);

        /**
         * @brief Sets source coordinates and file number to match the image
         *        requested.
         *
         * @param imgId: Image id to get the source coordinates for.
         */
        void SetImage(int imgId);

        /* Getters. */
        std::string GetLabel();
        int GetId();
        int GetFileNo();

    private:
        int id;
        int fileNo;
};

#endif // IMAGE_H
