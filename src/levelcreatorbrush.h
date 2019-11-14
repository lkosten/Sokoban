#ifndef LEVELCREATORBRUSH_H
#define LEVELCREATORBRUSH_H

#include "levelcreatormap.h"

enum tools{
    T_RUBBER = 0,
    T_WALL,
    T_BOX,
    T_POINT,
    T_SPAWN
};

class CreatorBrush{
    static const char EMPTY = 'e';
    static const char BOX = 'b';
    static const char WALL = 'w';
    static const char POINT = 'p';
    static const char OUTSIDE = 'o';
    static const char BOX_ON_POINT = 'u';

    static tools currentTool;

    friend class LevelCreator;
    friend class CreatorDrawer;

    static void ChangeTool(bool up);
    static void SetGate(unsigned int x, unsigned int y);
    static unsigned int GetToolNum();
};

#endif // LEVELCREATORBRUSH_H
