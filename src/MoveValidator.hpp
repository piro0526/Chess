#pragma once
#include <cstdlib>

class Board;

class MoveValidator
{
private:

public:
    virtual bool isMoveValid(Board& board, Move move) const;
};

class DiagonalMoveValidator : public MoveValidator
{
public:
    bool isMoveValid(Board& board, Move move) const;
};

class HorizonalMoveValidator : public MoveValidator
{
public:
    bool isMoveValid(Board& board, Move move) const;
};

class VerticalMoveValidator : public MoveValidator
{
public:
    bool isMoveValid(Board& board, Move move) const;
};

class PawnMoveValidator : public MoveValidator
{
public:
    bool isMoveValid(Board& board, Move move) const;
};

class KightMoveValidator : public MoveValidator
{
public:
    bool isMoveValid(Board& board, Move move) const;
};

class SingleMoveValidator : public MoveValidator
{
public:
    bool isMoveValid(Board& board, Move move) const;
};