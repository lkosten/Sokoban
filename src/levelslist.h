#ifndef LEVELSLIST_H
#define LEVELSLIST_H

#include <QtDebug>
#include <QDirIterator>
#include <string>
#include <stack>
#include <QString>

class LevelsList{
int Number;
QString* List;
public:
    LevelsList();
    QString GetFName(int n);
    QString GetFDirectory(int n);
    int GetNumber();
};

#endif // LEVELSLIST_H
