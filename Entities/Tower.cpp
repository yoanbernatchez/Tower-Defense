/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-06
 * Project: Tower Defense
 * File: Tower.cpp
 *
 * Brief: This class implements towers, which can target units, shoot units,
 *        level up. Also implements methods to load tower presets.
 */

#include "Tower.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#define STRINGIFY(x) #x ":"

Tower::Tower(int id, int cubeX, int cubeY)
{
    src = {0, 0, 0, 0};
    dst = {0, 0, 0, 0};
    name = "";
    frame = 0;
    this->id = id;
    this->level = 1;
    this->cubeX = cubeX;
    this->cubeY = cubeY;
    isRendered = false;
    orientation = 0;
    targetUnit = nullptr;
    isIndicatorActive = false;

    LoadAllPresets();
}

/*
 * Goes through all of the units and targets the one closest to the end of the
 * level (if they are within the range of the tower).
 */
void Tower::TargetUnit(std::vector<Unit> &units, int cubeHeight)
{
    float towerCenterX = dst.x + dst.w / 2;
    float towerCenterY = dst.y + dst.h - cubeHeight / 4;

    /* Check if the target unit is still in range. */
    if(targetUnit != nullptr)
    {
        float unitCenterX = targetUnit->dst.x + targetUnit->dst.w / 2;
        float unitCenterY = targetUnit->dst.y + targetUnit->dst.h;
        float x = (unitCenterX - towerCenterX) * (unitCenterX - towerCenterX);
        float y = (unitCenterY - towerCenterY) * (unitCenterY - towerCenterY);
        float w = range * range;
        float h = (range * ISO_V_SCALE) * (range * ISO_V_SCALE);

        /* Check if unit is out of range. */
        if(1.0f < x / w + y / h)
        {
            targetUnit = nullptr;
        }
    }

    /* Try to find a new unit to target. */
    if(targetUnit == nullptr)
    {
        for(auto &i : units)
        {
            float unitCenterX = i.dst.x + i.dst.w/2;
            float unitCenterY = i.dst.y + i.dst.h;
            float x = (unitCenterX - towerCenterX) *
                      (unitCenterX - towerCenterX);
            float y = (unitCenterY - towerCenterY) *
                      (unitCenterY - towerCenterY);
            float w = range * range;
            float h = (range * ISO_V_SCALE) * (range * ISO_V_SCALE);

            /* Assign a new target unit if it is within the turret's range. */
            if(i.isVisible && 1.0f >= x/w + y/h)
            {
                if(targetUnit == nullptr || i.path.GetDirections().size() <
                   targetUnit->path.GetDirections().size())
                {
                    targetUnit = &i;
                    ChangeDirection(240, 0, 120, 100);
                }
            }
        }
    }
}

/*
 * Tower changes directions towards the followed unit.
 */
void Tower::FollowUnit(int cubeHeight)
{
    if(targetUnit != nullptr)
    {
        float towerCenterX = dst.x + dst.w/2;
        float towerCenterY = dst.y + dst.h - cubeHeight / 4;
        float unitCenterX = targetUnit->dst.x + targetUnit->dst.w/2;
        float unitCenterY = targetUnit->dst.y + targetUnit->dst.h;

        ChangeDirection(towerCenterX, towerCenterY, unitCenterX, unitCenterY);
    }
}

/*
 * Makes the turret face in the direction of a point (changes the texture that
 * the turret uses).
 */
void Tower::ChangeDirection(float towerPosX, float towerPosY,
                            float targetX, float targetY)
{
    float angle = atan2f(targetY - towerPosY, targetX - towerPosX);
    angle = angle * 180.0f / M_PI;

    if(angle > -15.0f && angle <= 15.0f)
    {
        orientation = 0;
    }
    else if(angle > 15.0f && angle <= 60.0f)
    {
        orientation = 7;
    }
    else if(angle > 60.0f && angle <= 120.0f)
    {
        orientation = 6;
    }
    else if(angle > 120.0f && angle <= 165.0f)
    {
        orientation = 5;
    }
    else if((angle > 165.0f && angle <= 180.0f)
            || (angle > -180.0f && angle <= -165.0f))
    {
        orientation = 4;
    }
    else if(angle > -165.0f && angle <= -120.0f)
    {
        orientation = 3;
    }
    else if(angle > - 120.0f && angle <= -60.0f)
    {
        orientation = 2;
    }
    else if(angle > -60.0f && angle < -15.0f)
    {
        orientation = 1;
    }
}

/*
 * Upgrades a tower to the next superior level.
 */
bool Tower::UpgradeTower()
{
    bool isUpgraded = false;

    if(level < maxLevel)
    {
        level++;
        LoadAllPresets();
        isUpgraded = true;
    }

    return isUpgraded;
}

/*
 * Loads the presets (stats of the tower) associated with the tower id from a
 * file.
 */
void Tower::LoadAllPresets()
{
    LoadTowerSpecificPreset(name, STRINGIFY(name));
    LoadTowerSpecificPreset(maxLevel, STRINGIFY(maxLevel));
    LoadTowerSpecificPreset(cost, STRINGIFY(cost));
    LoadTowerSpecificPreset(upgradeCost, STRINGIFY(upgradeCost));
    LoadTowerSpecificPreset(sellingValue, STRINGIFY(sellingValue));
    LoadTowerSpecificPreset(targetMode, STRINGIFY(targetMode));
    LoadTowerSpecificPreset(range, STRINGIFY(range));
    LoadTowerSpecificPreset(damage, STRINGIFY(damage));
    LoadTowerSpecificPreset(attackSpeed, STRINGIFY(attackSpeed));
    LoadTowerSpecificPreset(dot, STRINGIFY(dot));
    LoadTowerSpecificPreset(dotDuration, STRINGIFY(dotDuration));
}

/*
 * Loads a tower preset (int) from a file associated with the tower's id.
 */
void Tower::LoadTowerSpecificPreset(int &arg, std::string varName)
{
    arg = GetTowerSpecificPreset(varName, id, level);
}

/*
 * Loads a tower preset (string) from a file associated with the tower's id.
 */
void Tower::LoadTowerSpecificPreset(std::string &arg, std::string varName)
{
    arg = GetTowerSpecificPreset(id, level, varName);
}

/*
 * Gets a tower preset (string) from a file and returns it.
 */
std::string Tower::GetTowerSpecificPreset(int id, int level,
                                          std::string varName)
{
    std::string retval;
    std::string label;
    std::string line;
    std::string sectionHeader;
    std::ifstream towerFile;

    sectionHeader = GetTowerSectionHeader(id, level);

    towerFile.open("presets/towers.txt");

    /* Go to the header line of the specified tower. */
    while(std::getline(towerFile, line))
    {
        if(line.find(sectionHeader) != std::string::npos)
            break;
    }

    /* Go to the argument specified. */
    while(std::getline(towerFile, line))
    {
        if(line.find(varName) != std::string::npos)
            break;
    }

    std::istringstream streamLine(line);
    streamLine >> label;
    retval = line.substr(label.length() + 1, line.length());

    towerFile.close();

    return retval;
}

/*
 * Gets a tower preset (int) from a file and returns it.
 */
int Tower::GetTowerSpecificPreset(std::string varName, int id, int level)
{
    int retval = 0;
    std::string line;
    std::string sectionHeader;
    std::ifstream towerFile;

    sectionHeader = GetTowerSectionHeader(id, level);

    towerFile.open("presets/towers.txt");

    /* Go to the header line of the specified tower. */
    while(std::getline(towerFile, line))
    {
        if(line.find(sectionHeader) != std::string::npos)
            break;
    }

    /* Go to the argument specified. */
    while(std::getline(towerFile, line))
    {
        if(line.find(varName) != std::string::npos)
            break;
    }

    std::istringstream streamLine(line);
    streamLine >> line >> retval;

    towerFile.close();

    return retval;
}

/*
 * Returns the section header of a tower, depending on its id and level.
 */
std::string Tower::GetTowerSectionHeader(int id, int level)
{
    std::string towerHeader = "TOWER ";
    std::ifstream towerFile;

    towerFile.open("presets/towers.txt");

    towerHeader.append(std::to_string(id));
    towerHeader.append(" : Level ");
    towerHeader.append(std::to_string(level));
    towerHeader.append("{");

    towerFile.close();

    return towerHeader;
}

int Tower::GetLevel() { return level; }
