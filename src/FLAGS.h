#ifndef FLAGS_H
#define FLAGS_H
#include <QColor>

class FLAGS{
public:
    static QColor wallColor;
    static QColor outsideColor;
    static QColor emptyColor;
    static QColor boxColor;
    static QColor pointColor;
    static QColor circleBoxColor;
    static QColor spawnColor;
    static QColor eraserColor;
    static QColor frameColor;

    static QColor manColor;

    static const char EMPTY = 'e';
    static const char BOX = 'b';
    static const char WALL = 'w';
    static const char POINT = 'p';
    static const char OUTSIDE = 'o';
    static const char BOX_ON_POINT = 'u';

    static char empty();
    static char box();
    static char wall();
    static char point();
    static char outside();
    static char boxOnPoint();
};

#endif // FLAGS_H
