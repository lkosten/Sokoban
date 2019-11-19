#ifndef PALLET_H
#define PALLET_H
#include "FLAGS.h"
#include <algorithm>
#include <QtOpenGL>
#include <vector>
#include <QPainter>
#include "mainwindow.h"

struct RGB{
    int R;
    int G;
    int B;
};

class ColorPallete{
    static std::vector<std::vector<RGB>> matrix;
    static qreal R,G,B;
    static qreal ColumnX,ColumnY;
    static qreal ColumnH,ColumnW;
    static qreal FrameY;
    static qreal PalleteX, PalleteY, PalleteH, PalleteAcc;
    static bool changing;

    static void drawMatrix(MainWindow &window);
    static void drawColumn(MainWindow &window);
    static RGB GetColor(size_t x, size_t y);

public:
    static void init(qreal X, qreal Y, qreal H, qreal accuracy);
    static void draw(MainWindow &window);
    static void Hold(qreal Y);
    static void Click(qreal X, qreal Y);
    static void Release();
};

#endif // PALLET_H
