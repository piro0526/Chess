#pragma once
#include "Spot.hpp"

class Move
{
protected:
    Spot start_spot_, end_spot_;
public:
    Move() : start_spot_(Spot()),end_spot_(Spot()){};
    Move(Spot s, Spot e) : start_spot_(s),end_spot_(e){};
    void set_start(Spot start_spot);
    void set_end(Spot end_spot);
    Spot get_start();
    Spot get_end();
};