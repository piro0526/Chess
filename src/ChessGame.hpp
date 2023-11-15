#pragma once
#include "PieceMetadata.hpp"
#include <vector>

class StateInfo
{
private:
    int _stateCode;
    std::string _stateMessage;
public:
    
};


class ChessGame
{
private:
    Player _whitePlayer, _blackPlayer;
    Board _board;
    PieceMetaData _metadata;
    IMoveHandler _moveHandler:
    AbstructStateChecker _stateChecker;
    std::vector<>
public:
    void init();
    Move playTurn(Player player);
    Move getPlayerInput(Player player);
    Spot parseCoordinates(std::string strCoodinates);
    void undo();
    Player swapPlayer(Player cuurentPlayer);
};