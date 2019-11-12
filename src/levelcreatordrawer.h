#ifndef LEVELCREATORDRAWER_H
#define LEVELCREATORDRAWER_H

#include <vector>
#include "mainwindow.h"

class CreatorDrawer{
    friend class CreatorMap;
    friend class LevelCreator;
public:
    static void fullRender(MainWindow&);
};

#endif // LEVELCREATORDRAWER_H
