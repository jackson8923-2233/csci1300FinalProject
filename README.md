# CSCI 1300 Final Project

## Theme

My game is a turn-based dungeon battle game that you play in the terminal. My hero
is stuck under a curse that will kill them after a set number of turns, so the
whole game is a race against time: you explore a dungeon, open chests for gold,
and fight the boss guarding it. Beating the boss gives you its key and clears the
dungeon. The full game will have four dungeons and four keys to break the curse.

## How to compile and run

Open the terminal in the folder that has all my project files (make sure
dungeon1.txt is in that folder too, because the game reads the map from it). To
compile, type this command (it lists all my .cpp files and names the program
"dungeon"):

g++ Entity.cpp Player.cpp Boss.cpp Game.cpp main.cpp -o dungeon

Then, to run the program, type:

./dungeon

## How to play

Pick "Start Game" and enter your hero's name. You move around the map with the
keys W (up), A (left), S (down), D (right). Press I to view your inventory and
gold, or Q to quit. Walls (#) block you. Stepping on a chest (C) gives you gold.
Stepping on the boss (B) lets you choose to fight. Each step and each fight action
uses up curse turns, so don't waste time. In battle you can Attack, Dodge (take no
damage that round), or Heal (if you have a blessing). Defeat the boss before your
curse or your health runs out.

## Classes

- **Entity** — the base class for anything that fights; stores name, health, and attack power.
- **Player** — the hero; inherits from Entity and adds gold, the curse timer, a blessing, and an inventory.
- **Boss** — a dungeon boss; inherits from Entity and adds the key it drops when defeated.
- **Game** — runs the whole game: loads the map from a file, handles movement, chests, combat, and the endings.

## File input

The dungeon map is stored in dungeon1.txt and read into the game when it starts.
The map uses # for walls, . for floor, H for the hero start, B for the boss, and C
for chests. Because the map is just a data file, future dungeons will use the same
code with different .txt files.

## Extra credit

I'm planning to add a shortest-path route recommendation (using BFS) that suggests
the fewest-steps path to the boss door so I can save curse turns.