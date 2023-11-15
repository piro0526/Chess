#pragma once


class MoveValidator
{
private:

public:
    virtual bool isMoveValid(Board board);
};

class DiagonalMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board);
};

class HorizonalMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board);
};

class VerticalMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board);
};

class PawnMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board);
};

class KightMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board);
};

class SingleMoveValidator : MoveValidator
{
public:
    bool isMoveValid(Board board);
};