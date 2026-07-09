#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
    private:
        Player hero;
        bool running;

    public:
        Game();

        void startGame();
        void showDashboard();
        void showMenu();
        void handleChoice(int choice);
};

#endif