#pragma once
#include "PieceMetadata.hpp"
#include "StateChecker.hpp"
#include "Player.hpp"
#include "Movehandler.hpp"
#include "GameStateCheck.hpp"
#include <vector>


class ChessGame
{
private:
    Player _whitePlayer, _blackPlayer;
    Board _board;
    PieceMetadata _metadata;
    std::unique_ptr<IMoveHandler> _moveHandler;
    std::unique_ptr<GameStateChecker> _stateChecker;
    std::vector<std::shared_ptr<GameStateCheck>> _checks;
    int _turns;
public:
    ChessGame();
    ChessGame(Player whitePlayer, Player _blackPlayer);
    void init();
    void playTurn(Player player);
    Move getPlayerInput(Player player);
    Spot parseCoordinates(std::string strCoodinates);
    void undo();
    void start();
    Player swapPlayer(Player player);
};