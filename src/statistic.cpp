#include "statistic.h"


unsigned int Stat::moves = 0;
unsigned int Stat::pushedBoxes = 0;
std::vector<size_t> Stat::score;
const std::string Stat::scoreFileDir = ":/statistics.bin";

void Stat::reset(){
    moves = 0;
    pushedBoxes = 0;
}
void Stat::move(){
    moves++;
}
void Stat::push(){
    moves++;
    pushedBoxes++;
}
unsigned int Stat::getMoves(){
    return moves;
}
unsigned int Stat::getPushes(){
    return pushedBoxes;
}

void Stat::read()
{
    score.clear();

    QFile file(scoreFileDir.c_str());

    file.open(QIODevice::ReadOnly);
    if (file.size() == 0)
    {
        return;
    }

    QByteArray InputArray = file.readAll();
    QDataStream Input(InputArray);

    size_t listSize = BinToInt(Input);

    score.resize(listSize);
    for (auto &i : score)
    {
        i = BinToInt(Input);
    }
}

void Stat::write()
{
    FILE* output;
    output = fopen(scoreFileDir.c_str(), "wb");

    int temp = static_cast<int>(score.size());
    fwrite(&temp, sizeof(int), 1, output);

    for (const auto &i : score)
    {
        fwrite(&i, sizeof(int), 1, output);
    }

    fclose(output);
}
