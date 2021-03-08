#ifndef PLAYER_H
#define PLAYER_H

/**
 * [NOT IMPLEMENTED YET]
 * @brief This class implements player saves and stats such as hp and currency.
 */
class Player
{
    public:
        int maxHp;
        int hp;
        int currency;

        Player();

        bool IsLevelUnlocked(int levelId);
};

#endif // PLAYER_H
