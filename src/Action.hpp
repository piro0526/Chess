#pragma once
#include "Move.hpp"
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <algorithm>


class Action{
protected:
    Move move_;
    std::string piece_type_;
    std::string saction_;
public:
    Action(Move move, std::string piece_type):move_(move),piece_type_(piece_type){};
    void set_move(Move move){move_=move;};
    void set_piece_type(std::string piece_type){piece_type_=piece_type;};
    std::string get_piece_type(){return piece_type_;};
    Move get_move(){return move_;};
    void set_saction(std::string saction){saction_=saction;};
    std::string get_saction(){return saction_;};
};