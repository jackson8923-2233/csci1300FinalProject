# CSCI 1300 Final Project

## Theme

My game is a single-player, turn-based dungeon battle game that runs in the
terminal. My hero is under a curse, and I have to fight down through a dungeon,
beat the bosses to collect their keys, take down the final boss, and bring its
drop back to the healer to break the curse before I run out of time.

## Goal

Collect all 3 keys from the first three bosses, open the final door, beat the
final boss, and get its drop back to the healer to lift the curse — all before the
curse counter reaches zero.

## How to compile and run

(TBA)

## How to play

(TBA)

## Classes

- **Item** — an item I can hold in my inventory or find in a chest.
- **Player** — my hero; holds all my stats and an inventory of Item objects.
- **Character** — my NPCs (blacksmith, merchant, healer, cloaked figure).
- **Boss** — a dungeon boss that drops a key and a sellable relic.
- **Game** — runs the whole game loop, the map, the menus, and the win/lose checks.

## Extra credit

I'm planning to add a shortest-path route recommendation (using BFS) that suggests
the fewest-steps path to the boss door so I can save curse turns.
