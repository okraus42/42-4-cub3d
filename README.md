# 42-4-cub3d
aMaze42 - cub3D project but also a maze
<h3>Test</h3>

<h3>Resources:</h3>
3DSage
Make Your Own Raycaster Part 1
https://www.youtube.com/watch?v=gYRrGTC7GtA
Make Your Own Raycaster Part 2
https://www.youtube.com/watch?v=PC1RaETIx3Y
Make Your Own Raycaster Part 3
https://www.youtube.com/watch?v=w0Bm4IA-Ii8

Wikipedia
https://en.wikipedia.org/wiki/Ray_casting

Lode's Computer Graphics Tutorial
Raycasting
https://lodev.org/cgtutor/raycasting.html
Raycasting II: Floor and Ceiling
https://lodev.org/cgtutor/raycasting2.html
Raycasting III: Sprites
https://lodev.org/cgtutor/raycasting3.html
Raycasting IV: Directional Sprites, Doors, And More
https://lodev.org/cgtutor/raycasting4.html

F. Permadi
Ray-Casting Tutorial For Game Development And Other Purposes
https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/

Stuff to check:
https://www.youtube.com/watch?v=NbSee-XM7WA
https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/
Saving math to arrays
Rendering image at 90 degrees
Other performance hacks (powers of two), no floats

Ray Casting Game Tutorial – Part 1 – Building The Engine
https://hotsource.dev/2019/05/03/raycasting-game-tutorial-part-1-building-the-engine/

Maze Generation:
https://en.wikipedia.org/wiki/Maze_generation_algorithm
https://www.jamisbuck.org/presentations/rubyconf2011/index.html


Todo today:
- Options
— Fov (1-720)
— fish eye correction (limits fov to 179)
— resolution (takes effect after restart)
— fullscreen (takes effect after restart)
— restart option?
— .ini file with settings preserved
-- save settings

--ESC in hall of fame

!!! Load game free old pointers befre assigning new values !!!

Ideas:
Refresh available maps
Add autosave
Hall of fame listing with arrows or Page up/Down keys?
Random generation check the map is complex enough (distance to exit should be more than x and more floor)
Saves called AGU or Freeze
Init when the game starts
init when the map loads
init for highscores
Display warning when trying to open invalid map

- Difficulty in Hall of fame?
- 4xresolution (4 pixels instead of one)
- The style of aMaze42:
- connected with 42 school thematic 
- doors could be doors of different campuses(Prague, Berlin, Paris etc), the same for collectibles 
- text bubbles above sprites
- staff members could be enemies, chasing player to do proper evaluations
- black hole sprite/ skybox 
- levels of game difficulty could be based on the holy graph (starting from piscine (using water textures) up to the transcendence and so on.)
- score calculation

- scale button size
- new game
— game mode selection (one level, campaign, time trial(competition))
— choose existing map
— generate random map
— difficulty selection (void, easy, moderate, hard, nightmare)
— name, coalition, campus selection 

- random map generation
- debugging strings onscreen
To do list:
- game menu
— pause game menu
— options change
— inventory?
— hall of fame?
— map?
— save game
— load game
— quit game
- draw string?
- key hook?
— name player
— name coalition
— name campus
- map generation (integrate options in menu)
— save options
— random options?
— save seed
- save game
— name save
- screen (2d)
— draws textures on the map
— moves the map if player is close to the edge of screen but not the edge of the map
— fills the empty fields
- screen (3d)
— first different colour walls
— then textured walls
— in the top left corner during game development
- collectibles
- score system
- doors
- sprites
- mouse control
- traps?
- enemies?
- autoplay?
- more advanced map generation?
- quadrant based calculations ?
- sounds
- jumping?
- look up/down?
- more code optimisations
- HUD?
- textured floor and ceiling
- skybox?
- special powers?
- special effects?
- portals?
- level to level transitions?
- split screen multiplayer (2-4 players)?