#ifndef LEVELLOGIC_H
#define LEVELLOGIC_H

#include <QtDebug>
#include <vector>
#include <algorithm>
#include <list>

class LevelLogic{
    static unsigned int CorrectNumber;
    static unsigned int TotalNumber;

    static bool Move(int i, int j);
public:

    static bool MoveRight();
    static bool MoveLeft();
    static bool MoveDown();
    static bool MoveUp();

    static bool CheckNum();
};

#endif // LEVELLOGIC_H
