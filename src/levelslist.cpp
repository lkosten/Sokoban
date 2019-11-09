#include "levelslist.h"

LevelsList::LevelsList(){
    QDirIterator it(":/levels/", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        List.push_back(it.next());
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
