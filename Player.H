// Player: the hero. Inherits from Entity and adds gold, the curse timer,
// a healing blessing, an inventory of keys, and a count of keys collected.

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
        int keyCount;          // how many boss keys collected; gates the final door

    public:
        Player();
        Player(string startName, int startHealth, int startAttack, int startGold, int startCurse);

        int getGold();
        int getCurseTurns();
        bool getHasBlessing();
        void setHasBlessing(bool value);
        int getKeyCount();
        void addKey();         // one more key toward the final door

        void addGold(int amount);
        bool spendGold(int amount);
        void useTurns(int amount);

        void addItem(string itemName);
        void displayInventory();
};

#endif