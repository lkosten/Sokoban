#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H
#pragma once
/*
structure of binary:

size of map : int X,int Y
number of walls : int n
coords of walls : {x1,y1,x2,y2,...,xn,yn}
number of boxes : int n
coords of boxes : {x1,y1,x2,y2,...,xn,yn}
number of points : int N
coords of points : {x1,y1,x2,y2,...,xn,yn}
spawnpoint : int x, int y

flags:

e - empty
o - outside
w - wall
b - box
p - point
u - box + point
*/
#include <QApplication>
#include "bintoint.h"
#include <string>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <QFile>
#include <QDataStream>

class LevelHandler{
private:
    char** Field;
    unsigned int SizeX, SizeY;
    unsigned int PosX, PosY;
    bool success = false;
public:
    LevelHandler();
    LevelHandler(const  QString& file_name);
    void read(const  QString& file_name);
    void write(const  QString& file_name);
    bool step_left();
    bool step_right();
    bool step_up();
    bool step_down();
    bool isSuccess();
};

#endif // LEVELHANDLER_H
