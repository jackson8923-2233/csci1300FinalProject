#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <string>
using namespace std;

class Player : public Entity {
    private:
        int gold;
        int curseTurns;

    public:
        Player();
        Player(string startName, int startHealth, int startAttack, int startGold, int startCurse);

        int getGold();
        int getCurseTurns();

        void addGold(int amount);
        bool spendGold(int amount);
        void useTurns(int amount);
};

#endif