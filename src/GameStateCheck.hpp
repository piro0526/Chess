#pragma once
#include "PieceMetadata.hpp"

class StateChecker;
class StateInfo;

class GameStateCheck
{
public:
    GameStateCheck(){};
    virtual ~GameStateCheck(){};
    virtual StateInfo get_state(Board& board, PieceMetadata& metadata, Color color) = 0;
    virtual bool IsIllegalForCurrentPlayer() = 0;

};

class CheckState : public GameStateCheck
{
public:
    StateInfo get_state(Board& board, PieceMetadata& metadata, Color color);
    bool IsIllegalForCurrentPlayer();
};

class CheckMateState : public GameStateCheck
{
public:
    StateInfo get_state(Board& board, PieceMetadata& metadata, Color color);
    bool IsIllegalForCurrentPlayer();
};

class StaleMateState : public GameStateCheck
{
public:
    StateInfo get_state(Board& board, PieceMetadata& metadata, Color color);
    bool IsIllegalForCurrentPlayer();
};