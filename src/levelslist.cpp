#include "levelslist.h"

unsigned int LevelsList::selectedLevel = 0;
unsigned int LevelsList::minPrintedLevel = 0;
unsigned int LevelsList::maxPrintedLevel = 6;

std::vector<QString> LevelsList::List = std::vector<QString>();

void LevelsList::GetList(){
    QDirIterator it(":/levels/", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString tempstr = it.next();
        List.push_back(tempstr);
    }
}

QString LevelsList::GetFDirectory(unsigned int n){
    if(static_cast<unsigned int>(n) >= List.size())return nullptr;
    return List[n];
}

QString LevelsList::GetFName(unsigned int n){
    if(static_cast<unsigned int>(n) >= List.size())return nullptr;

    const QString BIN = ".bin";
    int FirstChar = List[n].lastIndexOf('/') + 1;
    int LastChar = List[n].lastIndexOf(BIN);
    return List[n].mid(FirstChar, LastChar - FirstChar);
}

std::pair<QString,QString> LevelsList::GetFNameDir(unsigned int n){
    std::pair<QString,QString> Ret;
    Ret.first = GetFName(n);
    Ret.second = GetFDirectory(n);
    return Ret;
}

unsigned int LevelsList::GetNumber(){
    return static_cast<unsigned int>(List.size());
}
