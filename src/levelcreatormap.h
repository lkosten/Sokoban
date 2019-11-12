#ifndef LEVELCREATORMAP_H
#define LEVELCREATORMAP_H

#include <vector>

class CreatorMap{
public:
    static const char EMPTY = 'e';
    static const char BOX = 'b';
    static const char WALL = 'w';
    static const char POINT = 'p';
    static const char OUTSIDE = 'o';
    static const char BOX_ON_POINT = 'u';
private:
    static unsigned int SizeX, SizeY, PosX, PosY;
    static std::vector<std::vector<char>> Field;

    friend class CreatorDrawer;
    friend class CreatorBrush;
    friend class LevelCreator;

    static void SetSize(unsigned int x, unsigned int y);
};

#endif // LEVELCREATORMAP_H
