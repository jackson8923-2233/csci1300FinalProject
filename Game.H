// Game: the controller. Owns the hero and boss, holds the map, and runs
// the main loop (draw, take input, move, fight, check for game over).

#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Boss.h"
#include <string>
using namespace std;

class Game {
    private:
        Player hero;
        Boss dungeonBoss;
        bool running;
        bool playerWon;

        string grid[20];   // the map, one row of characters per slot
        int numRows;
        int heroRow;
        int heroCol;
        int bossRow;
        int bossCol;

    public:
        Game();

        void startGame();
        void mainMenu();
        bool loadMap(string filename);   // reads the map from a .txt file
        void drawScreen();
        void movePlayer(char direction);
        void fightBoss();
        void checkGameOver();
};

#endif