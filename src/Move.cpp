#include "Move.hpp"

void Move::setStart(Spot startSpot)
{
    _startSpot = startSpot;
};

void Move::setEnd(Spot endSpot)
{
    _endSpot = endSpot; 
};

Spot Move::getStart()
{
    return _startSpot;
};

Spot Move::getEnd()
{
    return _endSpot;
};
