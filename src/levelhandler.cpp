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

void LevelHandler::read(const  QString& file_name){
    success = false;
    Field.clear();

    QFile file(":/levels/" + file_name);
    file.open(QIODevice::ReadOnly);
    if (file.size() == 0){
        success = false;
        return;
    }
    QByteArray InputArray = file.readAll();
    file.close();
    unsigned int counter = 0;
    unsigned int i =0;

    SizeX = BinToInt(InputArray,counter);
    counter+=4;
    SizeY= BinToInt(InputArray,counter);
    counter+=4;

    PosY = BinToInt(InputArray,counter);
    counter+=4;
    PosX = BinToInt(InputArray,counter);
    counter+=4;

    for (;i<SizeX;i++){
        std::vector<char> temp;
        temp.resize(SizeY);
        for (unsigned int j =0;j<SizeY;j++){
            temp[j] = OUTSIDE;
        }
        Field.push_back(temp);
    }

    //place walls
    i = BinToInt(InputArray,counter);
    counter+=4;
    for(;i>0;i-=2){
        unsigned int TempX,TempY;
        TempX= BinToInt(InputArray,counter);
        counter+=4;
        TempY= BinToInt(InputArray,counter);
        counter+=4;
        Field[TempX][TempY]= WALL;
    }

    //field ground where we can walk with EMPTY
    std::stack<std::pair<unsigned int,unsigned int>> dfs;
    dfs.push({PosX,PosY});
    while(dfs.size()){
        std::pair<unsigned int,unsigned int> Current = dfs.top();
        dfs.pop();
        Field[Current.first][Current.second] = EMPTY;
        if(Field[Current.first + 1][Current.second] == OUTSIDE) dfs.push({Current.first + 1, Current.second});
        if(Field[Current.first][Current.second + 1] == OUTSIDE) dfs.push({Current.first, Current.second + 1});
        if(Field[Current.first - 1][Current.second] == OUTSIDE) dfs.push({Current.first - 1, Current.second});
        if(Field[Current.first][Current.second - 1] == OUTSIDE) dfs.push({Current.first, Current.second - 1});
    }

    //place boxes
    i = BinToInt(InputArray,counter);
    counter+=4;
    BoxNumber = i/2;
    for(;i>0;i-=2){
        unsigned int TempX,TempY;
        TempX = BinToInt(InputArray,counter);
        counter+=4;
        TempY = BinToInt(InputArray,counter);
        counter+=4;
        Field[TempX][TempY]= BOX;
    }

    //place points
    i = BinToInt(InputArray,counter);
    counter+=4;
    for(;i>0;i-=2){
        unsigned int TempX,TempY;
        TempX = BinToInt(InputArray,counter);
        counter+=4;
        TempY = BinToInt(InputArray,counter);
        counter+=4;
        if(Field[TempX][TempY] != BOX) Field[TempX][TempY]= POINT;
        else {Field[TempX][TempY]= BOX_ON_POINT; BoxOnPointNumber++;}
    }

    /* MATRIX CHECK
    std::ofstream check("check.txt");
    i = 0;
    for(;i<SizeX;i++){
        for(unsigned int j = 0;j<SizeY;j++){
            check << Field[i][j]<<" ";
        }
        check<<'\n';
    }
    check.close();
    */
    success = true;
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

unsigned int LevelHandler::GetPosX(){
    return PosX;
}

unsigned int LevelHandler::GetPosY(){
    return PosY;
}
