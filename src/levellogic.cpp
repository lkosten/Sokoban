#include "levellogic.h"
#include "levelhandler.h"

unsigned int LevelLogic::CorrectNumber = LevelHandler::GetBoxOnPointNumber();
unsigned int LevelLogic::TotalNumber = LevelHandler::GetBoxNumber();

bool LevelLogic::MoveRight(){
    return Move(1, 0);
}
bool LevelLogic::MoveLeft(){
    return Move(-1, 0);

}
bool LevelLogic::MoveDown(){
    return Move(0, 1);

}
bool LevelLogic::MoveUp(){
    return Move(0, -1);

}

bool LevelLogic::Move(int i,int j){
    unsigned int PosX = LevelHandler::GetPosX();
    unsigned int PosY = LevelHandler::GetPosY();

    LevelHandler::CheckList.push_back({PosX, PosY});
    LevelHandler::CheckList.push_back({static_cast<unsigned int>(static_cast<int>(PosX) + i), static_cast<unsigned int>(static_cast<int>(PosY) + j)});
    LevelHandler::CheckList.push_back({static_cast<unsigned int>(static_cast<int>(PosX) + i*2), static_cast<unsigned int>(static_cast<int>(PosY) + j*2)});

    //PLAYER - EMPTY
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i)][static_cast<unsigned long long>(static_cast<int>(PosY) + j)] == LevelHandler::EMPTY){
        PosX = static_cast<unsigned int>(static_cast<int>(PosX) + i);
        PosY = static_cast<unsigned int>(static_cast<int>(PosY) + j);
        return true;
    }
    //PLAYER - BOX - EMPTYorPOINT
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i)][static_cast<unsigned long long>(static_cast<int>(PosY) + j)] == LevelHandler::BOX &&
            ( LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] == LevelHandler::EMPTY
                || LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] == LevelHandler::POINT)
            ){

        PosX = static_cast<unsigned int>(static_cast<int>(PosX) + i);
        PosY = static_cast<unsigned int>(static_cast<int>(PosY) + j);

        //PLAYER - BOX - POINT
        if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] == LevelHandler::POINT){
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i)][static_cast<unsigned long long>(static_cast<int>(PosY) + j)] = LevelHandler::EMPTY;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] = LevelHandler::BOX_ON_POINT;
            CorrectNumber++;
            return true;
        }
        else{//PLAYER - BOX - EMPTY
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i)][static_cast<unsigned long long>(static_cast<int>(PosY) + j)] = LevelHandler::EMPTY;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] = LevelHandler::BOX;
            return true;
        }
    }

    //PLAYER - BOXonPOINT - EMPTYorPOINT
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i)][static_cast<unsigned long long>(static_cast<int>(PosY) + j)] == LevelHandler::BOX_ON_POINT &&
            ( LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] == LevelHandler::EMPTY
                || LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] == LevelHandler::POINT)
            ){

        PosX = static_cast<unsigned int>(static_cast<int>(PosX) + i);
        PosY = static_cast<unsigned int>(static_cast<int>(PosY) + j);

        //PLAYER - BOXonPOINT - POINT
        if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] == LevelHandler::POINT){
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i)][static_cast<unsigned long long>(static_cast<int>(PosY) + j)] = LevelHandler::POINT;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] = LevelHandler::BOX_ON_POINT;
            return true;
        }
        else{//PLAYER - BOXonPOINT - EMPTY
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i)][static_cast<unsigned long long>(static_cast<int>(PosY) + j)] = LevelHandler::POINT;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(PosY) + j*2)] = LevelHandler::BOX;
            CorrectNumber--;
            return true;
        }
    }
    return false;
}
bool LevelLogic::CheckNum(){
    if (CorrectNumber == TotalNumber) return true;
    else return false;
}
