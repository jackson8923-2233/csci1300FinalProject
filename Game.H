// Game: the controller. Owns the hero, runs the tavern hub and the dungeons,
// handles the NPCs, the seal tradeoff, and the endings.

#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Boss.h"
#include <string>
using namespace std;

class Game {
    private:
        Player hero;            // game storing player object
        bool running;          // master switch for the main loop
        bool playerWon;        // did the run end in victory

        bool sealBroken;       // the seal tradeoff: once true, attack is 6 but curse costs double
        bool introDone;        // has the cloaked figure given the quest yet
        bool blacksmithUsed;   // one-time weapon upgrade already bought

        // current dungeon state (reloaded fresh each time a dungeon is entered)
        Boss dungeonBoss;           // game storing player object
        bool finalDungeon;         // is the current dungeon the final one
        bool currentBossDefeated;  // did the hero just beat this dungeon's boss
        string grid[20];
        int numRows;
        int heroRow;
        int heroCol;

    public:
        Game();

        void startGame();
        void showIntro();

        // the tavern hub
        void showTavern();
        void talkCloaked();
        void talkHealer();
        void talkBlacksmith();
        void talkOracle();

        // dungeon handling
        void enterDungeon();               // auto-routes by key count, then runs the dungeon
        bool loadMap(string filename);
        void drawDungeon();
        void movePlayer(char direction);
        void fightBoss();

        // helpers
        void spendCurse(int base);         // applies the seal's double-cost when active
        void checkGameOver();
        void showEnding();
};

#endif