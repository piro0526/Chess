#pragma once
#include "PieceMetadata.hpp"
#include "StateChecker.hpp"
#include "Interface.hpp"
#include "MoveHandler.hpp"
#include "GameStateCheck.hpp"
#include "Interpreter.hpp"
#include "Action.hpp"
#include "ValidMoveChecker.hpp"
#include <vector>
#include <iostream>
#include <map>


class ChessGame
{
protected:
    std::shared_ptr<Interface> white_interface_, black_interface_;
    Board board_;
    std::shared_ptr<ValidMoveChecker> valid_move_checker_;
    Interpreter interpreter_;
    PieceMetadata metadata_;
    std::unique_ptr<IMoveHandler> move_handler_;
    std::unique_ptr<GameStateChecker> state_checker_;
    std::vector<std::array<std::string, 3> > hist_;
    int turns_[2];
public:
    ChessGame();
    ChessGame(const std::shared_ptr<Interface>&, const std::shared_ptr<Interface>&);
    void Init();
    bool PlayTurn(const std::shared_ptr<Interface>&, StateInfo);
    void Undo(Move move, const std::shared_ptr<Piece>&, const std::shared_ptr<Piece>&);
    void Start();
    std::shared_ptr<Interface> SwapInterface(const std::shared_ptr<Interface>&);
};