#pragma once
#include "Spot.hpp"

class Move
{
private:
    Spot _startSpot, _endSpot;
public:
    Move() : Move(Spot(), Spot()){};
    Move(Spot s, Spot e) : _startSpot(s),_endSpot(e){};
    void setStart(Spot startSpot){_startSpot=startSpot;};
    void setEnd(Spot endSpot){_endSpot=endSpot;};
    Spot getStart(){return _startSpot;};
    Spot getEnd(){return _endSpot;};
};