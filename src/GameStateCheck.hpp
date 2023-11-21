#pragma once
#include "PieceMetadata.hpp"
#include "StateChecker.hpp"



class GameStateCheck
{
public:
    virtual StateInfo getState(PieceMetadata metadata, Color color) = 0;
    virtual bool isIllegalForCurrentPlayer() = 0;
};

class CheckState : public GameStateCheck
{
private:
    
public:
    StateInfo getState(PieceMetadata metadata, Color color);
    bool isIllegalForCurrentPlayer();
};

class CheckMateState : public GameStateCheck
{
private:
    
public:
    StateInfo getState(PieceMetadata metadata, Color color);
    bool isIllegalForCurrentPlayer();
};

class StaleMateState : public GameStateCheck
{
private:
    
public:
    StateInfo getState(PieceMetadata metadata, Color color);
    bool isIllegalForCurrentPlayer();
};