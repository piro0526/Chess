#pragma once
#include "Spot.hpp"

class Move
{
private:
    Spot _startSpot, _endSpot;
public:
    Move() : Move(Spot(), Spot()){};
    Move(Spot s, Spot e) : _startSpot(s),_endSpot(e){};
    void setStart(Spot startSpot);
    void setEnd(Spot endSpot);
    Spot getStart();
    Spot getEnd();
};