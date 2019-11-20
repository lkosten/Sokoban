#ifndef PALLET_H
#define PALLET_H
#include "FLAGS.h"
#include <algorithm>
#include <QtOpenGL>
#include <QColor>
#include <vector>
#include <QPainter>
#include "mainwindow.h"

class ColorPallete{
    static qreal R,G,B;
    static int sR,sG,sB;
    static qreal ColumnX,ColumnY;
    static qreal ColumnH,ColumnW;
    static qreal FrameY;
    static qreal PalleteX, PalleteY, PalleteH, PalleteAcc;
    static qreal SelectX,SelectY;
    static bool changing;
    static bool selecting;

    static void drawMatrix(MainWindow &window);
    static void drawColumn(MainWindow &window);

public:
    static void init(qreal X, qreal Y, qreal H, qreal accuracy);
    static void draw(MainWindow &window);
    static void Hold(qreal X, qreal Y);
    static void Click(qreal X, qreal Y);
    static void Release();
    static QColor GetColor();
};

#endif // PALLET_H
