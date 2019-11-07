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
    QFile file(":/levels/" + file_name);
    file.open(QIODevice::ReadOnly);
    if (file.size() == 0){
        success = false;
        return;
    }
    QByteArray blob = file.readAll();
    unsigned int counter = 0;
    unsigned int i =0;
    SizeX = BinToInt(blob,counter);
    counter+=4;
    SizeY= BinToInt(blob,counter);
    counter+=4;
    Field = new char*[SizeX];
    for (;i<SizeX;i++){
        Field[i] = new char[SizeY];
        for (unsigned int j =0;j<SizeY;j++){
            Field[i][j] = 'o';
        }
    }

    i = BinToInt(blob,counter);
    counter+=4;
    for(;i>0;i-=2){
        unsigned int tx,ty;
        tx= BinToInt(blob,counter);
        counter+=4;
        ty= BinToInt(blob,counter);
        counter+=4;
        Field[tx][ty]= 'w';
    }

    i = BinToInt(blob,counter);
    counter+=4;
    for(;i>0;i-=2){
        unsigned int tx,ty;
        tx = BinToInt(blob,counter);
        counter+=4;
        ty = BinToInt(blob,counter);
        counter+=4;
        Field[tx][ty]= 'b';
    }

    i = BinToInt(blob,counter);
    counter+=4;
    for(;i>0;i-=2){
        unsigned int tx,ty;
        tx = BinToInt(blob,counter);
        counter+=4;
        ty = BinToInt(blob,counter);
        counter+=4;
        if(Field[tx][ty] != 'b') Field[tx][ty]= 'p';
        else Field[tx][ty]= 'u';
    }

    PosX = BinToInt(blob,counter);
    counter+=4;
    PosY = BinToInt(blob,counter);
    counter+=4;

    success = true;
}
