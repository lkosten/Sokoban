#ifndef LEVELDRAWER_H
#define LEVELDRAWER_H

#include "mainwindow.h"
#include "levelhandler.h"


class LevelDrawer
{
private:
    static const size_t protectedAreaY = 200;
    static const size_t protectedAreaX = 300;

    static QColor wallColor;
    static QColor outsideColor;
    static QColor emptyColor;
    static QColor manColor;
    static QColor boxColor;
    static QColor pointColor;
    static QColor circleBoxColor;


public:
    static void fullRender(MainWindow&);


};

#endif // LEVELDRAWER_H
