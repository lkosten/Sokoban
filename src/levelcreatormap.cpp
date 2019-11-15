#include "levelcreatormap.h"

unsigned int CreatorMap::SizeX = 10;
unsigned int CreatorMap::SizeY = 10;
unsigned int CreatorMap::PosX = 0;
unsigned int CreatorMap::PosY = 0;
unsigned int CreatorMap::BoxCounter = 0;
unsigned int CreatorMap::PointCounter = 0;
std::vector<std::vector<char>> CreatorMap::Field = std::vector<std::vector<char>>();

void CreatorMap::SetSize(unsigned int x, unsigned int y){
    SizeX = x;
    SizeY = y;

    std::vector<char> temp;
    temp.resize(SizeY, static_cast<char>(OUTSIDE));

    Field.resize(SizeX, temp);
    for(unsigned int i = 0; i < SizeX; i++){
        Field[i].resize(SizeY, static_cast<char>(OUTSIDE));
    }
}
