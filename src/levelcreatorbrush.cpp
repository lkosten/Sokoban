#include "levelcreatorbrush.h"

tools CreatorBrush::currentTool = T_RUBBER;

void CreatorBrush::ChangeTool(bool up){
    if (up && currentTool != T_RUBBER) currentTool = static_cast<tools>(static_cast<int>(currentTool) - 1);

    if (!up && currentTool != T_SPAWN) currentTool = static_cast<tools>(static_cast<int>(currentTool) + 1);
}

void CreatorBrush::SetGate(unsigned int x, unsigned int y){
    switch(currentTool){
        case T_RUBBER :{
            CreatorMap::Field[x][y] = FLAGS::OUTSIDE;
            break;
        }
        case T_WALL :{
            CreatorMap::Field[x][y] = FLAGS::WALL;
            break;
        }
        case T_BOX :{
            switch(CreatorMap::Field[x][y]){
            case FLAGS::POINT:{
                CreatorMap::Field[x][y] = FLAGS::BOX_ON_POINT;
                break;
            }
            case FLAGS::BOX:{
                CreatorMap::Field[x][y] = FLAGS::OUTSIDE;
                break;
            }
            case FLAGS::BOX_ON_POINT:{
                CreatorMap::Field[x][y] = FLAGS::POINT;
                break;
            }
            default:{
                CreatorMap::Field[x][y] = FLAGS::BOX;
            }
            }
            break;
        }
        case T_POINT :{
        switch(CreatorMap::Field[x][y]){
        case FLAGS::POINT:{
            CreatorMap::Field[x][y] = FLAGS::OUTSIDE;
            break;
        }
        case FLAGS::BOX:{
            CreatorMap::Field[x][y] = FLAGS::BOX_ON_POINT;
            break;
        }
        case FLAGS::BOX_ON_POINT:{
            CreatorMap::Field[x][y] = FLAGS::BOX;
            break;
        }
        default:{
            CreatorMap::Field[x][y] = FLAGS::POINT;
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
