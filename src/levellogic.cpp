#include "levellogic.h"

unsigned int LevelLogic::CorrectNumber = 0;
unsigned int LevelLogic::TotalNumber = 0;
bool LevelLogic::moved = false;
bool LevelLogic::pushed = false;

bool LevelLogic::MoveRight(){
    bool temp = Move(1, 0);
    if(isMoved()) Stat::move();
    if(isPushed()) Stat::push();
    return temp;
}
bool LevelLogic::MoveLeft(){
    bool temp = Move(-1, 0);
    if(isMoved()) Stat::move();
    if(isPushed()) Stat::push();
    return temp;

}
bool LevelLogic::MoveDown(){
    bool temp = Move(0, 1);
    if(isMoved()) Stat::move();
    if(isPushed()) Stat::push();
    return temp;

}
bool LevelLogic::MoveUp(){
    bool temp = Move(0, -1);
    if(isMoved()) Stat::move();
    if(isPushed()) Stat::push();
    return temp;

}

bool LevelLogic::Move(int i,int j){

    moved = false;
    pushed = false;

    LevelHandler::CheckList.clear();
    LevelHandler::CheckList.push_back({LevelHandler::PosX, LevelHandler::PosY});
    LevelHandler::CheckList.push_back({static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i), static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j)});
    LevelHandler::CheckList.push_back({static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i*2), static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j*2)});

    //PLAYER - EMPTY
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] == FLAGS::EMPTY){
        LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
        LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
        moved = true;
        return true;
    }
    //PLAYER - POINT
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] == FLAGS::POINT){
        LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
        LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
        moved = true;
        return true;
    }
    //PLAYER - BOX - EMPTYorPOINT
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] == FLAGS::BOX &&
            ( LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == FLAGS::EMPTY
                || LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == FLAGS::POINT)
            ){

        //PLAYER - BOX - POINT
        if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == FLAGS::POINT){
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] = FLAGS::EMPTY;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] = FLAGS::BOX_ON_POINT;
            CorrectNumber++;
            LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
            LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
            pushed = true;
            return true;
        }
        else{//PLAYER - BOX - EMPTY
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] = FLAGS::EMPTY;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] = FLAGS::BOX;
            LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
            LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
            pushed = true;
            return true;
        }
    }

    //PLAYER - BOXonPOINT - EMPTYorPOINT
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] == FLAGS::BOX_ON_POINT &&
            ( LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == FLAGS::EMPTY
                || LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == FLAGS::POINT)
            ){
        //PLAYER - BOXonPOINT - POINT
        if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == FLAGS::POINT){
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] = FLAGS::POINT;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] = FLAGS::BOX_ON_POINT;
            LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
            LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
            pushed = true;
            return true;
        }
        else{//PLAYER - BOXonPOINT - EMPTY
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] = FLAGS::POINT;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] = FLAGS::BOX;
            CorrectNumber--;
            LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
            LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
            pushed = true;
            return true;
        }
    }
    return false;
}
bool LevelLogic::CheckNum(){
    if (CorrectNumber == TotalNumber) return true;
    else return false;
}
unsigned int LevelLogic::GetCorrectNumber(){
    return CorrectNumber;
}
unsigned int LevelLogic::GetTotalNumber(){
    return TotalNumber;
}
bool LevelLogic::isPushed(){
    return pushed;
}
bool LevelLogic::isMoved(){
    return moved;
}
