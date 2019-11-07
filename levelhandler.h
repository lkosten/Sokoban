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
*/
#include <string>
#include <stdio.h>
#include <conio.h>
#include <fstream>

class LevelHandler{
private:
    char** Field;
    int SizeX, SizeY;
    int PosX, PosY;
public:
    LevelHandler();
    LevelHandler(const char* file_name);
    bool read(const char* file_name);
    bool write(const char* file_name);
    bool step_left();
    bool step_right();
    bool step_up();
    bool step_down();
};

#endif // LEVELHANDLER_H
