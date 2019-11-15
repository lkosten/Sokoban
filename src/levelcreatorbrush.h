#ifndef LEVELCREATORBRUSH_H
#define LEVELCREATORBRUSH_H
#include "FLAGS.h"
#include "levelcreatormap.h"

enum tools{
    T_RUBBER = 0,
    T_WALL,
    T_BOX,
    T_POINT,
    T_SPAWN
};

class CreatorBrush{

    static tools currentTool;

    friend class LevelCreator;
    friend class CreatorDrawer;

    static void ChangeTool(bool up);
    static void SetGate(unsigned int x, unsigned int y);
    static unsigned int GetToolNum();
};

#endif // LEVELCREATORBRUSH_H
