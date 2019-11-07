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

e - empty
o - outside
w - wall
b - box
p - point
u - box + point
*/

LevelHandler::LevelHandler(){}

LevelHandler::LevelHandler(const QString& file_name){
   this->read(file_name);
}

void LevelHandler::read(const  QString& file_name){
    QFile file(":/levels/testlevel.bin");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    if (file.size() == 0){
        success = false;
        return;
    }
    QByteArray blob = file.readAll();
    int i =0;
    in >> SizeX;
    in >> SizeY;
    Field = new char*[SizeX];
    for (;i<SizeX;i++){
        Field[i] = new char[SizeY];
        for (int j =0;j<SizeY;j++){
            Field[i][j] = 'o';
        }
    }

    in >> i;
    i*=2;
    for(;i>=0;i--){
        int tx,ty;
        in >> tx;
        in >> ty;
        Field[tx][ty]= 'w';
    }

    in >> i;
    i*=2;
    for(;i>=0;i--){
        int tx,ty;
        in >> tx;
        in >> ty;
        Field[tx][ty]= 'b';
    }

    in >> i;
    i*=2;
    for(;i>=0;i--){
        int tx,ty;
        in >> tx;
        in >> ty;
        if(Field[tx][ty] != 'b') Field[tx][ty]= 'p';
        else Field[tx][ty]= 'u';
    }

    in >> PosX;
    in >> PosY;

    success = true;
}
