#pragma once
#include "Spot.hpp"

class Move
{
private:
    Spot _startSpot, _endSpot;
public:
    void setStart(Spot startSpot);
    void setEnd(Spot endSpot);
    Spot getStart();
    Spot getEnd();
};