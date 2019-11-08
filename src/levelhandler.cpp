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


LevelHandler::LevelHandler(const QString& file_name){
   this->read(file_name);
}

void LevelHandler::read(const  QString& file_name){
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

    PosX = BinToInt(InputArray,counter);
    counter+=4;
    PosY = BinToInt(InputArray,counter);
    counter+=4;

    Field = new char*[SizeX];
    for (;i<SizeX;i++){
        Field[i] = new char[SizeY];
        for (unsigned int j =0;j<SizeY;j++){
            Field[i][j] = OUTSIDE;
        }
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

    //field ground where we can walk with empty
    std::stack<std::pair<int,int>> dfs;
    dfs.push({PosX,PosY});
    while(dfs.size()){
        std::pair<int,int> Current = dfs.top();
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
        else Field[TempX][TempY]= BOX_ON_POINT;
    }

    std::ofstream check("check.txt");
    i = 0;
    for(;i<SizeX;i++){
        for(unsigned int j = 0;j<SizeY;j++){
            check << Field[i][j]<<" ";
        }
        check<<'\n';
    }
    check.close();
    success = true;
}

void LevelHandler::GetField(char **RetField, unsigned int& X, unsigned int& Y){
    GetSize(X,Y);
    RetField = new char*[X];
    for (unsigned int i = 0; i < X; i++){
        RetField[i] = new char[Y];
        for (unsigned int j =0; j < Y; j++){
            RetField[i][j] = Field[i][j];
        }
    }
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

LevelHandler::~LevelHandler(){}
