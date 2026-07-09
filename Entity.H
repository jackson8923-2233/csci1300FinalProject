#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

class Entity {
    protected:
        string name;
        int health;
        int maxHealth;
        int attackPower;

    public:
        Entity();
        Entity(string startName, int startHealth, int startAttack);

        string getName();
        int getHealth();
        int getMaxHealth();
        int getAttackPower();

        void takeDamage(int amount);
        bool isAlive();
};

#endif