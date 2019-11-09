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
#include <stack>
#include <vector>

class LevelHandler{
public:
    static const char EMPTY = 'e';
    static const char BOX = 'b';
    static const char WALL = 'w';
    static const char OUTSIDE = 'o';
    static const char POINT = 'p';
    static const char BOX_ON_POINT = 'u';
private:
    static std::vector<std::vector<char>> Field;
    bool success = false;
    void read(const  QString& file_name);
    unsigned int SizeX, SizeY;  //size of playground
    unsigned int PosX, PosY;    //spawnpoint
public:
    LevelHandler(const  QString& file_name);
    ~LevelHandler();
    void GetSize(unsigned int& X, unsigned int& Y);
    void GetSpawn(unsigned int& X, unsigned int& Y);
    bool isSuccess();
};

#endif // LEVELHANDLER_H
