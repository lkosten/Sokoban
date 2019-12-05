#include "levelhandler.h"

/*
structure of binary:

size of map : int X,int Y
number of walls : int n
coords of walls : {x1,y1,x2,y2,...,xn,yn}
number of boxes : int n
coords of boxes : {x1,y1,x2,y2,...,xn,yn}
number of points : int N
coords of points : {x1,y1,x2,y2,...,xn,yn}
spawnpoint : int x, int y

flags:

e - empy
o - outside
w - wall
b - box
p - point
u - box + point
*/

bool LevelHandler::success = true;
unsigned int LevelHandler::SizeX = 0;
unsigned int LevelHandler::SizeY = 0; //size of playground
unsigned int LevelHandler::PosX = 0;
unsigned int LevelHandler::PosY = 0;
unsigned int LevelHandler::BoxNumber = 0;
unsigned int LevelHandler::BoxOnPointNumber = 0;

std::vector<std::vector<char>> LevelHandler::Field = std::vector<std::vector<char>>();
std::list<std::pair<unsigned int, unsigned int>> LevelHandler::CheckList = std::list<std::pair<unsigned int, unsigned int>>();

void LevelHandler::read(const  QString& file_name){
    Stat::reset();
    BoxOnPointNumber = 0;
    BoxNumber = 0;
    success = true;
    Field.clear();

    QFile file(file_name);

    file.open(QIODevice::ReadOnly);
    if (file.size() == 0){
        success = false;
        return;
    }

    QByteArray InputArray = file.readAll();
    QDataStream Input(InputArray);

    unsigned int i =0;

    SizeX = BinToInt(Input);
    SizeY = BinToInt(Input);
    PosX = BinToInt(Input);
    PosY = BinToInt(Input);

    if( SizeX > 60 || SizeY > 60 || PosX > SizeX || PosY > SizeY){
        success = false;
        return;
    }

    std::vector<char> temp;
    temp.resize(SizeY,FLAGS::outside());
    Field.resize(SizeX,temp);

    //place walls
    i = BinToInt(Input);
    if( i > 10000){
        success = false;
        return;
    }
    try{
        for(;i>0;i-=2){
            unsigned int TempX,TempY;
            TempX = BinToInt(Input);
            TempY = BinToInt(Input);
            if(TempX < SizeX && TempY < SizeY){
            Field[TempX][TempY] = FLAGS::WALL;
            }
            else{
                throw "Field overflow!";
            }
        }
    }
    catch(const char* msg){
        success = false;
        return;
    }

    //field ground where we can walk with EMPTY
    std::stack<std::pair<unsigned int,unsigned int>> dfs;
    dfs.push({PosX,PosY});
    try{
        while(dfs.size()){
            std::pair<unsigned int,unsigned int> Current = dfs.top();
            dfs.pop();
            if(Current.first != 0 && Current.first != SizeX - 1 && Current.second != 0 && Current.second != SizeY - 1){
                Field[Current.first][Current.second] = FLAGS::EMPTY;
                if(Field[Current.first + 1][Current.second] == FLAGS::OUTSIDE) dfs.push({Current.first + 1, Current.second});
                if(Field[Current.first][Current.second + 1] == FLAGS::OUTSIDE) dfs.push({Current.first, Current.second + 1});
                if(Field[Current.first - 1][Current.second] == FLAGS::OUTSIDE) dfs.push({Current.first - 1, Current.second});
                if(Field[Current.first][Current.second - 1] == FLAGS::OUTSIDE) dfs.push({Current.first, Current.second - 1});
            }
            else{
                throw "Field overflow!";
            }
        }
    }
    catch(const char* msg){
        success = false;
        return;
    }


    //place boxes
    i = BinToInt(Input);
    if( i > 10000){
        success = false;
        return;
    }
    BoxNumber = i/2;
    try{
        for(;i>0;i-=2){
            unsigned int TempX,TempY;
            TempX = BinToInt(Input);
            TempY = BinToInt(Input);
            if(TempX < SizeX && TempY < SizeY){
            Field[TempX][TempY] = FLAGS::BOX;
            }
            else{
                throw "Field overflow!";
            }
        }
    }
    catch(const char* msg){
        success = false;
        return;
    }

    //place points
    i = BinToInt(Input);
    if( i > 10000){
        success = false;
        return;
    }
    try{
        for(;i>0;i-=2){
            unsigned int TempX,TempY;
            TempX = BinToInt(Input);
            TempY = BinToInt(Input);
            if(TempX < SizeX && TempY < SizeY){
                if(Field[TempX][TempY] != FLAGS::BOX) Field[TempX][TempY]= FLAGS::POINT;
                else {Field[TempX][TempY]= FLAGS::BOX_ON_POINT; BoxOnPointNumber++;}
            }
            else{
                throw "Field overflow!";
            }
        }
    }
    catch(const char* msg){
        success = false;
        return;
    }

    LevelLogic::CorrectNumber = BoxOnPointNumber;
    LevelLogic::TotalNumber = BoxNumber;
}

void LevelHandler::GetSize(unsigned int& X, unsigned int& Y){
    X = SizeX;
    Y = SizeY;
}

void LevelHandler::GetSpawn(unsigned int& X, unsigned int& Y){
    X = PosX;
    Y = PosY;
}

bool LevelHandler::isSuccess(){
    return success;
}

unsigned int LevelHandler::GetBoxOnPointNumber(){
    return BoxOnPointNumber;
}

unsigned int LevelHandler::GetBoxNumber(){
    return BoxNumber;
}

unsigned int& LevelHandler::GetPosX(){
    return PosX;
}

unsigned int& LevelHandler::GetPosY(){
    return PosY;
}
