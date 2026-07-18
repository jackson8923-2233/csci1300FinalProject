#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() : Entity("Hero", 10, 3) {
    gold = 0;
    curseTurns = 150;
    hasBlessing = true;
    itemCount = 0;
    keyCount = 0;
}

Player::Player(string startName, int startHealth, int startAttack, int startGold, int startCurse)
    : Entity(startName, startHealth, startAttack) {
    gold = startGold;
    curseTurns = startCurse;
    hasBlessing = true;    // one free starting blessing
    itemCount = 0;
    keyCount = 0;
}

int Player::getGold() { return gold; }
int Player::getCurseTurns() { return curseTurns; }
bool Player::getHasBlessing() { return hasBlessing; }
void Player::setHasBlessing(bool value) { hasBlessing = value; }
int Player::getKeyCount() { return keyCount; }
void Player::addKey() { keyCount = keyCount + 1; }

void Player::addGold(int amount) {
    gold = gold + amount;
}

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

void Player::addItem(string itemName) {
    if (itemCount < 6) {
        inventory[itemCount] = itemName;
        itemCount = itemCount + 1;
    }
}

void Player::displayInventory() {
    cout << "----- Inventory -----" << endl;
    if (itemCount == 0) {
        cout << "(no keys yet)" << endl;
    } else {
        for (int i = 0; i < itemCount; i++) {
            cout << "- " << inventory[i] << endl;
        }
    }
    cout << "Gold: " << gold << "   Keys: " << keyCount << "/3" << endl;
    cout << "---------------------" << endl;
}