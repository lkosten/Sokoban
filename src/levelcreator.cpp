#include "levelcreator.h"

int LevelCreator::windowX = 100;
int LevelCreator::windowY = 100;

void LevelCreator::MouseClicked(int x, int y){
    int IndX = static_cast<int>((static_cast<size_t>(x) - CreatorDrawer::FieldX)/(CreatorDrawer::FieldWidth / CreatorMap::SizeX));
    int IndY = static_cast<int>((static_cast<size_t>(y) - CreatorDrawer::FieldY)/(CreatorDrawer::FieldHeight / CreatorMap::SizeY));
    if (IndX >= 0 && IndX < static_cast<int>(CreatorMap::SizeX) && IndY >= 0 && IndY < static_cast<int>(CreatorMap::SizeY)){
        CreatorBrush::SetGate(static_cast<unsigned int>(IndX), static_cast<unsigned int>(IndY));
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
