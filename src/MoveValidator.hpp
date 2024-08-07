#pragma once
#include <cstdlib>
#include <memory>

class Board;
class Move;

class MoveValidator
{
public:
    virtual bool IsMoveValid(Board& board, Move move) const;
};

class DiagonalMoveValidator : public MoveValidator
{
public:
    bool IsMoveValid(Board& board, Move move) const;
};

class HorizonalMoveValidator : public MoveValidator
{
public:
    bool IsMoveValid(Board& board, Move move) const;
};

class VerticalMoveValidator : public MoveValidator
{
public:
    bool IsMoveValid(Board& board, Move move) const;
};

class PawnMoveValidator : public MoveValidator
{
public:
    bool IsMoveValid(Board& board, Move move) const;
};

class KightMoveValidator : public MoveValidator
{
public:
    bool IsMoveValid(Board& board, Move move) const;
};

class SingleMoveValidator : public MoveValidator
{
public:
    bool IsMoveValid(Board& board, Move move) const;
};