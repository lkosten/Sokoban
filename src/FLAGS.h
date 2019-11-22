#ifndef FLAGS_H
#define FLAGS_H
#include <QColor>

class FLAGS{
public:
    static const QColor wallColor;
    static const QColor outsideColor;
    static const QColor emptyColor;
    static const QColor boxColor;
    static const QColor pointColor;
    static const QColor circleBoxColor;
    static const QColor spawnColor;
    static const QColor eraserColor;
    static const QColor frameColor;

    static QColor manColor;

    static const char EMPTY = 'e';
    static const char BOX = 'b';
    static const char WALL = 'w';
    static const char POINT = 'p';
    static const char OUTSIDE = 'o';
    static const char BOX_ON_POINT = 'u';
};

#endif // FLAGS_H
