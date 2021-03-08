/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-05
 * Project: Tower Defense
 * File: Renderer.cpp
 *
 * Brief: This class implements a Renderer class, used for rendering all the
 *        scene objects or level objects, as well as HUD components.
 */

#include "../~External Libraries/SDL2_gfxPrimitives.h"
#include "Renderer.h"

/**
 * @brief Draws a border around a destination rectangle.
 *
 * @param renderer:   Rendering target.
 * @param borderSize: Width in pixels of the border.
 * @param color:      Color of the border.
 * @param dst:        Destination rectangle to draw border around.
 */
static void DrawBorder(SDL_Renderer *renderer, int borderSize, SDL_Color color,
                       SDL_Rect dst);

/**
 * @brief Renders a text on screen along with its shadow if it has one.
 *
 * @param renderer:      Rendering target.
 * @param parentCompDst: Rendering destination of the text component's parent.
 * @param text:          Reference to the text to render.
 */
static void RenderText(SDL_Renderer *renderer, SDL_Rect parentCompDst,
                       std::shared_ptr<Text> &text);

/**
 * @brief Renders an image on screen.
 *
 * @param renderer: Rendering target.
 * @param textures: Textures object containing sprites and textures.
 * @param src:      Source coordinates of the image to render.
 * @param dst:      Destination coordinates of the image to render.
 * @param fileNo:   Image file number in which to find the image to render.
 */
static void RenderImage(SDL_Renderer *renderer, Textures &textures,
                        SDL_Rect src, SDL_Rect dst, int imgId);

Renderer::Renderer()
{
    renderDelay = 10;
}

/*
 * Draws a red elliptical range indicator around a point.
 */
void Renderer::DrawRange(SDL_Renderer *renderer, const Camera &camera,
                         int range, int x, int y)
{
    aaellipseRGBA(renderer, x, y, range * camera.GetZoom(),
                  range * ISO_V_SCALE * camera.GetZoom(), 255, 0, 0, 255);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

/*
 * Renders the elements of a scene. HUD, HUD components and black screen
 * transition.
 */
void Renderer::RenderSceneHud(Display &display, Scene &scene,
                              Textures &textures)
{
    /* Render the HUD and its components. */
    for(auto &i : scene.hud)
    {
        if(i.second->isVisible)
        {
            RenderHud(display.renderer, i.second, textures);
        }
    }

    /* Render the black screen (transition screen). */
    if(!scene.isTransitionDone)
    {
        SDL_Rect dest = {0, 0, display.GetWinLength(), display.GetWinHeight()};
        SDL_SetRenderDrawColor(display.renderer, 0, 0, 0, scene.opacity);
        SDL_RenderFillRect(display.renderer, &dest);
    }
}

/*
 * Renders a HUD and its components.
 */
void Renderer::RenderHud(SDL_Renderer *renderer, std::shared_ptr<Hud> &hud,
                         Textures &textures)
{
    if(hud != nullptr)
    {
        /* Draw HUD background. */
        if(hud->hasBackground)
        {
            SDL_SetRenderDrawColor(renderer,
                                   hud->backgroundColor.r,
                                   hud->backgroundColor.g,
                                   hud->backgroundColor.b,
                                   hud->backgroundColor.a);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect(renderer, &hud->dst);

            SDL_SetRenderDrawColor(renderer,
                                   hud->borderColor.r, hud->borderColor.g,
                                   hud->borderColor.b, hud->borderColor.a);
        }

        /* Draw HUD border. */
        if(hud->hasBorder)
        {
            DrawBorder(renderer, hud->borderSize, hud->borderColor, hud->dst);
        }

        /* Render image components. */
        for(auto &i : hud->images)
        {
            if(i.isVisible)
            {
                SDL_Rect imagePos;
                imagePos.x = hud->dst.x + i.dst.x;
                imagePos.y = hud->dst.y + i.dst.y;
                imagePos.w = i.dst.w;
                imagePos.h = i.dst.h;

                RenderImage(renderer, textures, i.src, imagePos,
                            i.GetFileNo());
            }
        }

        /* [Deprecated] Render portrait widget components.
        for(auto &i : hud->portraitWidgets)
        {
            if(i->isVisible)
            {
                SDL_Rect widgetPos;
                widgetPos.x = hud->dst.x + i->dst.x;
                widgetPos.y = hud->dst.y + i->dst.y;
                widgetPos.w = i->dst.w;
                widgetPos.h = i->dst.h;
                SDL_SetRenderDrawColor(display.renderer,
                                       i->backgroundColor.r,
                                       i->backgroundColor.g,
                                       i->backgroundColor.b,
                                       i->backgroundColor.a);
                SDL_RenderFillRect(display.renderer, &widgetPos);
                RenderPortraitWidget(display.renderer, i, textures, grid,
                                     widgetPos);
                DrawBorder(display.renderer, i->borderSize, i->borderColor,
                           widgetPos);
            }
        }
        */

        /* Render button components. */
        for(auto &i : hud->buttons)
        {
            if(i.isVisible)
            {
                SDL_Rect buttonPos;
                buttonPos.x = hud->dst.x + i.dst.x;
                buttonPos.y = hud->dst.y + i.dst.y;
                buttonPos.w = i.dst.w;
                buttonPos.h = i.dst.h;

                if(!i.isHovered)
                {
                    SDL_SetRenderDrawColor(renderer,
                                           i.backgroundColor.r,
                                           i.backgroundColor.g,
                                           i.backgroundColor.b,
                                           i.backgroundColor.a);
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderFillRect(renderer, &buttonPos);
                }
                else if(i.isHighlightable)
                {
                    SDL_SetRenderDrawColor(renderer,
                                           i.highlightColor.r,
                                           i.highlightColor.g,
                                           i.highlightColor.b,
                                           i.highlightColor.a);
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderFillRect(renderer, &buttonPos);
                }

                DrawBorder(renderer, 1, i.borderColor, buttonPos);

                for(auto &j : i.texts)
                {
                    if(j != nullptr && j->isVisible)
                    {
                        RenderText(renderer, buttonPos, j);
                    }
                }
            }
        }

        /* Render text components. */
        for(auto &i : hud->texts)
        {
            if(i->isVisible)
            {
                RenderText(renderer, hud->dst, i);
            }
        }
    }

    /* Reset render draw color to black. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

/*
 * Renders an image on screen.
 */
static void RenderImage(SDL_Renderer *renderer, Textures &textures,
                        SDL_Rect src, SDL_Rect dst, int fileNo)
{
    SDL_Texture *tempText = textures.GetTexture(renderer, TEXTURE_HUD, fileNo);

    if(tempText != nullptr)
    {
        SDL_RenderCopy(renderer, tempText, &src, &dst);
    }
}

/*
 * Renders a text on screen along with its shadow if it has one.
 */
static void RenderText(SDL_Renderer *renderer, SDL_Rect parentCompDst,
                       std::shared_ptr<Text> &text)
{
    if(text != nullptr)
    {
        SDL_Rect textPos;
        textPos.x = parentCompDst.x + text->dst.x + text->shadowOffsetX;
        textPos.y = parentCompDst.y + text->dst.y + text->shadowOffsetY;
        textPos.w = text->dst.w;
        textPos.h = text->dst.h;

        /* Render the text's shadow. */
        if(text->GetIsShadowEnabled() && text->GetShadowTexture() != nullptr)
        {
            SDL_RenderCopy(renderer, text->GetShadowTexture(),
                           &text->src, &textPos);
        }

        textPos.x = parentCompDst.x + text->dst.x;
        textPos.y = parentCompDst.y + text->dst.y;

        /* Render the text itself. */
        if(text->GetTexture() != nullptr)
        {
            SDL_RenderCopy(renderer, text->GetTexture(), &text->src, &textPos);
        }
    }
}

/*
 * Draws a border around a destination rectangle.
 */
static void DrawBorder(SDL_Renderer *renderer, int borderSize, SDL_Color color,
                       SDL_Rect dst)
{
    int x1, y1, x2, y2;
    int borderHalfSize = borderSize / 2;

    for(int i = 0; i < 4; i++)
    {
        /* Set border destination positions. */
        switch(i)
        {
        case 0: /* Left vertical border. */
            x1 = dst.x + borderHalfSize;
            y1 = dst.y;
            x2 = x1;
            y2 = y1 + dst.h - 1;
            break;
        case 1: /* Top horizontal border. */
            x1 = dst.x + borderSize;
            y1 = dst.y + borderHalfSize;
            x2 = dst.x + dst.w - borderSize - 1;
            y2 = y1;
            break;
        case 2: /* Right vertical border. */
            x1 = dst.x + dst.w - borderHalfSize;
            y1 = dst.y;
            x2 = x1;
            y2 = y1 + dst.h - 1;
            break;
        case 3: /* Bottom horizontal border. */
            x1 = dst.x + borderSize;
            y1 = dst.y + dst.h - borderHalfSize;
            x2 = dst.x + dst.w - borderSize - 1;
            y2 = y1;
            break;
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        thickLineRGBA(renderer, x1, y1, x2, y2, borderSize,
                      color.r, color.g, color.b, color.a);
    }
}

/*
 * Renders the entities associated with a cube.
 */
void Renderer::RenderEntities(SDL_Renderer *renderer, Level &level,
                              Textures &textures, int cubeX, int cubeY)
{
    /* Render units associated with the cube. */
    for(auto &i : level.units)
    {
        if(i.isVisible && i.cubeX == cubeX && i.cubeY == cubeY)
        {
            SDL_Texture *tempText = textures.GetTexture(renderer,
                                                        TEXTURE_UNIT, i.id);
            if(tempText != nullptr)
            {
                SDL_RenderCopy(renderer, tempText, &i.src, &i.dst);
            }
        }
    }

    /* Render turrets associated with the cube. */
    for(auto &i : level.towers)
    {
        if(i.cubeX == cubeX && i.cubeY == cubeY)
        {
            SDL_Texture *tempText = textures.GetTexture(renderer,
                                                        TEXTURE_TOWER, i.id);

            if(tempText != nullptr)
            {
                SDL_RenderCopy(renderer, tempText, &i.src, &i.dst);
            }
        }
    }
}

/*
 * Updates the source coordinates for cubes and entities.
 */
void Renderer::SetSrcPositions(Level &level, Camera &camera,
                               Textures &textures)
{
    int cubeSrcLength = textures.GetCubeSrcLength();
    int cubeSrcHeight = textures.GetCubeSrcHeight();
    int towerSrcLength = textures.towerSrcLength;
    int towerSrcHeight = textures.towerSrcHeight;
    int unitSrcLength = textures.unitSrcLength;
    int unitSrcHeight = textures.unitSrcHeight;

    /* Set cube src coordinates. */
    for(auto &i : level.grid.cubes)
    {
        i.src.w = cubeSrcLength;
        i.src.h = cubeSrcHeight;
        i.src.x = i.GetId() * cubeSrcLength;
        i.src.y = i.GetId() / textures.imgNbCubesLength * cubeSrcHeight;
    }

    /* Set tower src coordinates. */
    for(auto &i : level.towers)
    {
        i.src.w = towerSrcLength;
        i.src.h = towerSrcHeight;
        i.src.x = towerSrcLength * i.orientation;
        i.src.y = towerSrcHeight * (i.GetLevel() - 1);
    }

    /* Set unit src coordinates. */
    for(auto &i : level.units)
    {
        i.src.w = unitSrcLength;
        i.src.h = unitSrcHeight;

        /*
         * TODO: This needs to be updated when there will be more unit
         * sprites.
         */
        i.src.x = 0;
        i.src.y = 0;
    }

    level.isSrcUpdated = true;
}

/*
 * Updates the destination coordinates for cubes and entities.
 */
void Renderer::SetDstPositions(Level &level, Camera &camera,
                               Textures &textures)
{
    float cameraZoom = camera.GetZoom();

    int cubeSrcLength = textures.GetCubeSrcLength();
    int cubeSrcHeight = textures.GetCubeSrcHeight();
    int cubeMidX = textures.cubeSrcLength * cameraZoom / 2;
    int cubeMidY = textures.cubeSrcHeight * cameraZoom / 4;

    int towerDstWidth = textures.towerSrcLength * cameraZoom;
    int towerDstHeight = textures.towerSrcHeight * cameraZoom;

    int unitDstWidth = textures.unitSrcLength * cameraZoom;
    int unitDstHeight = textures.unitSrcHeight * cameraZoom;

    /* Set cubes dst coordinates. */
    for(auto &i : level.grid.cubes)
    {
        i.dst.w = cubeSrcLength * cameraZoom;
        i.dst.h = cubeSrcHeight * cameraZoom;
        i.dst.x = i.dst.w / 2 * (i.coordX - i.coordY) + camera.x;
        i.dst.y = i.dst.h / 4 * (i.coordX + i.coordY) + camera.y + i.coordZ *
                  cameraZoom;
    }

    /* Set towers dst coordinates. */
    for(auto &i : level.towers)
    {
        int cubeMidPosX = cubeMidX * (i.cubeX - i.cubeY);
        int cubeMidPosY = cubeMidY * (i.cubeX + i.cubeY);
        int towerCenterX = camera.x - i.dst.w / 2 + cubeMidX;
        int towerCenterY = camera.y - i.dst.h + cubeSrcHeight * cameraZoom / 2;

        i.dst.w = towerDstWidth;
        i.dst.h = towerDstHeight;
        i.dst.x = cubeMidPosX + towerCenterX;
        i.dst.y = cubeMidPosY + towerCenterY;
    }

    /* Set units dst coordinates. */
    for(auto &i : level.units)
    {
        int cubeCenterX = cubeMidX * (i.cubeX - i.cubeY);
        int cubeCenterY = cubeMidY + cubeMidY * (i.cubeY + i.cubeX);
        int unitPositionX = cubeMidX + i.x * cameraZoom + camera.x -
                            i.dst.w / 2;
        int unitPositionY = -i.dst.h + i.y * cameraZoom + camera.y;

        i.dst.w = unitDstWidth;
        i.dst.h = unitDstHeight;
        i.dst.x = cubeCenterX + unitPositionX;
        i.dst.y = cubeCenterY + unitPositionY;
    }
}

/*
 * Renders game elements such as the cubes, enemies and towers.
 */
void Renderer::RenderLevel(SDL_Renderer *renderer, Camera &camera,
                          Level &level, Textures &textures)
{
    int lowestRowPlusCol = level.grid.GetLowestRowPlusCol();
    int currentRowPlusCol = 0;
    bool isAllCubesRendered = false;

    /* Updates all the cube and entity src position when necessary. */
    if(!level.isSrcUpdated)
    {
        SetSrcPositions(level, camera, textures);
    }

    /* Update all cube and entity dst positions. */
    SetDstPositions(level, camera, textures);

    /* Render all the cubes along with their associated entities. */
    while(!isAllCubesRendered)
    {
        for(auto &i : level.grid.cubes)
        {
            if(!i.isRendered)
            {
                if(i.coordX + i.coordY == lowestRowPlusCol + currentRowPlusCol)
                {
                    SDL_Texture *tempText = textures.GetTexture(renderer,
                                                                TEXTURE_CUBE,
                                                                0);
                    /* Render the cube. */
                    if(tempText != nullptr)
                    {
                        SDL_RenderCopy(renderer, tempText, &i.src, &i.dst);
                    }

                    /* Render the entities associated with the cube. */
                    RenderEntities(renderer, level, textures,
                                   i.coordX, i.coordY);

                    i.isRendered = true;
                }
            }
        }

        /* Assume that all cubes have been rendered. */
        isAllCubesRendered = true;

        /* Check if all cubes really have been rendered. */
        for(auto const &i : level.grid.cubes)
        {
            if(!i.isRendered)
            {
                isAllCubesRendered = false;
                break;
            }
        }

        currentRowPlusCol++;
    }

    /* Render cube highlights. */
    for(auto &i : level.grid.cubes)
    {
        /* Render the cube's highlight. */
        if(i.isHighlighted)
        {
            SDL_Rect src = {0, 601, 205, 119};
            SDL_Rect dst = {i.dst.x, i.dst.y, i.dst.w, i.dst.h/2};
            SDL_RenderCopy(renderer,
                           textures.GetTexture(renderer, TEXTURE_HUD, 0),
                           &src, &dst);
        }
    }
    /* Render tower range indicators. */
    for(auto &i : level.towers)
    {
        if(i.isIndicatorActive)
        {
            Cube *cube = nullptr;

            for(auto &j : level.grid.cubes)
            {
                if(i.cubeX == j.coordX && i.cubeY == j.coordY)
                {
                    cube = &j;
                }
            }

            if(cube != nullptr)
            {
                int indicatorX = cube->dst.x + cube->dst.w / 2;
                int indicatorY = cube->dst.y + cube->dst.h / 4;
                DrawRange(renderer, camera, i.range, indicatorX, indicatorY);
            }
        }
    }

    /* Reset the isRendered tag. */
    for(auto &i : level.grid.cubes)
    {
        i.isRendered = false;
    }
}

/* [Deprecated] (Must be reworked)
static void RenderPortraitWidget(SDL_Renderer *renderer,
                                 std::shared_ptr<PortraitWidget>
                                 &portraitWidget,
                                 Textures &textures,
                                 SDL_Rect dst)
{
    SDL_Rect src = {0, 0, textures.unitSrcLength, textures.unitSrcHeight};

    if(portraitWidget != nullptr && portraitWidget->entity != nullptr)
    {

        if(portraitWidget->isPedestalActive)
        {
            int cubeX = portraitWidget->entity->cubeX;
            int cubeY = portraitWidget->entity->cubeY;
            int cubeId = 0;

            for(auto &i : grid.cubes)
            {
                if(i.coordX == cubeX && i.coordY == cubeY)
                {
                    cubeId = i.getId();
                }
            }

            SDL_RenderCopy(renderer,
                           textures.getTexture(renderer, TEXTURE_CUBE, cubeId),
                           &dst, &dst);
        }

        SDL_RenderCopy(renderer,
                       textures.GetTexture(renderer, TEXTURE_TOWER,
                                           portraitWidget->entity->id),
                       &src, &dst);
    }

}
*/
