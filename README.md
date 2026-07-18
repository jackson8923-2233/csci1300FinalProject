# CSCI 1300 Final Project — The Curse of the Deep

## Theme

This is a turn-based dungeon adventure game played in the terminal. You are a hero
cursed with a slow death: a curse counter ticks down with everything you do, and
if it reaches zero you die. To break the curse you must descend into four dungeons,
defeat the boss of each, collect three keys, open the final door, and defeat the
one who cursed you.

This is an **alternative theme** (not the Stardew farming setting). Here is how it
maps onto the project requirements:

- **Final Community Center bundle → the three keys.** Collecting all three boss
  keys is the collection goal that unlocks the final door.
- **Villagers → the four tavern characters** (Cloaked Figure, Healer, Blacksmith,
  Oracle), each of whom affects gameplay.
- **Town locations → the Tavern hub plus the four dungeons.**
- **JojaMart shortcut → the Cloaked Figure's seal.** Breaking the seal makes you
  stronger but makes the curse drain twice as fast, and it changes your ending.
- **Community-restoration ending → breaking the curse** (with a different final
  message depending on whether you used the seal shortcut).

## Goal

Collect the three keys from the first three dungeon bosses, open the final door,
and defeat the Curse-Weaver before your curse counter runs out.

## How to compile and run

Open the terminal in the folder that has all the project files, including the four
dungeon map files (dungeon1.txt through dungeon4.txt), because the game reads the
maps from those files. To compile, type:

g++ Entity.cpp Player.cpp Boss.cpp Game.cpp main.cpp -o game

Then to run it, type:

./game

## How to play

Start the game and enter your hero's name. You begin at the Tavern, a menu hub
where you can talk to characters and prepare. Choose "Enter the Dungeon" to descend
into the next dungeon (which one is decided automatically by how many keys you
have). In a dungeon you move with W/A/S/D, press I to view your keys, or Q to
retreat to the tavern. Walls (#) block you, chests (C) give 5 gold, and stepping on
the boss (B) lets you choose to fight.

In battle you can Attack, Dodge (take no damage that round), or Heal (if you have a
blessing). Every step and every action drains the curse. Returning to the tavern
restores your health, so use it to rest between dungeons. Spend gold at the Healer
(blessings), the Blacksmith (a stronger weapon), or the Oracle (hints). The Cloaked
Figure offers to break your seal for more power at a dangerous cost.

## Classes

- **Entity** — the base class for anything that fights; stores name, health, and attack power.
- **Player** — the hero; inherits from Entity and adds gold, the curse timer, a blessing, an inventory, and the key count.
- **Boss** — a dungeon boss; inherits from Entity and adds the key it drops.
- **Game** — runs the whole game: the intro, the tavern hub, the four characters, the dungeons (map loading, movement, combat), the seal tradeoff, and the endings.

## File input

The four dungeon maps are stored in dungeon1.txt through dungeon4.txt and read into
the game when each dungeon is entered. A map uses # for walls, . for floor, H for
the hero start, B for the boss, and C for chests. Because each map is just a data
file, all four dungeons run on the same code with different files.

## Extra credit

None attempted yet. (A shortest-path route recommendation using BFS is a possible
future addition.)