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

LevelHandler::LevelHandler(const char* file_name){
   this->read(file_name);
}

void LevelHandler::read(const char* file_name){
    FILE *input = std::fopen(file_name, "rb");
    if (input == NULL){
        success = false;
        return;
    }

    int i =0;
    fread(&SizeX, sizeof(int), 1, input);
    fread(&SizeY, sizeof(int), 1, input);
    for (;i<SizeX;i++){
        for (int j =0;j<SizeY;j++){
            Field[i][j] = 'o';
        }
    }

    fread(&i, sizeof(int), 1, input);
    i*=2;
    for(;i>=0;i--){
        int tx,ty;
        fread(&tx, sizeof(int), 1, input);
        fread(&ty, sizeof(int), 1, input);
        Field[tx][ty]= 'w';
    }

    fread(&i, sizeof(int), 1, input);
    i*=2;
    for(;i>=0;i--){
        int tx,ty;
        fread(&tx, sizeof(int), 1, input);
        fread(&ty, sizeof(int), 1, input);
        Field[tx][ty]= 'b';
    }

    fread(&i, sizeof(int), 1, input);
    i*=2;
    for(;i>=0;i--){
        int tx,ty;
        fread(&tx, sizeof(int), 1, input);
        fread(&ty, sizeof(int), 1, input);
        if(Field[tx][ty] != 'b') Field[tx][ty]= 'p';
        else Field[tx][ty]= 'u';
    }

    fread(&PosX, sizeof(int), 1, input);
    fread(&PosY, sizeof(int), 1, input);

    success = true;
}
