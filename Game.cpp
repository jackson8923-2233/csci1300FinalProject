// Game.cpp
#include "Game.h"
#include <iostream>
#include <fstream>   // for reading the map files
using namespace std;

// set up the starting state
Game::Game() {
    hero = Player("Hero", 20, 3, 0, 150);
    running = true;
    playerWon = false;
    sealBroken = false;
    introDone = false;
    blacksmithUsed = false;
    finalDungeon = false;
    currentBossDefeated = false;
    numRows = 0;
    heroRow = 0;
    heroCol = 0;
}

// spend curse time; the broken seal makes every cost twice as heavy
void Game::spendCurse(int base) {
    if (sealBroken) {
        hero.useTurns(base * 2);
    } else {
        hero.useTurns(base);
    }
}

// end the game if the hero died or the curse ran out
void Game::checkGameOver() { //game loop
    if (!hero.isAlive()) {
        running = false;
    } else if (hero.getCurseTurns() <= 0) {
        running = false;
    }
}

// the opening story and controls screen
void Game::showIntro() {
    cout << "========================================" << endl;
    cout << "         THE CURSE OF THE DEEP          " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "A curse festers in your blood. It will claim" << endl;
    cout << "your life in a set number of turns unless you" << endl;
    cout << "break it." << endl << endl;
    cout << "Three ancient keys, held by three dungeon" << endl;
    cout << "bosses, seal the final door. Beyond it waits" << endl;
    cout << "the one who cursed you." << endl << endl;
    cout << "Gather the keys. Open the door. Survive." << endl << endl;
    cout << "- Explore dungeons with W/A/S/D" << endl;
    cout << "- Fight bosses to win their keys" << endl;
    cout << "- Return to the Tavern to prepare" << endl;
    cout << "- Every step and action drains the curse" << endl << endl;
    cout << "Press ENTER to begin...";
    cin.get();   // wait for the player to press enter

    // arriving at the tavern: introduce the four characters and what they offer
    cout << endl;
    cout << "----------------------------------------" << endl << endl;
    cout << "You push open the tavern door. Firelight," << endl;
    cout << "smoke, and four faces turn toward you." << endl << endl;
    cout << "  THE CLOAKED FIGURE sits alone in the dark" << endl;
    cout << "  corner. He knows what the curse is, and he" << endl;
    cout << "  can break the seal on your power - for a" << endl;
    cout << "  terrible price." << endl << endl;
    cout << "  THE HEALER waits by the hearth. For 10 gold" << endl;
    cout << "  she will grant you a blessing that mends 6" << endl;
    cout << "  health in the middle of a battle." << endl << endl;
    cout << "  THE BLACKSMITH hammers at his forge. For 15" << endl;
    cout << "  gold he will sharpen your blade, raising your" << endl;
    cout << "  attack from 3 to 4." << endl << endl;
    cout << "  THE ORACLE reads the smoke. For a single" << endl;
    cout << "  gold coin she will tell you what waits in" << endl;
    cout << "  the dungeon below." << endl << endl;
    cout << "Rest here between descents - the tavern" << endl;
    cout << "restores your health." << endl << endl;
    cout << "Press ENTER to continue...";
    cin.get();   // wait again so the player can read the introductions
}

// draw the tavern dashboard and menu
void Game::showTavern() {
    cout << endl;
    cout << "========================================" << endl;
    cout << "               THE TAVERN               " << endl;
    cout << "========================================" << endl;
    cout << "Curse turns: " << hero.getCurseTurns();
    cout << "    HP: " << hero.getHealth() << "/" << hero.getMaxHealth();
    cout << "    Gold: " << hero.getGold() << endl;
    cout << "Keys collected: " << hero.getKeyCount() << " / 3";
    cout << "     Attack: " << hero.getAttackPower();
    if (sealBroken) { cout << " (seal broken)"; }
    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. Talk to the Cloaked Figure" << endl;
    cout << "2. Talk to the Healer" << endl;
    cout << "3. Talk to the Blacksmith" << endl;
    cout << "4. Talk to the Oracle" << endl;
    cout << "5. Enter the Dungeon" << endl;
    cout << "6. Quit" << endl;
    cout << "Choose: ";
}

// Cloaked Figure: gives the quest once, then offers the seal tradeoff until taken
void Game::talkCloaked() {
    spendCurse(3);   // talking takes time
    cout << endl;
    if (!introDone) {
        cout << "The Cloaked Figure rasps:" << endl;
        cout << "\"Cursed one. Three keys lie in the dungeons below." << endl;
        cout << " Claim them, and the final door will open. Fail," << endl;
        cout << " and the curse takes you. Now go.\"" << endl;
        introDone = true;
        return;
    }
    if (sealBroken) {
        cout << "The Cloaked Figure whispers: \"The dark power is yours now." << endl;
        cout << " There is no turning back.\"" << endl;
        return;
    }
    // offer the seal tradeoff
    cout << "The Cloaked Figure offers: \"I can break the seal on your power." << endl;
    cout << " Your strength will surge, but the curse will drain twice as fast.\"" << endl;
    cout << "Break the seal? (y/n): ";
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        sealBroken = true;
        hero.setAttackPower(6);
        cout << "Dark power floods your veins! Attack is now 6, but the curse quickens." << endl;
    } else {
        cout << "You keep your seal intact... for now." << endl;
    }
}

// Healer: sells one blessing for 10 gold
void Game::talkHealer() {
    spendCurse(3);
    cout << endl;
    cout << "The Healer smiles warmly." << endl;
    if (hero.getHasBlessing()) {
        cout << "\"You already carry a blessing. Use it before you seek another.\"" << endl;
        return;
    }
    cout << "\"A blessing to mend your wounds costs 10 gold. Buy one? (y/n): \"";
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        if (hero.spendGold(10)) {
            hero.setHasBlessing(true);
            cout << "You receive a blessing. It will heal you once in battle." << endl;
        } else {
            cout << "\"You lack the gold, traveler.\"" << endl;
        }
    } else {
        cout << "\"Return when you are ready.\"" << endl;
    }
}

// Blacksmith: one-time attack upgrade from 3 to 4 for 15 gold
void Game::talkBlacksmith() {
    spendCurse(3);
    cout << endl;
    cout << "The Blacksmith grunts over the forge." << endl;
    if (blacksmithUsed) {
        cout << "\"I've nothing more to sharpen for you.\"" << endl;
        return;
    }
    if (hero.getAttackPower() >= 4) {
        cout << "\"Your weapon is already keen enough.\"" << endl;
        return;
    }
    cout << "\"I'll sharpen your blade, attack 3 to 4, for 15 gold. Buy? (y/n): \"";
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        if (hero.spendGold(15)) {
            hero.setAttackPower(4);
            blacksmithUsed = true;
            cout << "Your blade gleams. Attack is now 4." << endl;
        } else {
            cout << "\"Come back with coin.\"" << endl;
        }
    } else {
        cout << "\"Suit yourself.\"" << endl;
    }
}

// Oracle: 1 gold for a useful hint, including the next boss's stats
void Game::talkOracle() {
    spendCurse(3);
    cout << endl;
    cout << "The Oracle gazes into the smoke." << endl;
    if (!hero.spendGold(1)) {
        cout << "\"Even wisdom has a price: 1 gold. You have none.\"" << endl;
        return;
    }
    cout << "\"For your gold, hear this:\"" << endl;
    // tell the player about the dungeon they'll enter next (based on keys held)
    int keys = hero.getKeyCount();
    if (keys == 0) {
        cout << "- Next lies the Crypt. Its guardian, Bonelord, has 15 HP and hits for 2." << endl;
    } else if (keys == 1) {
        cout << "- Next lies the Caverns. Mirewraith waits there: 18 HP, hits for 2." << endl;
    } else if (keys == 2) {
        cout << "- Next lies the Depths. Stonejaw guards it: 21 HP, hits for 3." << endl;
    } else {
        cout << "- The final door is open. The Curse-Weaver awaits: 24 HP, hits for 3." << endl;
    }
    cout << "- Remember: chests hold 5 gold, and the Healer's blessing mends 6 HP." << endl;
}

// read a dungeon file into the grid and find the hero's start
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

    // find the hero start (H) and clear it to floor; the hero is drawn separately
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < (int)grid[r].length(); c++) {
            if (grid[r][c] == 'H') {
                heroRow = r;
                heroCol = c;
                grid[r][c] = '.';
            }
        }
    }
    return true;
}

// draw the dungeon dashboard and the map with the hero on top
void Game::drawDungeon() {
    cout << endl;
    cout << "===== " << dungeonBoss.getName() << "'s Dungeon =====" << endl;
    cout << "Curse: " << hero.getCurseTurns();
    cout << "   HP: " << hero.getHealth() << "/" << hero.getMaxHealth();
    cout << "   Gold: " << hero.getGold();
    cout << "   Keys: " << hero.getKeyCount() << "/3" << endl;
    cout << "--------------------------------" << endl;
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < (int)grid[r].length(); c++) { // nested for loop
            if (r == heroRow && c == heroCol) {
                cout << 'H';
            } else {
                cout << grid[r][c];
            }
        }
        cout << endl;
    }
    cout << "--------------------------------" << endl;
    cout << "Move: W/A/S/D   I: inventory   Q: retreat to tavern" << endl;
    cout << "Your move: ";
}

// turn a movement key into a step, handling walls, chests, and the boss
void Game::movePlayer(char direction) {
    int newRow = heroRow;
    int newCol = heroCol;
    if (direction == 'w' || direction == 'W') { newRow = heroRow - 1; } // defnsive code if they enter caps or not
    else if (direction == 's' || direction == 'S') { newRow = heroRow + 1; }
    else if (direction == 'a' || direction == 'A') { newCol = heroCol - 1; }
    else if (direction == 'd' || direction == 'D') { newCol = heroCol + 1; }
    else {
        cout << "That is not a move key." << endl;
        return;
    }

    char target = grid[newRow][newCol];
    if (target == '#') {
        cout << "A wall blocks your path." << endl;
        return;
    }

    heroRow = newRow;
    heroCol = newCol;
    spendCurse(1);   // each step costs a curse turn (doubled if the seal is broken)

    if (target == 'C') {
        hero.addGold(5);
        cout << "You found a chest! +5 gold." << endl;
        grid[newRow][newCol] = '.';
    } else if (target == 'B') {
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
        spendCurse(2);   // every combat action costs 2 curse (doubled if seal broken)

        if (choice == 1) {                              // Attack
            dungeonBoss.takeDamage(hero.getAttackPower());
            cout << "You strike for " << hero.getAttackPower() << "!" << endl;
            if (dungeonBoss.isAlive()) {
                hero.takeDamage(dungeonBoss.getAttackPower());
                cout << dungeonBoss.getName() << " hits you for " << dungeonBoss.getAttackPower() << "!" << endl;
            }
        } else if (choice == 2) {                       // Dodge
            cout << "You dodge! The boss's attack misses." << endl; //simple
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

    // decide the result of the battle
    if (!dungeonBoss.isAlive()) {
        cout << endl << "You defeated " << dungeonBoss.getName() << "!" << endl;
        if (finalDungeon) {
            playerWon = true;      // beating the final boss wins the game
            running = false;
        } else {
            hero.addKey();                              // progress toward the final door
            hero.addItem(dungeonBoss.getKeyDropped());  // keep the key in the inventory
            cout << "You claim the " << dungeonBoss.getKeyDropped() << "! (Keys: " << hero.getKeyCount() << "/3)" << endl;
            currentBossDefeated = true;                 // signal to return to the tavern
        }
    }
}

// pick the dungeon by key count, load it, and run it until win/retreat/death
void Game::enterDungeon() {
    int keys = hero.getKeyCount();
    string filename;
    finalDungeon = false;

    // auto-route: the number of keys decides which dungeon opens
    if (keys == 0) {
        dungeonBoss = Boss("Bonelord", 15, 2, "Bonelord Key");
        filename = "dungeon1.txt";
    } else if (keys == 1) {
        dungeonBoss = Boss("Mirewraith", 18, 2, "Mirewraith Key");
        filename = "dungeon2.txt";
    } else if (keys == 2) {
        dungeonBoss = Boss("Stonejaw", 21, 3, "Stonejaw Key");
        filename = "dungeon3.txt";
    } else {
        dungeonBoss = Boss("The Curse-Weaver", 24, 3, "None");
        filename = "dungeon4.txt";
        finalDungeon = true;
        cout << endl << "With all three keys, the final door grinds open..." << endl;
    }

    if (!loadMap(filename)) { return; }   // stop if the map file is missing (Defensive code)
    currentBossDefeated = false;

    // the dungeon loop: explore until the boss falls, you retreat, or you die
    bool inDungeon = true;
    while (inDungeon && running) {
        drawDungeon();
        char move;
        cin >> move;
        if (move == 'q' || move == 'Q') {
            cout << "You retreat to the tavern." << endl;
            inDungeon = false;
        } else if (move == 'i' || move == 'I') {
            hero.displayInventory();
        } else {
            movePlayer(move);
        }
        checkGameOver();
        if (currentBossDefeated) { inDungeon = false; }   // won this dungeon; back to tavern
    }
}

// print the correct ending based on how the run finished
void Game::showEnding() {
    cout << endl << "========================================" << endl;
    if (playerWon) {
        cout << "The Curse-Weaver falls. The curse is broken!" << endl;
        if (sealBroken) {
            cout << "But the dark power you borrowed has left its mark." << endl;
            cout << "You are free... yet no longer wholly yourself." << endl;
        } else {
            cout << "You broke the curse with your own strength." << endl;
            cout << "The valley is safe, and so are you." << endl;
        }
    } else if (!hero.isAlive()) {
        cout << "You have fallen in the dark. GAME OVER." << endl;
    } else {
        cout << "The curse consumes you at last. GAME OVER." << endl;
    }
    cout << "========================================" << endl;
}

// the top-level flow: intro, name, then the tavern main loop
void Game::startGame() {                //game loop
    showIntro();

    cout << endl << "Enter your hero's name: ";
    string chosenName;
    cin >> chosenName;
    hero = Player(chosenName, 20, 3, 0, 150); //health, attack, keys, cursetimer

    // MAIN GAME LOOP: the tavern hub, running until win, loss, or quit
    while (running) {
        hero.heal(9999);   // resting at the tavern restores the hero to full health
        showTavern();
        int choice;
        cin >> choice;

        if (choice == 1) { talkCloaked(); }
        else if (choice == 2) { talkHealer(); }
        else if (choice == 3) { talkBlacksmith(); }
        else if (choice == 4) { talkOracle(); }
        else if (choice == 5) { enterDungeon(); }
        else if (choice == 6) {
            cout << "You abandon your quest." << endl;
            running = false;
        }
        else { cout << "That is not a valid option." << endl; }

        checkGameOver();   // after each action, see if the curse or HP ended things
    }

    showEnding();
}