#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() : Entity("Hero", 20, 3) {
    gold = 10;
    curseTurns = 30;
}

Player::Player(string startName, int startHealth, int startAttack, int startGold, int startCurse)
    : Entity(startName, startHealth, startAttack) {
    gold = startGold;
    curseTurns = startCurse;
}

int Player::getGold() {
    return gold;
}

int Player::getCurseTurns() {
    return curseTurns;
}

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
    if (curseTurns < 0) {
        curseTurns = 0;
    }
}