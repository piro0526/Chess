#pragma once
#include "Move.hpp"

typedef int File;
typedef int Rank;

class Spot
{
private:
    Rank _rank;
    File _file;
public:
    Spot();
    Spot(Rank rank, File file);
    void setRank(Rank rank);
    void setFile(File file);
    Rank getRank();
    File getFile();
};