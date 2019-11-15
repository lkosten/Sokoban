#include "levelcreatorbrush.h"

tools CreatorBrush::currentTool = T_RUBBER;

void CreatorBrush::ChangeTool(bool up){
    if (up && currentTool != T_RUBBER) currentTool = static_cast<tools>(static_cast<int>(currentTool) - 1);

    if (!up && currentTool != T_SPAWN) currentTool = static_cast<tools>(static_cast<int>(currentTool) + 1);
}

void CreatorBrush::SetGate(unsigned int x, unsigned int y){
    switch(currentTool){
        case T_RUBBER :{
        if(CreatorMap::Field[x][y] == BOX)CreatorMap::BoxCounter--;
        if(CreatorMap::Field[x][y] == POINT)CreatorMap::PointCounter--;
        if(CreatorMap::Field[x][y] == BOX_ON_POINT){CreatorMap::BoxCounter--; CreatorMap::PointCounter--;}
            CreatorMap::Field[x][y] = OUTSIDE;
            break;
        }
        case T_WALL :{
        if(CreatorMap::Field[x][y] == BOX)CreatorMap::BoxCounter--;
        if(CreatorMap::Field[x][y] == POINT)CreatorMap::PointCounter--;
        if(CreatorMap::Field[x][y] == BOX_ON_POINT){CreatorMap::BoxCounter--; CreatorMap::PointCounter--;}
            CreatorMap::Field[x][y] = WALL;
            break;
        }
        case T_BOX :{
            switch(CreatorMap::Field[x][y]){
            case POINT:{
                CreatorMap::BoxCounter++;
                CreatorMap::Field[x][y] = BOX_ON_POINT;
                break;
            }
            case BOX:{
                CreatorMap::BoxCounter--;
                CreatorMap::Field[x][y] = OUTSIDE;
                break;
            }
            case BOX_ON_POINT:{
                CreatorMap::BoxCounter--;
                CreatorMap::Field[x][y] = POINT;
                break;
            }
            default:{
                CreatorMap::BoxCounter++;
                CreatorMap::Field[x][y] = BOX;
            }
            }
            break;
        }
        case T_POINT :{
        switch(CreatorMap::Field[x][y]){
        case POINT:{
            CreatorMap::PointCounter--;
            CreatorMap::Field[x][y] = OUTSIDE;
            break;
        }
        case BOX:{
            CreatorMap::PointCounter++;
            CreatorMap::Field[x][y] = BOX_ON_POINT;
            break;
        }
        case BOX_ON_POINT:{
            CreatorMap::PointCounter--;
            CreatorMap::Field[x][y] = BOX;
            break;
        }
        default:{
            CreatorMap::PointCounter++;
            CreatorMap::Field[x][y] = POINT;
        }
        }
        break;
        }
        case T_SPAWN :{
            CreatorMap::PosX=x;
            CreatorMap::PosY=y;
            break;
        }
    }
}

unsigned int CreatorBrush::GetToolNum(){
    return static_cast<unsigned int>(currentTool);
}
