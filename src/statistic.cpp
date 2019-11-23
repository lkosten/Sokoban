#include "statistic.h"


unsigned int Stat::moves = 0;
unsigned int Stat::pushedBoxes = 0;
std::vector<int> Stat::score;
const std::string Stat::scoreFileDir = "statistics.bin";

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

    std::ifstream statInput;
    statInput.open(scoreFileDir, std::ios::binary);
    if (!statInput.is_open())
        return;


    int listSize = 0;

    statInput.read((char*)&listSize, sizeof(listSize));

    score.resize(static_cast<size_t>(listSize));
    for (auto &i : score)
    {
        statInput.read((char*)&i, sizeof (i));
    }
    statInput.close();
}

void Stat::write()
{
    std::ofstream statOutput(scoreFileDir, std::ios::binary);
    if (!statOutput.is_open())
        return;

    int temp = static_cast<int>(score.size());
    statOutput.write((char*)&temp, sizeof(temp));

    for (const auto &i : score)
    {
        statOutput.write((char*)&i, sizeof(i));
    }

    statOutput.close();
}

void Stat::updScore(size_t levelNum)
{
    int updValue = static_cast<int>(moves + 5 * pushedBoxes);

    if (score[levelNum] == 0) score[levelNum] = updValue;
    score[levelNum] = std::min(score[levelNum], updValue);
}
