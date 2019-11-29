#ifndef STATISTIC_H
#define STATISTIC_H

#include "bintoint.h"
#include "levelslist.h"

#include <QtDebug>
#include <QDirIterator>
#include <QString>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <QFile>
#include <QDataStream>
#include <QBitArray>

class Stat{
    friend class LevelLogic;
    friend class LevelHandler;
public:
    static unsigned int getMoves();
    static unsigned int getPushes();

    static void read();
    static void write();

    static void updScore(size_t levelNum);

    static unsigned int selectedLevel;
    static unsigned int minPrintedLevel;
    static unsigned int maxPrintedLevel;

    static unsigned int GetNumber();
    static int GetStat(size_t);
    static void addLevel();
private:
    static void reset();
    static void move();
    static void push();
    static unsigned int moves;
    static unsigned int pushedBoxes;

    static std::vector<int> score;

    static const std::string scoreFileDir;
};

#endif // STATISTIC_H
