// Entity: base class for anything that fights (the hero and the bosses).

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
        void setAttackPower(int amount);   // lets the blacksmith or seal change the hero's damage

        void takeDamage(int amount);
        void heal(int amount);
        bool isAlive(); //important
};

#endif