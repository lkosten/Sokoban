#ifndef STATUS_ENUMS_H
#define STATUS_ENUMS_H

#include "FLAGS.h"

enum GameStatus
{
    MAIN_MENU = 0,
    LEVEL_SELECTION,
    STATISTICS,
    SETTINGS,
    PLAYING,
    LEVEL_CREATOR,
    LEVEL_COMPLETED
};

enum MainMenuStatus
{
    MENU_PLAY = 0,
    MENU_LEVEL_CREATOR,
    MENU_STATISTICS,
    MENU_SETTINGS,
    MENU_EXIT

};

enum Texture
{
    EMPTY = 0,
    BOX,
    WALL,
    CIRCLE,
    OUTSIDE,
    MAN,
    ERASER,
    SPAWNPOINT,
    FRAME,
    PLUS,
    MINUS
};

#endif // STATUS_ENUMS_H
