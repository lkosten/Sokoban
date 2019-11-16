#include "statistic.h"

unsigned int Stat::moves = 0;
unsigned int Stat::pushedBoxes = 0;

void Stat::reset(){
    moves = 0;
    pushedBoxes = 0;
}
void Stat::move(){
    moves++;
}
void Stat::push(){
    moves++;
    pushedBoxes++;
}
unsigned int Stat::getMoves(){
    return moves;
}
unsigned int Stat::getPushes(){
    return pushedBoxes;
}
