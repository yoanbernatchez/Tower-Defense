/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-03
 * Project: Tower Defense
 * File: Image.cpp
 *
 * Brief: This class contains an implementation of "Image" that stores
 *        information about an image. This includes the source position of
 *        an image on a file and which file the image is in.
 */

#include "Image.h"
#include <iostream>
#include <string>

Image::Image(int imgId, int x, int y)
{
    dst = {x, y, 0, 0};
    savedDst = {0, 0, 0, 0};
    borderSize = 0;
    borderColor = {0, 0, 0};
    backgroundColor = {0, 0, 0};
    opacity = 255;
    isVisible = true;

    SetImage(imgId);
}

Image::Image(int imgId, int x, int y, int w, int h)
{
    fileNo = -1;

    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    isVisible = true;

    SetImage(imgId);
}

/*
 * Sets source coordinates and file number to match the image requested.
 */
void Image::SetImage(int imgId)
{
    switch(imgId)
    {
    /*----------------------------- HUD icons. ------------------------------*/
    case 0: /* Heart icon. */
        src.x = 0;
        src.y = 0;
        src.w = 58;
        src.h = 50;
        fileNo = 0;
        break;
    case 1: /* Coin icon. */
        src.x = 73;
        src.y = 0;
        src.w = 45;
        src.h = 53;
        fileNo = 0;
        break;
    case 2: /* Game title. */
        src.x = 133;
        src.y = 0;
        src.w = 646;
        src.h = 79;
        fileNo = 0;
        break;
    case 3: /* Robot. */
        src.x = 11;
        src.y = 94;
        src.w = 450;
        src.h = 480;
        fileNo = 0;
        break;
    /*---------------------------- Planet images ----------------------------*/
    case 10: /* Yellow sun. */
        src.x = 15;
        src.y = 13;
        src.w = 717;
        src.h = 713;
        fileNo = 1;
        break;
    case 11: /* Grand blue. */
        src.x = 775;
        src.y = 46;
        src.w = 490;
        src.h = 467;
        fileNo = 1;
        break;
    case 12: /* Dust giant. */
        src.x = 1298;
        src.y = 2;
        src.h = 972;
        src.w = 931;
        fileNo = 1;
        break;
    case 13: /* Methuselah. */
        src.x = 16;
        src.y = 738;
        src.h = 1272;
        src.w = 1246;
        fileNo = 1;
        break;
    case 14: /* Fire red. */
        src.x = 2075;
        src.y = 997;
        src.h = 900;
        src.w = 875;
        fileNo = 1;
        break;
    /*---------------------------- Turret icons -----------------------------*/
    case 30: /* Terrain cube. */
        break;
    case 31: /* Mini-gun turret. */
        src.x = 567;
        src.y = 100;
        src.w = 75;
        src.h = 64;
        fileNo = 0;
        break;
    default:
        std::cout << "Image set to an invalid id.\n";
        src.x = 0;
        src.y = 0;
        src.w = 0;
        src.h = 0;
        fileNo = 0;
        break;
    }

    id = imgId;

    if(dst.w == 0)
    {
        dst.w = src.w;
    }
    if(dst.h == 0)
    {
        dst.h = src.h;
    }
}

int Image::GetId() { return id; }

int Image::GetFileNo() { return fileNo; }

std::string Image::GetLabel()
{
    return std::to_string(GetId());
}
