#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() {
    hero = Player("Hero", 20, 3, 10, 30);
    running = true;
}

void Game::showDashboard() {
    cout << "==================================" << endl;
    cout << "        THE CURSED DUNGEON        " << endl;
    cout << "==================================" << endl;
    cout << "Hero: " << hero.getName() << endl;
    cout << "HP: " << hero.getHealth() << " / " << hero.getMaxHealth() << endl;
    cout << "Gold: " << hero.getGold() << endl;
    cout << "Curse turns left: " << hero.getCurseTurns() << endl;
    cout << "==================================" << endl;
}

void Game::showMenu() {
    cout << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Enter the dungeon" << endl;
    cout << "2. Visit the tavern" << endl;
    cout << "3. View stats" << endl;
    cout << "4. Quit" << endl;
    cout << "Choose an option: ";
}

void Game::handleChoice(int choice) {
    if (choice == 1) {
        cout << "You step into the dungeon... (fighting coming soon!)" << endl;
        hero.useTurns(1);
    } else if (choice == 2) {
        cout << "You visit the tavern... (NPCs coming soon!)" << endl;
    } else if (choice == 3) {
        showDashboard();
    } else if (choice == 4) {
        cout << "You give up your quest. Goodbye!" << endl;
        running = false;
    } else {
        cout << "That is not a valid option." << endl;
    }
}

void Game::startGame() {
    int choice;

    cout << "Welcome to The Cursed Dungeon!" << endl;
    cout << "Break the curse before your turns run out." << endl << endl;

    while (running == true) {
        showDashboard();
        showMenu();
        cin >> choice;
        cout << endl;
        handleChoice(choice);
        cout << endl;

        if (hero.getCurseTurns() <= 0) {
            cout << "The curse has consumed you. Game over." << endl;
            running = false;
        }
    }

    cout << "Thanks for playing!" << endl;
}