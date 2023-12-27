#pragma once

typedef int File;
typedef int Rank;

class Spot
{
private:
    Rank _rank;
    File _file;
public:
    Spot(){Spot(0, 0);};
    Spot(Rank rank, File file) : _rank(rank), _file(file){};
    void setRank(Rank rank){_rank = rank;};
    void setFile(File file){_file = file;};
    Rank getRank(){return _rank;};
    File getFile(){return _file;};
};