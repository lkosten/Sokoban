#ifndef LEVELCREATORDRAWER_H
#define LEVELCREATORDRAWER_H

#include <vector>
#include <algorithm>
#include "mainwindow.h"

class MainWindow;

class CreatorDrawer{
    friend class CreatorMap;
    friend class LevelCreator;

    static QColor wallColor;
    static QColor outsideColor;
    static QColor emptyColor;
    static QColor manColor;
    static QColor boxColor;
    static QColor pointColor;
    static QColor circleBoxColor;
    static QColor spawnColor;
    static QColor eraserColor;

    static const size_t FieldX = 100;
    static const size_t FieldY = 100;

    static const size_t FieldWidth = 400;
    static const size_t FieldHeight = 400;

    static const size_t ToolsX = 600;
    static const size_t ToolsY = 100;

    static const size_t ToolsWidth = 100;
    static const size_t ToolsHeight = 400;

public:
    static void fullRender(MainWindow&);
};

#endif // LEVELCREATORDRAWER_H
