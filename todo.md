# Draw Game TODO


🟡 In Progress
🔴 Not Started
🟢 Complete

---

Refactor and organize

basic logic:

1. timer
2. random time within a range
3. sometime within random time DRAW
4. enemy level difficulty reduces the amount of time
from DRAW to the time he shoots
5. player has to react AFTER DRAW but before ENEMY SHOOTS
6. penalty if they react before DRAW
7. one mulligan? Two penalties = LOSS

what indicates draw?

1. distinct sharp >1s sound
2. enemy animation changes

what indicates shoot?

1. winner (only one winner) shoot animation
2. winner (only one winner) shoot sound

what indicates win?
1. player shoot animation
2. player shoot sound
3. enemy die animation
4. enemie die sound

++player advances level

what indicates loss?
1. enemy shoot animation
2. enemy  shoot sound
3. player die animation
4. player die sound

--game over

-----> Slow motion is cool.

---

🟡 Basic Player Animator

🟡 Text display



🔴 Input system (space for shoot, select)

🔴 Main menu, options, hi score

🔴 Enemy animations

🔴 Set up timer system

🔴 Game logic

🔴 Text: 1. timer, 2: info

🔴 Cooler shoot/blood/death

🔴 Slowmo?
 
🔴 create/add sounds

🟢 Explicit memory allocation typdef headers (done: r_types.h)

🟢 Set up basic game loop (done)

🟢 Get textures loaded and rendered properly (done)

🟢 Tile struct and modifier function (done: modifyTile())

🟢 set up placeholder player animation with framecounter (done: playerAnimation())

🟢 set up debugger (done: msvc)

🟢 Initial Timer set up

---

*NOTE: 4ed mark concept: home, ctrl+space, end, ctrl+c, move ctrl+v*
*NOTE: alt+n jump to errors*