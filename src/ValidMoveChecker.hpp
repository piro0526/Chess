#pragma once
#include "PieceMetadata.hpp"
#include "StateChecker.hpp"
#include "Interface.hpp"
#include "MoveHandler.hpp"
#include "GameStateCheck.hpp"
#include "Interpreter.hpp"
#include "Action.hpp"
#include <vector>
#include <iostream>
#include <map>

class ValidMoveChecker
{
protected:
    Board *board_;
    PieceMetadata metadata_;
    std::unique_ptr<IMoveHandler> move_handler_;
    std::unique_ptr<GameStateChecker> state_checker_;
public:
    ValidMoveChecker(Board *board);
    int IsValidMove(Action);
};