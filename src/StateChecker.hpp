#pragma once
#include "GameStateCheck.hpp"
#include <vector>

class AbstructStateChecker
{
private:
    ChessGame _chessGame;
public:
    virtual StateInfo checkState(Color color) const;
    virtual Stateinfo checkIllegalStates(Color color) const;
};

class GameStateChecker : AbstructStateChecker
{
private:
    std::vector<GameStateCheck> _checks;
public:
    StateInfo checkState(Color color) const;
    Stateinfo checkIllegalStates(Color color) const;
    void addGameStateCheck(GameStateCheck);
};