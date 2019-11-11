#ifndef LEVELCREATORBRUSH_H
#define LEVELCREATORBRUSH_H

class CreatorBrush{
    static char Current;
    static const char EMPTY = 'e';
    static const char BOX = 'b';
    static const char WALL = 'w';
    static const char POINT = 'p';

    friend class CreatorDrawer;
};

#endif // LEVELCREATORBRUSH_H
