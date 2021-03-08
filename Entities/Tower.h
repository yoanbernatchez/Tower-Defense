#ifndef TOWER_H
#define TOWER_H

#include "Entities.h"
#include "Unit.h"

#define ISO_V_SCALE 0.574

/**
 * @brief This class implements towers, which can target units, shoot units,
 *        level up and load presets.
 */
class Tower: public Entities
{
    public:
        Unit *targetUnit;
        int maxLevel;
        int cost;
        int upgradeCost;
        int sellingValue;
        int targetMode;
        int range;
        int damage;
        int attackSpeed;
        int dot;
        int dotDuration;
        bool isIndicatorActive;

        Tower(int id, int cubeX, int cubeY);

        /**
         * @brief Tower changes directions towards the followed unit.
         *
         * @param cubeHeight: Height of a cube.
         */
        void FollowUnit(int cubeHeight);

        /**
         * @brief Goes through all of the units and targets the one closest to
         *        the end of the level (if they are within the range of the
         *        tower).
         *
         * @param units:      Vector of all the units currently in the level.
         * @param cubeHeight: Height of a cube.
         */
        void TargetUnit(std::vector<Unit> &units, int cubeHeight);

        /**
         * @brief Makes the turret face in the direction of a point (changes
         *        the texture that the turret uses).
         *
         * @param towerPosX: Coordinate of the center of the tower in x.
         * @param towerPosY: Coordinate of the center of the tower in y.
         * @param targetX:   Coordinate of the center of the point to target
         *                   in x.
         * @param targetY:   Coordinate of the center of the point to target
         *                   in y.
         */
        void ChangeDirection(float towerPosX, float towerPosY,
                            float targetX, float targetY);

        /**
         * @brief Upgrades a tower to the next superior level.
         *
         * @return True on success, false if requested level is above the
         *         max level.
         */
        bool UpgradeTower();

        /* Getters. */
        int GetLevel();
        int GetTowerSpecificPreset(std::string varName, int id, int level);
        std::string GetTowerSpecificPreset(int id, int level,
                                           std::string varName);

    private:
        int level;

        /**
         * @brief Loads the presets (stats of the tower) associated with the
         *        tower id from a file.
         */
        void LoadAllPresets();

        /**
         * @brief Loads a tower preset (int) from a file associated with the
         *        tower's id.
         *
         * @param arg:     Argument (int) to store the value fetched in.
         * @param varName: Name of the argument to store the value in.
         */
        void LoadTowerSpecificPreset(int &arg, std::string varName);

        /**
         * @brief Loads a tower preset (string) from a file associated with
         *        the tower's id.
         *
         * @param arg:     Argument (string) to store the value fetched in.
         * @param varName: Name of the argument to store the value in.
         */
        void LoadTowerSpecificPreset(std::string &arg, std::string varName);

        /**
         * @brief Returns the section header of a tower, depending on its id
         *        and level.
         *
         * @param id:    Id of the tower to get the header for.
         * @param level: Level of the tower to get the header for.
         *
         * @return A string corresponding to the section header of a tower.
         */
        std::string GetTowerSectionHeader(int id, int level);
};

#endif // TOWER_H
