#include "Entity.h"
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
    maxHealth = startHealth;   // start at full health
    attackPower = startAttack;
}

string Entity::getName() { return name; }
int Entity::getHealth() { return health; }
int Entity::getMaxHealth() { return maxHealth; }
int Entity::getAttackPower() { return attackPower; }
void Entity::setAttackPower(int amount) { attackPower = amount; }

void Entity::takeDamage(int amount) {
    health = health - amount;
    if (health < 0) { health = 0; }   // defensive code: never let health go negative
}

void Entity::heal(int amount) {
    health = health + amount;
    if (health > maxHealth) { health = maxHealth; }   // never heal past the ceiling
}

bool Entity::isAlive() {
    if (health > 0) { return true; }
    else { return false; }
}