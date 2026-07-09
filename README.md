# CSCI 1300 Final Project

## Theme

My game is a turn-based dungeon battle game that you play in the terminal. My hero
is stuck under a curse that will kill them after a set number of turns, so the
whole game is a race against time: you fight your way down through a dungeon,
defeat the bosses guarding it, and collect the keys they drop. Once you have all
the keys you can reach the final boss, and beating it lets you break the curse and
survive.

## How to compile and run

Open the terminal in the folder that has all my project files. To compile the
program, type this command (it lists all my .cpp files so the compiler has every
class, and names the finished program "dungeon"):

g++ Entity.cpp Player.cpp Boss.cpp Game.cpp main.cpp -o dungeon

Then, to actually run the program, type:

./dungeon

## How to play

(TBA)

## Classes

- **Entity** — the base class for anything that fights; stores name, health, and attack power.
- **Player** — the hero; inherits from Entity and adds gold and the curse counter.
- **Boss** — a dungeon boss; inherits from Entity and adds the key it drops.
- **Game** — runs the main menu loop and owns the Player.

## Extra credit

I'm planning to add a shortest-path route recommendation (using BFS) that suggests
the fewest-steps path to the boss door so I can save curse turns.
