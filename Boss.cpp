#include "Boss.h"
using namespace std;

Boss::Boss() : Entity("Boss", 15, 2) {
    keyDropped = "Mystery Key";
}

Boss::Boss(string startName, int startHealth, int startAttack, string key)
    : Entity(startName, startHealth, startAttack) {
    keyDropped = key;
}

string Boss::getKeyDropped() { return keyDropped; }