#pragma once

class GameStateCheck
{
public:
    virtual StateInfo getState(ChessGame chessGame, Color color) = 0;
    virtual bool isIllegalForCurrentPlayer() = 0;
};