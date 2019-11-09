#ifndef LEVELSLIST_H
#define LEVELSLIST_H

#include <QtDebug>
#include <QDirIterator>
#include <QString>
#include <vector>
#include <algorithm>

class LevelsList{
std::vector<QString> List;
QString GetFName(unsigned int n);
QString GetFDirectory(unsigned int n);
public:
    LevelsList();
    std::pair<QString,QString> GetFNameDir(unsigned int n);
    unsigned int GetNumber();
};

#endif // LEVELSLIST_H
