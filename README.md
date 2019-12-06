Sokoban
=
Sokoban (倉庫番 sōko-ban, "warehouse keeper") is a type of puzzle video game, in which the player pushes crates or boxes around in a warehouse, trying to get them to storage locations.

<p align="center">
  <img width="400" height="300" src="https://github.com/soleni/images-for-md/blob/master/Screencast_12-06-2019_11_44_50%20PM%20(3).gif">
</p>

Rules
-
The game is played on a board of squares, where each square is a floor or a wall. Some floor squares contain boxes, and some floor squares are marked as storage locations.

The player is confined to the board, and may move horizontally or vertically onto empty squares (never through walls or boxes). The player can also move into a box, which pushes it into the square beyond. Boxes may not be pushed into other boxes or walls, and they cannot be pulled. The number of boxes is equal to the number of storage locations. The puzzle is solved when all boxes are at storage locations ([wiki](https://en.wikipedia.org/wiki/Sokoban)).

Features
-
* **In-game level creator** - create your own levels and pass them!
<p align="center">
  <img width="400" height="330" src="https://github.com/soleni/images-for-md/blob/master/Screenshot%20from%202019-12-06%2023-25-44.png">
</p>

* **Warehouse keeper appearance customization** - more than 70 textures (number will grow) and RGB pallete!
<p align="center">
  <img width="400" height="280" src="https://github.com/soleni/images-for-md/blob/master/Screenshot%20from%202019-12-06%2023-21-37.png">
</p>

Credits
-
http://www.sourcecode.se/sokoban/levels - tons of levels by community

https://game-icons.net/ - textures collection

Build
-
OpenGL libraries for windows and linux are different. Edit .pro file before build.

OpenGl library for windows :
```
  LIBS     += -lopengl32
```

OpenGl library for linux :
```
  LIBS     += -lGL
```
