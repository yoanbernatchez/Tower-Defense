/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-24
 * Project: Tower Defense
 * File: Scene.cpp
 *
 * Brief: This class implements the Scene class, which acts as a container
 *        for graphical and level data. Gives methods to load scenes such
 *        as Main Menu, Level Selection, etc.
 */

#include "Scene.h"
#include <vector>
#include <string>

Scene::Scene(SDL_Renderer *renderer, SCENE sceneId, int winSizeX, int winSizeY)
{
    opacity = 0;
    isTransitionDone = true;
    LoadScenePreset(renderer, sceneId, winSizeX, winSizeY);
}

/*
 * Loads a scene preset.
 */
void Scene::LoadScenePreset(SDL_Renderer *renderer, SCENE sceneId,
                            int winSizeX, int winSizeY)
{
    /* Unload previous scene. */
    hud.clear();

    /* Load scene. */
    switch(sceneId)
    {
    case SCENE_MAIN_MENU:
        LoadSceneMainMenu(renderer, winSizeX, winSizeY);
        break;
    case SCENE_LEVEL_SELECTION:
        LoadSceneLevelSelection(renderer, winSizeX, winSizeY);
        break;
    case SCENE_LEVEL:
        LoadSceneLevel(renderer, winSizeX, winSizeY);
        break;
    case SCENE_SETTINGS:
        break;
    }

    this->sceneId = sceneId;
}

/*
 * Loads the Main Menu scene presets.
 */
void Scene::LoadSceneMainMenu(SDL_Renderer *renderer, int winSizeX,
                              int winSizeY)
{
    /* Creating the HUD. */
    SDL_Rect buttonsHudPos = {0, 0, winSizeX, winSizeY};
    std::shared_ptr<Hud> buttonsHud(new Hud(buttonsHudPos, false,
                                            SDL_COLOR_BLACK, 0, false,
                                            SDL_COLOR_BLACK));
    hud.emplace(HUD_BUTTONS, buttonsHud);

    /* Setting up the main menu buttons. */
    Button menuButton(4, SDL_COLOR_FUSHIA, SDL_COLOR_DARK_RED, 200, 50);
    menuButton.dst.y = 200;

    /* Add four buttons. */
    for(int i = 0; i < 4; i++)
    {
        hud[HUD_BUTTONS]->buttons.push_back(menuButton);
        hud[HUD_BUTTONS]->buttons[i].dst.y = menuButton.dst.y
                                             + ((menuButton.dst.h + 50)* i);
        hud[HUD_BUTTONS]->buttons[i].dst.x = 200;
    }

    /* Add text to menu buttons. */
    hud[HUD_BUTTONS]->buttons[0].AddText(renderer, "New Game", 36,
                                         SDL_COLOR_LIGHT_WHITE,
                                         FONT_AGENCY_FB_REGULAR);
    hud[HUD_BUTTONS]->buttons[1].AddText(renderer, "Continue", 36,
                                         SDL_COLOR_LIGHT_WHITE,
                                         FONT_AGENCY_FB_REGULAR);
    hud[HUD_BUTTONS]->buttons[2].AddText(renderer, "Settings", 36,
                                         SDL_COLOR_LIGHT_WHITE,
                                         FONT_AGENCY_FB_REGULAR);
    hud[HUD_BUTTONS]->buttons[3].AddText(renderer, "Exit", 36,
                                         SDL_COLOR_LIGHT_WHITE,
                                         FONT_AGENCY_FB_REGULAR);

    for(int i = 0; i < 4; i++)
    {
        hud[HUD_BUTTONS]->buttons[i].CenterTextById(0);
    }

    /* Add planet images. */
    hud[HUD_BUTTONS]->AddImage(10, winSizeX / 2 - 100, winSizeY / 2 - 100,
                               100, 100);
    hud[HUD_BUTTONS]->AddImage(11, 400, 70, 30, 30);
    hud[HUD_BUTTONS]->AddImage(12, 600, 150, 50, 50);
    hud[HUD_BUTTONS]->AddImage(13, 700, 150, 100, 100);
    hud[HUD_BUTTONS]->AddImage(14, 800, 300, 900, 875);

    /* Add game title image. */
    hud[HUD_BUTTONS]->AddImage(2, 10, 10);
}


/*
 * Loads the Level Selection scene presets.
 */
void Scene::LoadSceneLevelSelection(SDL_Renderer *renderer, int winSizeX,
                                    int winSizeY)
{
    /* Creating the HUDs. */
    SDL_Rect hudPos = {0, 0, 0, 0};

    SDL_Color txtColor = {220,220,220,255};

    std::shared_ptr<Hud> planetHud(new Hud(hudPos, false, SDL_COLOR_FUSHIA, 0,
                                           false, SDL_COLOR_DARK_RED));
    std::shared_ptr<Hud> infoHud(new Hud(hudPos, true, SDL_COLOR_FUSHIA, 1,
                                         true, SDL_COLOR_DARK_RED));
    std::shared_ptr<Hud> zone1Hud(new Hud(hudPos, true, SDL_COLOR_FUSHIA,
                                          1, true, SDL_COLOR_DARK_RED));
    std::shared_ptr<Hud> zone2Hud(new Hud(hudPos, true, SDL_COLOR_FUSHIA,
                                          1, true, SDL_COLOR_DARK_RED));

    hud.emplace(HUD_PLANET, planetHud);
    hud.emplace(HUD_ZONE1, zone1Hud);
    hud.emplace(HUD_ZONE2, zone2Hud);
    hud.emplace(HUD_PLANET_INFO, infoHud);

    /*-------------------------- Planets HUD setup --------------------------*/

    /* Add images for all the planets. */
    hud[HUD_PLANET]->AddImage(10, 0, 0, 400, 400);
    hud[HUD_PLANET]->AddImage(10, 0, 0, 250, 250);
    hud[HUD_PLANET]->AddImage(10, 0, 0, 250, 250);

    /* Add image for the robot. */
    hud[HUD_PLANET]->AddImage(3, 0, 0);
    hud[HUD_PLANET]->images[3].dst.w = hud[HUD_PLANET]->images[3].dst.w
                                       * 35 / 100;
    hud[HUD_PLANET]->images[3].dst.h = hud[HUD_PLANET]->images[3].dst.h
                                       * 35 / 100;

    /*-------------------------- Zone HUDs setup ----------------------------*/
    for(int i = 0; i < 2; i++)
    {
        HUD_PRESETS_LEVEL_SELECT CURR_ZONE;

        switch(i)
        {
        case 0:
            CURR_ZONE = HUD_ZONE1;
            break;
        case 1:
            CURR_ZONE = HUD_ZONE2;
            break;
        }

        Button playButton(4, SDL_COLOR_FUSHIA, SDL_COLOR_DARK_RED, 220/2, 30);

        /* Zone mission text. */
        hud[CURR_ZONE]->AddText(renderer, " ", 28, SDL_COLOR_LIGHT_WHITE,
                                FONT_AGENCY_FB_REGULAR);
        hud[CURR_ZONE]->texts[0]->dst.x = 5;
        hud[CURR_ZONE]->texts[0]->dst.y = 5;

        /* Zone threat level text. */
        hud[CURR_ZONE]->AddText(renderer, " ", 20, SDL_COLOR_WHITE,
                                FONT_AGENCY_FB_REGULAR);
        hud[CURR_ZONE]->texts[1]->dst.x = 5;
        hud[CURR_ZONE]->texts[1]->dst.y = 40;

        /* Zone description text. */
        hud[CURR_ZONE]->AddText(renderer, " ", 20, SDL_COLOR_LIGHT_WHITE,
                                FONT_AGENCY_FB_REGULAR);
        hud[CURR_ZONE]->texts[2]->Wrap(renderer, 210);
        hud[CURR_ZONE]->texts[2]->dst.x = 5;
        hud[CURR_ZONE]->texts[2]->dst.y = 70;

        /* Zone play button. */
        hud[CURR_ZONE]->buttons.push_back(playButton);
        hud[CURR_ZONE]->buttons[0].dst.x = 220/2;
        hud[CURR_ZONE]->buttons[0].dst.y = 150;
        hud[CURR_ZONE]->buttons[0].AddText(renderer, " ", 20, SDL_COLOR_WHITE,
                                           FONT_AGENCY_FB_REGULAR);
        hud[CURR_ZONE]->buttons[0].CenterTextById(0);

        hud[CURR_ZONE]->buttons[0].isVisible = false;
    }

    /*------------------------- Planet info HUD setup -----------------------*/

    /* Planet name. */
    hud[HUD_PLANET_INFO]->AddText(renderer, " ", 28, SDL_COLOR_LIGHT_WHITE,
                                  FONT_AGENCY_FB_REGULAR);
    hud[HUD_PLANET_INFO]->texts[0]->dst.x = 5;
    hud[HUD_PLANET_INFO]->texts[0]->dst.y = 5;

    /* Planet description. */
    hud[HUD_PLANET_INFO]->AddText(renderer, " ", 20, txtColor,
                                  FONT_AGENCY_FB_REGULAR);
    hud[HUD_PLANET_INFO]->texts[1]->Wrap(renderer, 490);
    hud[HUD_PLANET_INFO]->texts[1]->dst.x = 5;
    hud[HUD_PLANET_INFO]->texts[1]->dst.y = 45;

    /* Add planet transition buttons. */
    Button nextPlanetButton(4, SDL_COLOR_FUSHIA, SDL_COLOR_DARK_RED, 40, 130);
    hud[HUD_PLANET_INFO]->buttons.push_back(nextPlanetButton);
    hud[HUD_PLANET_INFO]->buttons.push_back(nextPlanetButton);
    hud[HUD_PLANET_INFO]->buttons[0].dst.x = - hud[HUD_PLANET_INFO]->
                                             buttons[0].dst.w;
    hud[HUD_PLANET_INFO]->buttons[1].dst.x = 500;

    /* Text for the left planet transition button. */
    hud[HUD_PLANET_INFO]->buttons[0].AddText(renderer, "<", 60,
                                             SDL_COLOR_WHITE,
                                             FONT_AGENCY_FB_REGULAR);
    hud[HUD_PLANET_INFO]->buttons[0].CenterTextById(0);
    hud[HUD_PLANET_INFO]->buttons[0].isVisible = false;

    /* Text for the right planet transition button. */
    hud[HUD_PLANET_INFO]->buttons[1].AddText(renderer, ">", 60,
                                             SDL_COLOR_WHITE,
                                             FONT_AGENCY_FB_REGULAR);
    hud[HUD_PLANET_INFO]->buttons[1].CenterTextById(0);
    hud[HUD_PLANET_INFO]->buttons[1].isVisible = false;
}

/*
 * Loads the Level scene presets.
 */
void Scene::LoadSceneLevel(SDL_Renderer *renderer, int winSizeX, int winSizeY)
{
    int nbButtons = 6;
    int buttonPadding = 15;

    /* Setting up HUD positions. */
    SDL_Rect infoHudPos = {winSizeX - 293 + 6, winSizeY - 216 + 6, 293, 216};
    SDL_Rect towerHudPos = {0,
                            winSizeY - 115 + 6,
                            nbButtons * (buttonPadding + 90) + 50 - 15,
                            115};
    towerHudPos.x = winSizeX/2 - towerHudPos.w/2;
    SDL_Rect comsHudPos = {-6 - 1, winSizeY - 216 + 6, 294 + 1, 216};
    SDL_Rect statusHudPos = {0, 0, 210, 30};
    SDL_Rect waveHudPos = {winSizeX/2, 0, 200, 50};
    SDL_Rect errorHudPos = {winSizeX/2 - infoHudPos.w, towerHudPos.y - 26,
                            293, 26};

    /* Creating the HUDs. */
    std::shared_ptr<Hud> infoHud(new Hud(infoHudPos, true, SDL_COLOR_FUSHIA,
                                         6, true, SDL_COLOR_DARK_RED));
    std::shared_ptr<Hud> towerHud(new Hud(towerHudPos, true, SDL_COLOR_FUSHIA,
                                          6, true, SDL_COLOR_DARK_RED));
    std::shared_ptr<Hud> comsHud(new Hud(comsHudPos, true, SDL_COLOR_FUSHIA,
                                         6, true, SDL_COLOR_DARK_RED));
    std::shared_ptr<Hud> statusHud(new Hud(statusHudPos, false,
                                           SDL_COLOR_FUSHIA, 0, true,
                                           SDL_COLOR_DARK_RED));
    std::shared_ptr<Hud> waveHud(new Hud(waveHudPos, false, SDL_COLOR_FUSHIA,
                                         0, false, SDL_COLOR_DARK_RED));
    std::shared_ptr<Hud> errorHud(new Hud(errorHudPos, false, SDL_COLOR_RED,
                                          0, false, SDL_COLOR_RED));

    /*---------------------------- Info HUD setup ---------------------------*/

    hud.emplace(HUD_INFO, infoHud);

    /* Adding stat description texts. */
    hud[HUD_INFO]->AddText(renderer, "damage :", 24, SDL_COLOR_WHITE,
                           FONT_AGENCY_FB_REGULAR);
    hud[HUD_INFO]->AddText(renderer, "range :", 24, SDL_COLOR_WHITE,
                           FONT_AGENCY_FB_REGULAR);
    hud[HUD_INFO]->AddText(renderer, "atk. speed :", 24, SDL_COLOR_WHITE,
                           FONT_AGENCY_FB_REGULAR);
    hud[HUD_INFO]->AddText(renderer, "dot :", 24, SDL_COLOR_WHITE,
                           FONT_AGENCY_FB_REGULAR);
    hud[HUD_INFO]->AddText(renderer, "dot dur. :", 24, SDL_COLOR_WHITE,
                           FONT_AGENCY_FB_REGULAR);

    /* Adding stat texts. */
    for(int i = 0; i < 5; i++)
    {
        hud[HUD_INFO]->AddText(renderer, " ", 24, SDL_COLOR_WHITE,
                               FONT_AGENCY_FB_REGULAR);
    }

    /* Setting up stat description text positions. */
    for(int i = 0; i < 5; i++)
    {
        hud[HUD_INFO]->texts[i]->dst.x = hud[HUD_INFO]->dst.w/2
                                         - hud[HUD_INFO]->texts[i]->dst.w - 40;
        hud[HUD_INFO]->texts[i]->dst.y = 20 + 24 * i;
    }

    /* Setting up stat text positions. */
    for(int i = 0; i < 5; i++)
    {
        hud[HUD_INFO]->texts[5+i]->dst.x = hud[HUD_INFO]->dst.w/2
                                           - hud[HUD_INFO]->texts[5 + i]->dst.w
                                           - 40;
        hud[HUD_INFO]->texts[5+i]->dst.y = 20 + 24 * i;
    }

    /* Add texts for selling value and upgrading price of the tower. */
    hud[HUD_INFO]->AddText(renderer, "90", 18, SDL_COLOR_YELLOW,
                           FONT_AGENCY_FB_REGULAR);
    hud[HUD_INFO]->AddText(renderer, "200", 18, SDL_COLOR_YELLOW,
                           FONT_AGENCY_FB_REGULAR);

    /* Give shadows to all the texts. */
    for(int i = 0; i < 12; i++)
    {
        hud[HUD_INFO]->texts[i]->EnableShadow(renderer, 1, 1, SDL_COLOR_BLACK);
    }

    // Setting up buttons
    Button infoButton(4, SDL_COLOR_FUSHIA, SDL_COLOR_DARK_RED, 118, 30);
    hud[HUD_INFO]->buttons.push_back(infoButton);
    hud[HUD_INFO]->buttons.push_back(infoButton);

    /* Adding text to the Sell button. */
    hud[HUD_INFO]->buttons[0].AddText(renderer, "Sell", 25, SDL_COLOR_WHITE,
                                      FONT_AGENCY_FB_REGULAR);
    hud[HUD_INFO]->buttons[0].dst.x = 20;
    hud[HUD_INFO]->buttons[0].dst.y = hud[HUD_INFO]->dst.h
                                      - hud[HUD_INFO]->buttons[0].dst.h - 26;
    hud[HUD_INFO]->buttons[0].CenterTextById(0);

    /* Adding text to the Upgrade button. */
    hud[HUD_INFO]->buttons[1].AddText(renderer, "Upgrade", 25, SDL_COLOR_WHITE,
                                      FONT_AGENCY_FB_REGULAR);
    hud[HUD_INFO]->buttons[1].dst.x = hud[0]->dst.w
                                      - hud[0]->buttons[1].dst.w - 20;
    hud[HUD_INFO]->buttons[1].dst.y = hud[0]->buttons[0].dst.y;
    hud[HUD_INFO]->buttons[1].CenterTextById(0);

    /* Setting the selling value position. */
    hud[HUD_INFO]->texts[10]->dst.x = hud[HUD_INFO]->buttons[0].dst.x
                                      + hud[HUD_INFO]->buttons[0].dst.w
                                      - hud[HUD_INFO]->texts[10]->dst.w;
    hud[HUD_INFO]->texts[10]->dst.y = hud[HUD_INFO]->buttons[0].dst.y
                                      + hud[HUD_INFO]->buttons[0].dst.h;

    /* Setting the upgrading cost position. */
    hud[HUD_INFO]->texts[11]->dst.x = hud[HUD_INFO]->buttons[1].dst.x
                                      + hud[HUD_INFO]->buttons[1].dst.w
                                      - hud[HUD_INFO]->texts[11]->dst.w;
    hud[HUD_INFO]->texts[11]->dst.y = hud[HUD_INFO]->texts[10]->dst.y;

    /* [DEPRECATED] Setting portrait widget */
    /*
    hud[HUD_INFO]->AddPortraitWidget(nullptr, 6, SDL_COLOR_FUSHIA,
                                       SDL_COLOR_DARK_RED, 120, 120);
    hud[HUD_INFO]->portraitWidgets[0]->dst.x = hud[HUD_INFO]->dst.w
                                               - hud[HUD_INFO]->
                                               portraitWidgets[0]->dst.w;
    */

    hud[HUD_INFO]->isVisible = false;

    /*--------------------------- Tower HUD setup ---------------------------*/

    hud.emplace(HUD_TOWER, towerHud);
    hud.emplace(HUD_COMS, comsHud);

    Button buttonTower(4, SDL_COLOR_FUSHIA, SDL_COLOR_DARK_RED, 90, 75);

    /* Add buttons for towers. */
    for(int i = 0; i < 6; i++)
    {
        hud[HUD_TOWER]->buttons.push_back(buttonTower);
        hud[HUD_TOWER]->buttons[i].dst.y = 15;
        hud[HUD_TOWER]->buttons[i].dst.x = 25 + (buttonTower.dst.w + 15) * i;
    }

    /* Add price texts for the towers. */
    hud[HUD_TOWER]->buttons[0].AddText(renderer, "50", 16, SDL_COLOR_YELLOW,
                                       FONT_AGENCY_FB_REGULAR);
    hud[HUD_TOWER]->buttons[1].AddText(renderer, "150", 16, SDL_COLOR_YELLOW,
                                       FONT_AGENCY_FB_REGULAR);
    hud[HUD_TOWER]->buttons[2].AddText(renderer, "250", 16, SDL_COLOR_YELLOW,
                                       FONT_AGENCY_FB_REGULAR);
    hud[HUD_TOWER]->buttons[3].AddText(renderer, "300", 16, SDL_COLOR_YELLOW,
                                       FONT_AGENCY_FB_REGULAR);
    hud[HUD_TOWER]->buttons[4].AddText(renderer, "350", 16, SDL_COLOR_YELLOW,
                                       FONT_AGENCY_FB_REGULAR);
    hud[HUD_TOWER]->buttons[5].AddText(renderer, "400", 16, SDL_COLOR_YELLOW,
                                       FONT_AGENCY_FB_REGULAR);

    for(auto &i: hud[HUD_TOWER]->buttons)
    {
        i.texts[0]->EnableShadow(renderer, 1, 1, SDL_COLOR_BLACK);
    }

    /* Center price texts horizontally. */
    for(auto &i : hud[HUD_TOWER]->buttons)
    {
        i.CenterTextById(0);
        i.texts[0]->dst.y = i.dst.h - i.texts[0]->dst.h;
    }

    /* Add tower image previews to the tower buttons. */
    hud[HUD_TOWER]->AddImage(31, 0, 0);
    hud[HUD_TOWER]->images[0].dst.x = hud[HUD_TOWER]->buttons[1].dst.x
                                      + hud[HUD_TOWER]->buttons[1].dst.w/2
                                      - hud[HUD_TOWER]->images[0].dst.w/2;
    hud[HUD_TOWER]->images[0].dst.y = hud[HUD_TOWER]->buttons[1].dst.y
                                      + hud[HUD_TOWER]->buttons[1].dst.h/2
                                      - hud[HUD_TOWER]->images[0].dst.h/2;

    /*---------------------------- Status HUD setup -------------------------*/

    hud.emplace(HUD_STATUS, statusHud);
    hud[HUD_STATUS]->backgroundColor.a = 160;

    /* Add status text for health and currency. */
    hud[HUD_STATUS]->AddText(renderer, "100/100", 28, SDL_COLOR_RED,
                             FONT_AGENCY_FB_REGULAR);
    hud[HUD_STATUS]->AddText(renderer, "500", 28, SDL_COLOR_YELLOW,
                             FONT_AGENCY_FB_REGULAR);
    hud[HUD_STATUS]->texts[0]->dst.x = 40;
    hud[HUD_STATUS]->texts[1]->dst.x = 170;

    for(int i = 0; i < 2; i++)
    {
        hud[HUD_STATUS]->texts[i]->EnableShadow(renderer, 1, 1,
                                                SDL_COLOR_BLACK);
    }

    /* Add heart icon and currency icon. */
    hud[HUD_STATUS]->AddImage(0, 0, 0, 30, 30);
    hud[HUD_STATUS]->AddImage(1, 130, 0, 30, 30);

    /*---------------------------- Wave HUD setup ---------------------------*/

    hud.emplace(HUD_WAVE, waveHud);

    /* Add a wave number text. */
    hud[HUD_WAVE]->AddText(renderer, " ", 60, SDL_COLOR_LIGHT_GREY,
                           FONT_AGENCY_FB_REGULAR);
    hud[HUD_WAVE]->texts[0]->EnableShadow(renderer, 2, 2, SDL_COLOR_WHITE);

    /*---------------------------- Error HUD setup --------------------------*/

    hud.emplace(HUD_ERROR, errorHud);

    /* Add an error text. */
    hud[HUD_ERROR]->AddText(renderer, " ", 22, SDL_COLOR_RED,
                            FONT_AGENCY_FB_REGULAR);
    hud[HUD_ERROR]->texts[0]->EnableShadow(renderer, 1, 1, SDL_COLOR_BLACK);
}
