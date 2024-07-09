#include "Move.hpp"

void Move::set_start(Spot start_spot)
{
    start_spot_ = start_spot;
};

void Move::set_end(Spot end_spot)
{
    end_spot_ = end_spot;
};

Spot Move::get_start()
{
    return start_spot_;
};

Spot Move::get_end()
{
    return end_spot_;
};
