#pragma once
#include "Board.hpp"
#include "StateChecker.hpp"
#include "Action.hpp"
#include <string>

class Interpreter{
public:
    std::string ToInterface(Board&, StateInfo) const;
    Action ToGame(std::string);
    std::string FEN(Board&) const;
};