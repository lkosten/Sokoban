#ifndef LEVELSLIST_H
#define LEVELSLIST_H

#include "FLAGS.h"

#include <QtDebug>
#include <QDirIterator>
#include <QString>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class LevelsList{
private:
    friend class LevelCreator;
    static std::vector<QString> List;
    static QString GetFName(unsigned int n);
    static QString GetFDirectory(unsigned int n);
public:
    static void GetList();
    static std::pair<QString,QString> GetFNameDir(unsigned int n);
    static unsigned int GetNumber();
    static unsigned int selectedLevel;
    static unsigned int minPrintedLevel;
    static unsigned int maxPrintedLevel;
};

#endif // LEVELSLIST_H
