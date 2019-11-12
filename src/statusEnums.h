#ifndef STATUS_ENUMS_H
#define STATUS_ENUMS_H

enum GameStatus
{
    MAIN_MENU = 0,
    LEVEL_SELECTION,
    STATISTICS,
    SETTINGS,
    PLAYING,
    LEVEL_CREATOR
};

enum MainMenuStatus
{
    MENU_PLAY = 0,
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
    MAN
};

#endif // STATUS_ENUMS_H
