// Player: the hero. Inherits from Entity and adds gold, the curse timer,
// a healing blessing, and an inventory for collected keys.

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <string>
using namespace std;

class Player : public Entity {   // Player inherits from Entity
    private:
        int gold;
        int curseTurns;
        bool hasBlessing;
        string inventory[6];   // holds collected keys
        int itemCount;

    public:
        Player();
        Player(string startName, int startHealth, int startAttack, int startGold, int startCurse);

        int getGold();
        int getCurseTurns();
        bool getHasBlessing();
        void setHasBlessing(bool value);

        void addGold(int amount);
        bool spendGold(int amount);
        void useTurns(int amount);

        void addItem(string itemName);
        void displayInventory();
};

#endif