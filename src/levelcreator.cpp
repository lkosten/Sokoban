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
    if(CreatorMap::PointCounter!= CreatorMap::BoxCounter) return;
    std::stack<std::pair<unsigned int,unsigned int>> dfs;
    dfs.push({ CreatorMap::PosX, CreatorMap::PosY});
    std::vector<bool> TmpVec;
    TmpVec.resize(CreatorMap::SizeY,false);
    std::vector<std::vector<bool>> used;
    used.resize(CreatorMap::SizeX, TmpVec);
    used[CreatorMap::PosX][CreatorMap::PosY] = true;
    unsigned int foundBoxes = 0;
    unsigned int foundPoints = 0;
    while(dfs.size()){
        std::pair<unsigned int,unsigned int> Current = dfs.top();
        dfs.pop();
        if(CreatorMap::Field[Current.first][Current.second]== CreatorMap::BOX){
            foundBoxes++;
        }
        if(CreatorMap::Field[Current.first][Current.second]== CreatorMap::POINT){
            foundPoints++;
        }
        if(CreatorMap::Field[Current.first][Current.second]== CreatorMap::BOX_ON_POINT){
            foundBoxes++;
            foundPoints++;
        }
        if(CreatorMap::Field[Current.first][Current.second]!= CreatorMap::WALL){
            if(Current.first == 0 || Current.first == CreatorMap::SizeX - 1) {
                TmpVec.clear();
                used.clear();
                return;
            }
            if(Current.first == 0 || Current.first == CreatorMap::SizeY - 1) {
                TmpVec.clear();
                used.clear();
                return;
            }

            if(!used[Current.first + 1][Current.second]){
            dfs.push({Current.first + 1, Current.second});
            used[Current.first + 1][Current.second] = true;
            }
            if(!used[Current.first][Current.second + 1]){
            dfs.push({Current.first, Current.second + 1});
            used[Current.first][Current.second + 1] = true;
            }
            if(!used[Current.first - 1][Current.second]){
            dfs.push({Current.first - 1, Current.second});
            used[Current.first - 1][Current.second] = true;
            }
            if(!used[Current.first][Current.second - 1]){
            dfs.push({Current.first, Current.second - 1});
            used[Current.first][Current.second - 1] = true;
            }
        }
    }
    if(foundBoxes != CreatorMap::BoxCounter || foundPoints != CreatorMap::PointCounter) {
        TmpVec.clear();
        used.clear();
        return;
    }

    TmpVec.clear();
    used.clear();

    FILE* ifile;
    ifile = fopen("testgood.bin", "wb");

    size_t temp = CreatorMap::SizeX + 2;
    fwrite(&temp, sizeof(int), 1, ifile);

    temp = CreatorMap::SizeY + 2;
    fwrite(&temp, sizeof(int), 1, ifile);

    temp = CreatorMap::PosX + 1;
    fwrite(&temp, sizeof(int), 1, ifile);

    temp = CreatorMap::PosY + 1;
    fwrite(&temp, sizeof(int), 1, ifile);

    std::stack<size_t> walls;
    std::stack<size_t> boxes;
    std::stack<size_t> points;
    for (size_t i = 0; i < CreatorMap::SizeY; i++) {
        for (size_t j = 0; j < CreatorMap::SizeX; j++) {
            if (CreatorMap::Field[j][i] == 'w') {
                walls.push(i);
                walls.push(j);
            }
            if (CreatorMap::Field[j][i] == 'b') {
                boxes.push(i);
                boxes.push(j);

            }
            if (CreatorMap::Field[j][i] == 'p') {
                points.push(i);
                points.push(j);
            }
            if (CreatorMap::Field[j][i] == 'u') {
                boxes.push(i);
                boxes.push(j);
                points.push(i);
                points.push(j);
            }
        }
    }
    temp = walls.size();
    fwrite(&temp, sizeof(int), 1, ifile);
    while (walls.size()) {
        temp = walls.top() + 1;
        fwrite(&temp, sizeof(int), 1, ifile);
        walls.pop();
    }
    temp = boxes.size();
    fwrite(&temp, sizeof(int), 1, ifile);
    while (boxes.size()) {
        temp = boxes.top() + 1;
        fwrite(&temp, sizeof(int), 1, ifile);
        boxes.pop();
    }

    temp = points.size();
    fwrite(&temp, sizeof(int), 1, ifile);
    while (points.size()) {
        temp = points.top() + 1;
        fwrite(&temp, sizeof(int), 1, ifile);
        points.pop();
    }
    fclose(ifile);
}
void LevelCreator::initMap(){
    CreatorMap::SetSize(10,10);
}
void LevelCreator::clear(){
    CreatorBrush::currentTool = T_RUBBER;
    CreatorMap::Field.clear();
}
