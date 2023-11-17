#pragma once


class MoveValidator
{
private:

public:
    virtual bool isMoveValid(Board board, Move move) const;
};

class DiagonalMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board, Move move) const;
};

class HorizonalMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board, Move move) const;
};

class VerticalMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board, Move move) const;
};

class PawnMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board, Move move) const;
};

class KightMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board, Move move) const;
};

class SingleMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board, Move move) const;
};