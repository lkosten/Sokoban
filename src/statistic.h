#ifndef STATISTIC_H
#define STATISTIC_H

class Stat{
    friend class LevelLogic;
    friend class LevelHandler;
public:
    static unsigned int getMoves();
    static unsigned int getPushes();
private:
    static void reset();
    static void move();
    static void push();
    static unsigned int moves;
    static unsigned int pushedBoxes;
};

#endif // STATISTIC_H
