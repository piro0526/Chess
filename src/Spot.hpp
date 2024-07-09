#pragma once

typedef int File;
typedef int Rank;

class Spot
{
protected:
    Rank rank_;
    File file_;
public:
    Spot(){Spot(0, 0);};
    Spot(Rank rank, File file) : rank_(rank), file_(file){};
    void set_rank(Rank rank){rank_ = rank;};
    void set_file(File file){file_ = file;};
    Rank get_rank(){return rank_;};
    File get_file(){return file_;};
};