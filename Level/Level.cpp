/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-01-20
 * Project: Tower Defense
 * File: Level.cpp
 *
 * Brief: This class contains an implementation of the Level class, used for
 *        loading and storing level informations from file such as wave data,
 *        cube data, etc.
 */

#include "Level.h"

#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief Advances to a section in a level file.
 *
 * @param levelFile:   Level file reference (already opened).
 * @param sectionName: Section name to find in the level file.
 */
static void AdvanceToSection(std::ifstream &levelFile,
                             std::string sectionName);

Level::Level()
{
    spawnPoint = {0, 0};
    destination = {0, 0};
    timeBetweenWaves = 10;
    isSrcUpdated = false;
}

/*
 * Advances to a section in a level file.
 */
static void AdvanceToSection(std::ifstream &levelFile, std::string sectionName)
{
    std::string line;

    if(levelFile.is_open())
    {
        /* Advance to the data section. */
        while(std::getline(levelFile, line))
        {
            if(line.find(sectionName) != std::string::npos)
            {
                break;
            }
        }
    }
}

/*
 * Loads wave information from a level file.
 */
void Level::LoadWave(int levelId, int wave)
{
    std::ifstream levelFile;
    std::string fileName = "levels/";
    std::string waveName = "WAVE ";
    std::string line;
    std::istringstream iline;
    int nbUnits = 0;
    int id = 0;
    int hp = 0;
    int movSpeed = 0;
    int goldValue = 0;
    int timeBetween = 0;
    int spawnTime = 0;

    fileName.append(std::to_string(levelId));
    fileName.append(".txt");

    waveName.append(std::to_string(wave));
    waveName.append(" {");

    levelFile.open(fileName);

    AdvanceToSection(levelFile, waveName);

    /* Load units. */
    while(true)
    {
        std::getline(levelFile, line);

        if(line.compare("}") == 0)
        {
            break;
        }

        iline.str(line);

        iline >> nbUnits >> id >> hp >> movSpeed >> goldValue >> timeBetween
              >> spawnTime;

        for(int i = 0; i < nbUnits; i++)
        {
            Unit unit(id, hp, movSpeed, goldValue,
                      spawnTime + i * timeBetween);
            unit.cubeX = spawnPoint.x;
            unit.cubeY = spawnPoint.y;
            units.push_back(unit);
        }

        iline.clear();
    }

    levelFile.close();
}

/*
 * Loads the spawn points and destination points of the level.
 */
void Level::LoadSpawnPointAndDestination(int levelId)
{
    std::ifstream levelFile;
    std::string fileName = "levels/";
    std::string line;
    char separator;

    fileName.append(std::to_string(levelId));
    fileName.append(".txt");

    levelFile.open(fileName);

    /* Load spawn points. */
    AdvanceToSection(levelFile, "SPAWNPOINTS {");

    std::getline(levelFile, line);
    std::istringstream iline(line);
    iline >> spawnPoint.x >> separator >> spawnPoint.y;

    /* Load destination points. */
    AdvanceToSection(levelFile, "DESTINATIONS {");

    std::getline(levelFile, line);
    iline.clear();
    iline.str(line);
    iline >> destination.x >> separator >> destination.y;

    levelFile.close();
}

/*
 * Loads the level's cubes data.
 */
void Level::LoadLevel(int levelId)
{
    std::ifstream levelFile;
    std::string fileName = "levels/";
    std::string line;
    int x = 0;
    int y = 0;
    int z = 0;
    int id = 0;
    char separator;

    fileName.append(std::to_string(levelId));
    fileName.append(".txt");

    levelFile.open(fileName);

    AdvanceToSection(levelFile, "CUBES {");

    /* Get data for all cubes. */
    while(true)
    {
        std::getline(levelFile, line);

        if(line.compare("}") == 0)
        {
            break;
        }
        else if(line.empty() || levelFile.bad() || levelFile.eof())
        {
            std::cout << "Level file: CUBES section is corrupted or not"
                         "formatted correctly.\n";
            break;
        }

        std::istringstream iline(line);
        iline >> x >> separator;

        while(iline.peek() != EOF)
        {
            iline >> y >> z >> id >> separator;

            grid.AddCube(x, y, z, id);

            if(separator == ';')
            {
                break;
            }
            else if(separator != ',')
            {
                std::cout << "Level file: CUBES section is corrupted or not"
                             "formatted correctly.\n";
            }
        }
    }

    levelFile.close();
    LoadSpawnPointAndDestination(levelId);
}

/*
 * Returns the level's description.
 */
std::string Level::GetLevelDescription(int levelId)
{
    std::string levelDesc = "";
    std::ifstream levelFile;
    std::string fileName = "levels/";
    std::string line;

    fileName.append(std::to_string(levelId));
    fileName.append(".txt");

    levelFile.open(fileName);

    AdvanceToSection(levelFile, "DESCRIPTION {");

    std::getline(levelFile, line);

    /* Get description. */
    std::getline(levelFile, line);
    levelDesc = line;

    levelFile.close();

    return levelDesc;
}

/*
 * Returns the threat description of a level.
 */
std::string Level::GetLevelThreat(int levelId)
{
    std::string levelThreat;
    std::ifstream levelFile;
    std::string fileName = "levels/";
    std::string line;

    fileName.append(std::to_string(levelId));
    fileName.append(".txt");

    levelFile.open(fileName);

    AdvanceToSection(levelFile, "DESCRIPTION {");

    /* Get threat description. */
    std::getline(levelFile, line);
    levelThreat = line;

    levelFile.close();

    return levelThreat;
}

/*
 * Returns a planet's image id.
 */
int Level::GetPlanetImgId(int planetId)
{
    int planet = -1;
    std::ifstream levelFile;
    std::string fileName = "presets/planets.txt";
    std::string planetHeader = "PLANET ";
    std::string separator = "";
    std::string line;

    planetHeader.append(std::to_string(planetId)).append(" {");

    levelFile.open(fileName);

    AdvanceToSection(levelFile, planetHeader);

    std::getline(levelFile, line);
    std::istringstream iline(line);

    iline >> separator;

    /* Get the image id. */
    if(separator == "planetId:")
    {
        iline >> planet;
    }

    levelFile.close();

    return planet;
}

/*
 * Returns a planet's name.
 */
std::string Level::GetPlanetName(int planetId)
{
    std::string planetName;
    std::ifstream levelFile;
    std::string fileName = "presets/planets.txt";
    std::string planetHeader = "PLANET ";

    planetHeader.append(std::to_string(planetId)).append(" {");

    levelFile.open(fileName);

    AdvanceToSection(levelFile, planetHeader);

    /* Get the planet's name. */
    std::getline(levelFile, planetName);
    std::getline(levelFile, planetName);

    levelFile.close();

    return planetName;
}

/*
 * Returns a planet's description.
 */
std::string Level::GetPlanetDescription(int planetId)
{
    std::string planetDesc;
    std::ifstream levelFile;
    std::string fileName = "presets/planets.txt";
    std::string planetHeader = "PLANET ";

    planetHeader.append(std::to_string(planetId)).append(" {");

    levelFile.open(fileName);

    AdvanceToSection(levelFile, planetHeader);

    /* Get the planet's description. */
    std::getline(levelFile, planetDesc);
    std::getline(levelFile, planetDesc);
    std::getline(levelFile, planetDesc);

    levelFile.close();

    return planetDesc;
}

/*
 * Returns a planet's level id based on the mission id.
 */
int Level::GetPlanetLevel(int planetId, int mission)
{
    int planetLevel = -1;
    std::ifstream levelFile;
    std::string fileName = "presets/planets.txt";
    std::string planetHeader = "PLANET ";
    std::string levelHeader = "level_";
    std::string line = "";
    std::string separator = "";

    planetHeader.append(std::to_string(planetId)).append(" {");
    levelHeader.append(std::to_string(mission)).append(":");

    levelFile.open(fileName);

    AdvanceToSection(levelFile, planetHeader);

    /* Advance to the levelHeader section and get line. */
    while(std::getline(levelFile, line))
    {
        if(line.find(levelHeader) != std::string::npos)
        {
            break;
        }
    }

    levelFile.close();

    std::istringstream iline(line);
    iline >> separator;

    /* Gets the mission's level id. */
    if(separator.compare(levelHeader) == 0)
    {
        iline >> line;
        planetLevel = atoi(line.c_str());
    }

    return planetLevel;
}
