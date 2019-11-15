#include "levelcreator.h"

int LevelCreator::windowX = 100;
int LevelCreator::windowY = 100;

void LevelCreator::MouseClicked(int x, int y){
    size_t FieldMaxSize;
    if(CreatorDrawer::FieldWidth > CreatorDrawer::FieldHeight) FieldMaxSize = CreatorDrawer::FieldWidth;
            else FieldMaxSize = CreatorDrawer::FieldHeight;

    size_t MatrxMaxSize;
    if(CreatorMap::SizeX > CreatorMap::SizeY) MatrxMaxSize = CreatorMap::SizeX;
            else MatrxMaxSize = CreatorMap::SizeY;

    int IndX = static_cast<int>((static_cast<size_t>(x) - CreatorDrawer::FieldX)/
                                (FieldMaxSize / MatrxMaxSize));
    int IndY = static_cast<int>((static_cast<size_t>(y) - CreatorDrawer::FieldY)/
                                (FieldMaxSize / MatrxMaxSize));


    if (IndX >= 0 && IndX < static_cast<int>(CreatorMap::SizeX) && IndY >= 0 && IndY < static_cast<int>(CreatorMap::SizeY)){
        CreatorBrush::SetGate(static_cast<unsigned int>(IndX), static_cast<unsigned int>(IndY));
    }


    if(static_cast<unsigned int>(x) >= CreatorDrawer::XresizeX - 75 && static_cast<unsigned int>(x) < CreatorDrawer::XresizeX - 25
            && static_cast<unsigned int>(y) >= CreatorDrawer::XresizeY && static_cast<unsigned int>(y) <= CreatorDrawer::XresizeY + 50){
        CreatorMap::SetSize(CreatorMap::SizeX - 1, CreatorMap::SizeY);
    }

    if(static_cast<unsigned int>(x) >= CreatorDrawer::XresizeX + 25 && static_cast<unsigned int>(x) < CreatorDrawer::XresizeX + 75
            && static_cast<unsigned int>(y) >= CreatorDrawer::XresizeY && static_cast<unsigned int>(y) <= CreatorDrawer::XresizeY + 50){
        CreatorMap::SetSize(CreatorMap::SizeX + 1, CreatorMap::SizeY);

    }

    if(static_cast<unsigned int>(x) >= CreatorDrawer::YresizeX && static_cast<unsigned int>(x) <= CreatorDrawer::YresizeX + 50
            && static_cast<unsigned int>(y) >= CreatorDrawer::YresizeY - 75 && static_cast<unsigned int>(y) <= CreatorDrawer::YresizeY - 25){
        CreatorMap::SetSize(CreatorMap::SizeX, CreatorMap::SizeY + 1);

    }

    if(static_cast<unsigned int>(x) >= CreatorDrawer::YresizeX && static_cast<unsigned int>(x) <= CreatorDrawer::YresizeX + 50
            && static_cast<unsigned int>(y) >= CreatorDrawer::YresizeY + 25 && static_cast<unsigned int>(y) <= CreatorDrawer::YresizeY + 75){
        CreatorMap::SetSize(CreatorMap::SizeX, CreatorMap::SizeY - 1);

    }

}
void LevelCreator::KeyUp(){
    CreatorBrush::ChangeTool(true);
}
void LevelCreator::KeyDown(){
    CreatorBrush::ChangeTool(false);
}
void LevelCreator::Write(QString name){
}
void LevelCreator::initMap(){
    CreatorMap::SetSize(10,10);
}
