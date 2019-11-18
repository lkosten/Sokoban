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
public:
    static void draw(MainWindow &window);
    static RGB GetColor(size_t x, size_t y);
};

#endif // PALLET_H
