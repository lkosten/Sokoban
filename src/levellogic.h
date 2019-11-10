#ifndef LEVELLOGIC_H
#define LEVELLOGIC_H

class LevelLogic{
    static unsigned int CorrectNumber;
    static unsigned int TotalNumber;
    static unsigned int PosX;
    static unsigned int PosY;

    static bool MoveRight();
    static bool MoveLeft();
    static bool MoveDown();
    static bool MoveUp();

public:
    static bool Move(int i, int j);
    static bool CheckNum();
};

#endif // LEVELLOGIC_H
