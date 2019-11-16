#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H
#pragma once
#include "FLAGS.h"

#include <QApplication>
#include "bintoint.h"
#include "levellogic.h"
#include "statistic.h"
#include <string>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <QFile>
#include <QtDebug>
#include <QDataStream>
#include <stack>
#include <vector>
#include <QBitArray>

class LevelHandler{
public:

    static void read(const  QString& file_name);

private:
    friend class LevelDrawer;
    friend class LevelLogic;

    static unsigned int BoxOnPointNumber;
    static unsigned int BoxNumber;
    static unsigned int SizeX, SizeY;  //size of playground
    static unsigned int PosX, PosY;    //spawnpoint
    static bool success;

    static std::list<std::pair<unsigned int, unsigned int>>  CheckList;
    static std::vector<std::vector<char>> Field;
    static void GetSize(unsigned int& X, unsigned int& Y);
    static void GetSpawn(unsigned int& X, unsigned int& Y);
    static unsigned int GetBoxOnPointNumber();
    static unsigned int GetBoxNumber();
    static unsigned int& GetPosX();
    static unsigned int& GetPosY();
    static bool isSuccess();
};

#endif // LEVELHANDLER_H
