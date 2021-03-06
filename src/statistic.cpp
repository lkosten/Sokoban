#include "statistic.h"

unsigned int Stat::selectedLevel    = 0;
unsigned int Stat::minPrintedLevel  = 0;
unsigned int Stat::maxPrintedLevel  = 6;

unsigned int Stat::moves       = 0;
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
    {
        std::ofstream temp(scoreFileDir, std::ios::binary);
        temp.close();

        statInput.open(scoreFileDir, std::ios::binary);
    }



    int listSize = 0;

    statInput.read((char*)&listSize, sizeof(listSize));

    if (listSize != 0)
    {
        score.resize(static_cast<size_t>(listSize));
        for (auto &i : score)
        {
            statInput.read((char*)&i, sizeof (i));
        }
    }
    else
    {
        listSize = static_cast<int>(LevelsList::GetNumber());

        score.resize(static_cast<size_t>(listSize));
        for (auto &i : score)
        {
            i = 0;
        }
    }

    statInput.close();
}

void Stat::write()
{
    std::ofstream statOutput(scoreFileDir, std::ios::binary);
    if (!statOutput.is_open())
    {
        return;
    }


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

unsigned int Stat::GetNumber()
{
    return static_cast<unsigned int>(score.size());
}

int Stat::GetStat(size_t levelNum)
{
    return score[levelNum];
}

void Stat::addLevel()
{
    score.push_back(0);
}
