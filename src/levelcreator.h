#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include <QString>
class LevelCreator{
public:
    static void MouseClicked(int x, int y);
    static void KeyUp();
    static void KeyDown();
    static void Write(QString name);
};

#endif // LEVELCREATOR_H
