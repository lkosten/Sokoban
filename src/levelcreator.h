#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include <QString>
#include "levelcreatorbrush.h"
#include "levelcreatordrawer.h"
#include "levelcreatormap.h"

class LevelCreator{
    static int windowX,windowY;
public:
    static void initMap();
    static void MouseClicked(int x, int y);
    static void KeyUp();
    static void KeyDown();
    static void Write(QString name);
};

#endif // LEVELCREATOR_H
