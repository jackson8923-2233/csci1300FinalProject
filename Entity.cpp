#include "Entity.h"
#include <iostream>
using namespace std;

Entity::Entity() {
    name = "Unknown";
    health = 10;
    maxHealth = 10;
    attackPower = 1;
}

Entity::Entity(string startName, int startHealth, int startAttack) {
    name = startName;
    health = startHealth;
    maxHealth = startHealth;
    attackPower = startAttack;
}

string Entity::getName() {
    return name;
}

int Entity::getHealth() {
    return health;
}

int Entity::getMaxHealth() {
    return maxHealth;
}

int Entity::getAttackPower() {
    return attackPower;
}

void Entity::takeDamage(int amount) {
    health = health - amount;
    if (health < 0) {
        health = 0;
    }
}

bool Entity::isAlive() {
    if (health > 0) {
        return true;
    } else {
        return false;
    }
}