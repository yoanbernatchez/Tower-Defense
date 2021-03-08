/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-06
 * Project: Tower Defense
 * File: Player.cpp
 *
 * Brief: This class implements player saves and stats such as hp and currency.
 */

#include "Player.h"

Player::Player()
{
    maxHp = 100;
    hp = 100;
    currency = 500;
}

/*
 * NOT IMPLEMENTED YET
 * Simply returns true if the level exists for the moment.
 */
bool Player::IsLevelUnlocked(int levelId)
{
    if(levelId != 0)
    {
        return false;
    }

    return true;
}
