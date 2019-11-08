#include "levelslist.h"

LevelsList::LevelsList(){
    QDirIterator it(":/levels/",QDirIterator::Subdirectories);
    std::stack<QString> input;
    while (it.hasNext()) {
        input.push(it.next());
    }

    List = new QString[input.size()];
    Number = (int)input.size();

    int i =0;
    while(input.size()){
        List[i] = input.top();
        input.pop();
        i++;
    }
}

QString LevelsList::GetFDirectory(int n){
    if(n > Number)return NULL;
    return List[n];
}

QString LevelsList::GetFName(int n){
    if(n > Number)return NULL;

    const QString BIN = ".bin";
    QString Name;
    return List[n];
}

int LevelsList::GetNumber(){
    return Number;
}
