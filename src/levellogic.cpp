#include "levellogic.h"
#include "levelhandler.h"

unsigned int LevelLogic::CorrectNumber = LevelHandler::GetBoxOnPointNumber();
unsigned int LevelLogic::TotalNumber = LevelHandler::GetBoxNumber();

bool LevelLogic::MoveRight(){
   // std::swap(LevelHandler::PosX,LevelHandler::PosY);
    bool temp = Move(1, 0);
   // std::swap(LevelHandler::PosX,LevelHandler::PosY);
    return temp;
}
bool LevelLogic::MoveLeft(){
   // std::swap(LevelHandler::PosX,LevelHandler::PosY);
    bool temp = Move(-1, 0);
   // std::swap(LevelHandler::PosX,LevelHandler::PosY);
    return temp;

}
bool LevelLogic::MoveDown(){
   // std::swap(LevelHandler::PosX,LevelHandler::PosY);
    bool temp = Move(0, 1);
   // std::swap(LevelHandler::PosX,LevelHandler::PosY);
    return temp;

}
bool LevelLogic::MoveUp(){
   // std::swap(LevelHandler::PosX,LevelHandler::PosY);
    bool temp = Move(0, -1);
   // std::swap(LevelHandler::PosX,LevelHandler::PosY);
    return temp;

}

bool LevelLogic::Move(int i,int j){


    LevelHandler::CheckList.clear();
    LevelHandler::CheckList.push_back({LevelHandler::PosX, LevelHandler::PosY});
    LevelHandler::CheckList.push_back({static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i), static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j)});
    LevelHandler::CheckList.push_back({static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i*2), static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j*2)});

    qDebug() << LevelHandler::PosX<<" "<<LevelHandler::PosY;
    qDebug() << LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)]<<" "<< LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)];

    //PLAYER - EMPTY
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] == LevelHandler::EMPTY){
        LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
        LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
        return true;
    }
    //PLAYER - POINT
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] == LevelHandler::POINT){
        LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
        LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
        return true;
    }
    //PLAYER - BOX - EMPTYorPOINT
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] == LevelHandler::BOX &&
            ( LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == LevelHandler::EMPTY
                || LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == LevelHandler::POINT)
            ){

        //PLAYER - BOX - POINT
        if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == LevelHandler::POINT){
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] = LevelHandler::EMPTY;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] = LevelHandler::BOX_ON_POINT;
            CorrectNumber++;
            LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
            LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
            return true;
        }
        else{//PLAYER - BOX - EMPTY
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] = LevelHandler::EMPTY;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] = LevelHandler::BOX;
            LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
            LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
            return true;
        }
    }

    //PLAYER - BOXonPOINT - EMPTYorPOINT
    if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] == LevelHandler::BOX_ON_POINT &&
            ( LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == LevelHandler::EMPTY
                || LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == LevelHandler::POINT)
            ){
        //PLAYER - BOXonPOINT - POINT
        if(LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] == LevelHandler::POINT){
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] = LevelHandler::POINT;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] = LevelHandler::BOX_ON_POINT;
            LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
            LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
            return true;
        }
        else{//PLAYER - BOXonPOINT - EMPTY
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j)] = LevelHandler::POINT;
            LevelHandler::Field[static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosX) + i*2)][static_cast<unsigned long long>(static_cast<int>(LevelHandler::PosY) + j*2)] = LevelHandler::BOX;
            CorrectNumber--;
            LevelHandler::PosX = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosX) + i);
            LevelHandler::PosY = static_cast<unsigned int>(static_cast<int>(LevelHandler::PosY) + j);
            return true;
        }
    }
    return false;
}
bool LevelLogic::CheckNum(){
    if (CorrectNumber == TotalNumber) return true;
    else return false;
}
