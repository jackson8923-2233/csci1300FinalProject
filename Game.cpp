#include "Game.h"
#include <iostream>
#include <fstream>   // for reading the map file
using namespace std;

// set up the starting hero, boss, and game state
Game::Game() {
    hero = Player("Hero", 10, 3, 0, 40);
    dungeonBoss = Boss("Bonelord", 15, 2, "Bonelord key");
    running = true;
    playerWon = false;
    numRows = 0;
    heroRow = 0;
    heroCol = 0;
    bossRow = 0;
    bossCol = 0;
}

// read the dungeon file into the grid and record the hero and boss positions
bool Game::loadMap(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open map file '" << filename << "'." << endl;
        return false;
    }

    numRows = 0;
    string line;
    while (getline(file, line) && numRows < 20) {
        grid[numRows] = line;
        numRows = numRows + 1;
    }
    file.close();

    // find the hero start (H) and boss (B) tiles
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < (int)grid[r].length(); c++) {
            if (grid[r][c] == 'H') {
                heroRow = r;
                heroCol = c;
                grid[r][c] = '.';   // clear it; the hero is drawn separately
            } else if (grid[r][c] == 'B') {
                bossRow = r;
                bossCol = c;
            }
        }
    }
    return true;
}

// print the stats and the map, drawing the hero on its current tile
void Game::drawScreen() {
    cout << endl;
    cout << "====================================" << endl;
    cout << "         THE CURSED DUNGEON         " << endl;
    cout << "====================================" << endl;
    cout << "Hero: " << hero.getName();
    cout << "   HP: " << hero.getHealth() << "/" << hero.getMaxHealth() << endl;
    cout << "Gold: " << hero.getGold();
    cout << "   Curse turns: " << hero.getCurseTurns() << endl;
    if (hero.getHasBlessing()) {
        cout << "Blessing: Yes" << endl;
    } else {
        cout << "Blessing: No" << endl;
    }
    cout << "------------------------------------" << endl;

    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < (int)grid[r].length(); c++) {
            if (r == heroRow && c == heroCol) {
                cout << 'H';   // hero always shows on its own tile
            } else {
                cout << grid[r][c];
            }
        }
        cout << endl;
    }
    cout << "------------------------------------" << endl;
    cout << "Move: W/A/S/D   I: inventory   Q: quit" << endl;
    cout << "Your move: ";
}

// turn a W/A/S/D key into a step, handling walls, chests, and the boss
void Game::movePlayer(char direction) {
    int newRow = heroRow;
    int newCol = heroCol;

    if (direction == 'w' || direction == 'W') { newRow = heroRow - 1; }
    else if (direction == 's' || direction == 'S') { newRow = heroRow + 1; }
    else if (direction == 'a' || direction == 'A') { newCol = heroCol - 1; }
    else if (direction == 'd' || direction == 'D') { newCol = heroCol + 1; }
    else {
        cout << "That is not a move key." << endl;
        return;
    }

    char target = grid[newRow][newCol];

    if (target == '#') {   // wall: no move, no time lost
        cout << "A wall blocks your path." << endl;
        return;
    }

    // valid move: step in and spend one curse turn
    heroRow = newRow;
    heroCol = newCol;
    hero.useTurns(1);

    if (target == 'C') {           // chest: gain gold and empty it
        hero.addGold(5);
        cout << "You found a chest! +5 gold." << endl;
        grid[newRow][newCol] = '.';
    } else if (target == 'B') {    // boss: offer the fight
        cout << "You have reached " << dungeonBoss.getName() << "!" << endl;
        cout << "Fight the boss? (y/n): ";
        char answer;
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            fightBoss();
        } else {
            cout << "You step back for now." << endl;
        }
    }
}

// the battle loop: Attack, Dodge, or Heal each round (boss hits back unless you dodge)
void Game::fightBoss() {
    cout << endl << "*** BATTLE: " << dungeonBoss.getName() << " ***" << endl;

    while (dungeonBoss.isAlive() && hero.isAlive() && running) {
        cout << endl;
        cout << hero.getName() << " HP: " << hero.getHealth() << "/" << hero.getMaxHealth() << endl;
        cout << dungeonBoss.getName() << " HP: " << dungeonBoss.getHealth() << "/" << dungeonBoss.getMaxHealth() << endl;
        cout << "1. Attack   2. Dodge   3. Heal" << endl;
        cout << "Choose: ";

        int choice;
        cin >> choice;
        hero.useTurns(2);   // every combat action costs 2 curse turns

        if (choice == 1) {                              // Attack
            dungeonBoss.takeDamage(hero.getAttackPower());
            cout << "You strike for " << hero.getAttackPower() << "!" << endl;
            if (dungeonBoss.isAlive()) {
                hero.takeDamage(dungeonBoss.getAttackPower());
                cout << dungeonBoss.getName() << " hits you for " << dungeonBoss.getAttackPower() << "!" << endl;
            }
        } else if (choice == 2) {                       // Dodge
            cout << "You dodge! The boss's attack misses." << endl;
        } else if (choice == 3) {                       // Heal
            if (hero.getHasBlessing()) {
                hero.heal(6);
                hero.setHasBlessing(false);
                cout << "You call on your blessing and heal 6 HP!" << endl;
            } else {
                cout << "No blessings left!" << endl;
            }
            if (dungeonBoss.isAlive()) {
                hero.takeDamage(dungeonBoss.getAttackPower());
                cout << dungeonBoss.getName() << " hits you for " << dungeonBoss.getAttackPower() << "!" << endl;
            }
        } else {
            cout << "Not a valid choice; you hesitate." << endl;
        }

        if (hero.getCurseTurns() <= 0) { running = false; }   // curse can run out mid-fight
    }

    if (!dungeonBoss.isAlive()) {   // victory
        cout << endl << "You defeated " << dungeonBoss.getName() << "!" << endl;
        cout << "You gained the " << dungeonBoss.getKeyDropped() << "!" << endl;
        hero.addItem(dungeonBoss.getKeyDropped());
        cout << "You cleared the dungeon! (More dungeons coming soon.)" << endl;
        playerWon = true;
        running = false;
    }
}

// end the game if the hero has died or the curse has run out
void Game::checkGameOver() {
    if (!hero.isAlive()) {
        cout << endl << "You have fallen in the dungeon. GAME OVER." << endl;
        running = false;
    } else if (hero.getCurseTurns() <= 0) {
        cout << endl << "The curse consumes you. GAME OVER." << endl;
        running = false;
    }
}

// opening menu before the game starts
void Game::mainMenu() {
    cout << "====================================" << endl;
    cout << "         THE CURSED DUNGEON         " << endl;
    cout << "====================================" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Quit" << endl;
    cout << "Choose: ";

    int choice;
    cin >> choice;
    if (choice != 1) {
        cout << "Maybe another day." << endl;
        running = false;
    }
}

// top-level flow: menu, name, load map, then the main loop
void Game::startGame() {
    mainMenu();
    if (!running) { return; }

    cout << "Enter your hero's name: ";
    string chosenName;
    cin >> chosenName;
    hero = Player(chosenName, 10, 3, 0, 40);

    if (!loadMap("dungeon1.txt")) { return; }

    cout << endl << "Break the curse before your turns run out!" << endl;

    while (running) {   // MAIN GAME LOOP
        drawScreen();
        char move;
        cin >> move;

        if (move == 'q' || move == 'Q') {
            cout << "You flee the dungeon. Farewell." << endl;
            running = false;
        } else if (move == 'i' || move == 'I') {
            hero.displayInventory();
        } else {
            movePlayer(move);
        }

        checkGameOver();
    }

    if (playerWon) {
        cout << endl << "Victory! The curse is broken." << endl;
    }
    cout << "Thanks for playing!" << endl;
}