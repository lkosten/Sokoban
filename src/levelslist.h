#ifndef LEVELSLIST_H
#define LEVELSLIST_H

#include <QtDebug>
#include <QDirIterator>
#include <QString>
#include <vector>
#include <algorithm>

class LevelsList{
private:
    static std::vector<QString> List;
    static QString GetFName(unsigned int n);
    static QString GetFDirectory(unsigned int n);
public:
    static void GetList();
    static std::pair<QString,QString> GetFNameDir(unsigned int n);
    static size_t GetNumber();
    static size_t selectedLevel;
};

#endif // LEVELSLIST_H
