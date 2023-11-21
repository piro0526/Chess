#pragma once
#include "PieceMetadata.hpp"
#include "Player.hpp"
#include <vector>

class StateInfo
{
private:
    int _stateCode;
    std::string _stateMessage;
public:
    StateInfo(int stateCode, std::string stateMessage) : _stateCode(stateCode), _stateMessage(stateMessage){};
};


class ChessGame
{
private:
    Player _whitePlayer, _blackPlayer;
    Board _board;
    PieceMetadata _metadata;
    IMoveHandler _moveHandler:
    AbstructStateChecker _stateChecker;
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
    Player swapPlayer(Player player);
};