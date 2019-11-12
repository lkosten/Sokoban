#include "levelcreatorbrush.h"

tools CreatorBrush::currentTool = T_RUBBER;

void CreatorBrush::ChangeTool(bool up){
    if (up && currentTool != T_RUBBER) currentTool = static_cast<tools>(static_cast<int>(currentTool) - 1);

    if (!up && currentTool != T_SPAWN) currentTool = static_cast<tools>(static_cast<int>(currentTool) + 1);
}

void CreatorBrush::SetGate(unsigned int x, unsigned int y){
    switch(currentTool){
        case T_RUBBER :{
            CreatorMap::Field[x][y] = OUTSIDE;
            break;
        }
        case T_WALL :{
            CreatorMap::Field[x][y] = WALL;
            break;
        }
        case T_BOX :{
            switch(CreatorMap::Field[x][y]){
            case POINT:{
                CreatorMap::Field[x][y] = BOX_ON_POINT;
                break;
            }
            case BOX:{
                CreatorMap::Field[x][y] = OUTSIDE;
                break;
            }
            case BOX_ON_POINT:{
                CreatorMap::Field[x][y] = POINT;
                break;
            }
            default:{
                CreatorMap::Field[x][y] = BOX;
            }
            }
            break;
        }
        case T_POINT :{
        switch(CreatorMap::Field[x][y]){
        case POINT:{
            CreatorMap::Field[x][y] = OUTSIDE;
            break;
        }
        case BOX:{
            CreatorMap::Field[x][y] = BOX_ON_POINT;
            break;
        }
        case BOX_ON_POINT:{
            CreatorMap::Field[x][y] = BOX;
            break;
        }
        default:{
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
