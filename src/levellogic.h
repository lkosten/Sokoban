#ifndef LEVELLOGIC_H
#define LEVELLOGIC_H

#include "FLAGS.h"
#include "levelhandler.h"
#include "statistic.h"
#include <QtDebug>
#include <vector>
#include <algorithm>
#include <list>

class LevelLogic{
    static unsigned int CorrectNumber;
    static unsigned int TotalNumber;
    friend class LevelHandler;
    static bool Move(int i, int j);
public:


    static bool MoveRight();
    static bool MoveLeft();
    static bool MoveDown();
    static bool MoveUp();
    static unsigned int GetCorrectNumber();
    static unsigned int GetTotalNumber();
    static bool CheckNum();
};

#endif // LEVELLOGIC_H
