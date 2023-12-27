#pragma once
#include "PieceMetadata.hpp"
#include "StateChecker.hpp"
#include "Player.hpp"
#include "MoveHandler.hpp"
#include "GameStateCheck.hpp"
#include <vector>
#include <iostream>


class ChessGame
{
private:
    std::shared_ptr<Player> _whitePlayer, _blackPlayer;
    Board _board;
    PieceMetadata _metadata;
    std::unique_ptr<IMoveHandler> _moveHandler;
    std::unique_ptr<GameStateChecker> _stateChecker;
    std::vector<std::shared_ptr<GameStateCheck>> _checks;
    int _turns;
public:
    ChessGame();
    ChessGame(std::unique_ptr<Player> whitePlayer, std::unique_ptr<Player> _blackPlayer);
    void init();
    void playTurn(std::shared_ptr<Player> player);
    Move getPlayerInput(std::shared_ptr<Player> player);
    Spot parseCoordinates(std::string strCoodinates);
    void undo(Move move, std::shared_ptr<Piece> startPiece, std::shared_ptr<Piece> endPiece);
    void start();
    std::shared_ptr<Player> swapPlayer(std::shared_ptr<Player> player);
};