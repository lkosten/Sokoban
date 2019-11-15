#ifndef LEVELCREATORDRAWER_H
#define LEVELCREATORDRAWER_H
#include "FLAGS.h"
#include <vector>
#include <algorithm>
#include <QtOpenGL>
#include <QPainter>
#include "mainwindow.h"
#include "levelcreatorbrush.h"

class MainWindow;

class CreatorDrawer{
    friend class CreatorMap;
    friend class LevelCreator;

    static const size_t FieldX = 100;
    static const size_t FieldY = 100;

    static const size_t FieldWidth = 400;
    static const size_t FieldHeight = 400;

    static const size_t ToolsX = 600;
    static const size_t ToolsY = 100;

    static const size_t ToolsWidth = 100;
    static const size_t ToolsHeight = 400;

    static const size_t XresizeX = 300;
    static const size_t XresizeY = 525;

    static const size_t YresizeX = 25;
    static const size_t YresizeY = 300;

public:
    static void fullRender(MainWindow&);
};

#endif // LEVELCREATORDRAWER_H
