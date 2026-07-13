#include "Player.h"
#include <iostream>
using namespace std;

// pass base stats up to Entity, then set the hero's own extras
Player::Player() : Entity("Hero", 10, 3) {
    gold = 0;
    curseTurns = 40;
    hasBlessing = true;   // one free starting blessing
    itemCount = 0;
}

Player::Player(string startName, int startHealth, int startAttack, int startGold, int startCurse)
    : Entity(startName, startHealth, startAttack) {
    gold = startGold;
    curseTurns = startCurse;
    hasBlessing = true;
    itemCount = 0;
}

int Player::getGold() { return gold; }
int Player::getCurseTurns() { return curseTurns; }
bool Player::getHasBlessing() { return hasBlessing; }
void Player::setHasBlessing(bool value) { hasBlessing = value; }

void Player::addGold(int amount) {
    gold = gold + amount;
}

// only spend if the hero can afford it
bool Player::spendGold(int amount) {
    if (gold >= amount) {
        gold = gold - amount;
        return true;
    } else {
        return false;
    }
}

void Player::useTurns(int amount) {
    curseTurns = curseTurns - amount;
    if (curseTurns < 0) { curseTurns = 0; }   // defensive code: never show negative time
}

// add an item if there's room in the bag
void Player::addItem(string itemName) {
    if (itemCount < 6) {
        inventory[itemCount] = itemName;
        itemCount = itemCount + 1;
    }
}

void Player::displayInventory() {
    cout << "----- Inventory -----" << endl;
    if (itemCount == 0) {
        cout << "(empty)" << endl;
    } else {
        for (int i = 0; i < itemCount; i++) {
            cout << "- " << inventory[i] << endl;
        }
    }
    cout << "Gold: " << gold << endl;
    cout << "---------------------" << endl;
}