// Boss: a dungeon boss. Inherits from Entity and adds the key it drops.

#ifndef BOSS_H
#define BOSS_H

#include "Entity.h"
#include <string>
using namespace std;

class Boss : public Entity {   // Boss inherits from Entity
    private:
        string keyDropped;

    public:
        Boss();
        Boss(string startName, int startHealth, int startAttack, string key);
        string getKeyDropped();
};

#endif