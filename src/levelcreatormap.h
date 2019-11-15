#ifndef LEVELCREATORMAP_H
#define LEVELCREATORMAP_H
#include "FLAGS.h"
#include <vector>

class CreatorMap{
private:
    static unsigned int SizeX, SizeY, PosX, PosY;
    static std::vector<std::vector<char>> Field;

    friend class CreatorDrawer;
    friend class CreatorBrush;
    friend class LevelCreator;

    static void SetSize(unsigned int x, unsigned int y);
};

#endif // LEVELCREATORMAP_H
