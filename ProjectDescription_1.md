# CSCI 1300 Final Project — Project Description

## Theme

I'm making a turn-based dungeon battle game that you play in the terminal. The
main idea is that my hero (they show up as an `H` on the map) is stuck under a
curse that's going to kill them after a certain number of turns. So the whole game
is a race against that curse: you have to fight your way down through a dungeon,
take out the bosses, and grab what you need from them to break the curse before
your turns run out. I went with turn-based because nothing happens until the
player actually makes a move, which felt way more realistic for me to build since
this is my first coding class.

## Goal

My version of the "final bundle" is collecting 3 keys. Each of the first three
bosses drops its own key, and I need all three to unlock the door to the final
boss. After I beat the final boss it drops something, and I have to carry that back
to the healer, who uses it to lift the curse. If I do all of that before the curse
counter hits zero, my hero survives and I win.

## Classes

I'm planning on using 5 classes. It looks like a lot but honestly each one is
small — most of them are just a few stats and some short functions.

- **Item** — one thing that can be in my inventory or hidden in a chest. It keeps
  track of a name, a type (potion, weapon, relic, or key), a value for selling,
  and an effect amount (like how much a potion heals or how much damage a weapon
  adds).
- **Player** — this is my hero. It holds the name, HP, max HP, gold, where the
  hero is on the grid, the curse counter, which keys I've collected, and my
  inventory, which is made of Item objects. This is the class that stores objects
  of another class, which is one of the things the project requires.
- **Character** — my NPCs, so the blacksmith, the merchant, the healer, and the
  cloaked figure. It stores their name and role and handles what happens when I
  talk to them.
- **Boss** — every boss has a name, HP, attack damage, the key it drops, and the
  relic it drops. I made this its own class because it was just easier for me to
  think about each boss as its own object with its own drops.
- **Game** — this is the one that basically runs everything. It holds my Player,
  the Characters, the Bosses, the current map, and the game state, and it runs the
  main loop: draw the screen and map, take my input, move the hero, start fights,
  and check if I won or lost.

## Limited Resources

- **Time (required):** the curse counter. That's my main limited resource.
- **HP:** if my health hits zero in a fight, I die.
- **Gold:** what I spend at the blacksmith and healer, and earn by selling loot.

## Handling Time

I'm doing time with a curse counter that goes down whenever the hero does
something:

- Taking a step in the maze costs 1.
- Talking to an NPC costs 3.
- Every action in a fight (attacking, using an item, etc.) costs 2.

If the counter ever hits zero, my hero dies and I lose. I did it this way on
purpose so that everything I do drains the curse a little — that way there's
always pressure and I can't just sit there grinding a boss forever. I haven't
locked in the exact starting numbers yet (like the total curse, HP, gold, and boss
stats). I'm planning to figure those out and balance them in the later checkpoints
once I can actually test it.

## Tradeoff System (my "JojaMart" shortcut)

My shortcut is the cloaked figure in the tavern. Every time I beat a boss and come
back, he offers me a choice:

- **Keep the seal:** my hero has normal strength and the curse ticks at its normal
  speed.
- **Break the seal:** my hero gets a strength boost so fights are easier and go
  faster, but the curse starts ticking faster and I have fewer turns left.

So it's basically power now for time later. It's really tempting when a boss is
kicking my butt, but if I keep using it I'll run out of turns, which is how the
"easy way out" ends up backfiring. That's the tempting-but-costly tradeoff the
project wants.

## Map Style

Each dungeon is a simple 2D grid made out of text characters. Here's what my
symbols mean:

- `H` = my hero (the one I move around)
- `#` = wall
- `.` = open floor
- `C` = chest (has an item I can sell)
- `D` = boss door

There are 4 maps total. The first three each have their own maze, 3 chests, and
one boss door, and the fourth one is the final dungeon. I move the `H` around with
keyboard input, and when I reach a boss door the game asks if I want to go in. If I
say yes the fight starts, and after I win I go back to the tavern.

## Extra Credit

I'm hoping to do the shortest-path route recommendation (+5). Since my maze is just
a grid of connected squares, I want to add a feature that finds the path with the
fewest steps from wherever my hero is to the boss door, so the player can save
curse turns. My plan is to use a breadth-first search (BFS) over the open floor
squares — treating each square as connected to the squares next to it — and then
print out the recommended path and how many steps it takes.

## Win / Lose Condition

- **Win:** I get all 3 keys, beat the final boss, and bring its drop back to the
  healer before the curse runs out. The curse gets lifted and my hero lives.
- **Lose (death):** the curse counter hits zero, or my hero's HP hits zero in a
  fight. Either one means my hero dies and the game's over.
