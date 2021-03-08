#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Grid.h"
#include "../Entities/Unit.h"
#include "../Entities/Tower.h"

/**
 * @brief Simple data structure containing a 2D point.
 *
 * @param x: Point in x.
 * @param y: Point in y.
 */
typedef struct Coordinates{
    int x;
    int y;
} Coordinates;

/**
 * @brief Level class used for loading and storing level informations from file
 *        such as wave data, cube data, etc.
 */
class Level
{
    public:
        Grid grid;
        Coordinates spawnPoint;
        Coordinates destination;
        std::vector<Unit> units;
        std::vector<Tower> towers;
        int timeBetweenWaves;
        bool isSrcUpdated;

        Level();

        /**
         * @brief Loads the level's cubes data.
         *
         * @param levelId: Id of the level to load.
         */
        void LoadLevel(int levelId);

        /**
         * @brief Loads the spawn points and destination points of the level.
         *
         * @param levelId: Id of the level to load from.
         */
        void LoadSpawnPointAndDestination(int levelId);

        /**
         * @brief Loads wave information from a level file.
         *
         * @param levelId: The id of the level.
         * @param wave:    Wave id to load.
         */
        void LoadWave(int levelId, int wave);

        /**
         * @param Returns the level's description.
         *
         * @param levelId: Level's id to fetch the description of.
         *
         * @return The level's description.
         */
        std::string GetLevelDescription(int levelId);

        /**
         * @brief Returns the threat description of a level.
         *
         * @param levelId: Level's id to fetch the threat of.
         *
         * @return The level's threat description.
         */
        std::string GetLevelThreat(int levelId);

        /**
         * @brief Returns a planet's image id.
         *
         * @param planetId: Id of the planet to fetch the name of.
         *
         * @return The image id of the planet.
         */
        int GetPlanetImgId(int planetId);

        /**
         * @brief Returns a planet's description.
         *
         * @param planetId: Id of the planet to fetch the description of.
         *
         * @return The planet's description.
         */
        std::string GetPlanetDescription(int planetId);

        /**
         * @brief Returns a planet's level id based on the mission id.
         *
         * @param planetId: Planet's id.
         * @param mission:  Id of the mission to fetch the level from.
         *
         * @return The planet's mission level id.
         */
        int GetPlanetLevel(int planetId, int level);

        /**
         * @brief Returns a planet's name.
         *
         * @param planetId: Id of the planet to fetch the name of.
         *
         * @return The planet's name.
         */
        std::string GetPlanetName(int planetId);
};

#endif // LEVEL_H
