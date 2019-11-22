#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H
#include "FLAGS.h"

#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stack>
#include <string>
#include <iostream>
#include <QString>
#include <QTextEdit>
#include <QWidget>
#include <algorithm>
#include <QDebug>
#include <QResource>
#include <fstream>
#include "levelcreatorbrush.h"
#include "levelcreatordrawer.h"
#include "levelcreatormap.h"
#include "mainwindow.h"



class LevelCreator{
    static int windowX,windowY;
public:
    static void initMap();
    static void MouseClicked(int x, int y);
    static void KeyUp();
    static void KeyDown();
    static void clear();
    static bool check();
    static void Write(QString name);
};

#endif // LEVELCREATOR_H
