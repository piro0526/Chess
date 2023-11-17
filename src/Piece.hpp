#pragma once
#include "Board.hpp"
#include "MoveValidator.hpp"

typedef int Color;
static const Color BLACK = -1;
static const Color WHITE = 1;

class Piece
{
protected:
    std::string _symbol;
    Color _color;
    std::vector<MoveValidator> _moveVaridators;
    int _movedAmount;
public:
    Piece();
    bool canMakeMove(Board board, Move move) const;
    void addMoveValidator(MoveValidator MoveValidator);
    bool isAllyPiece(Piece piece);
    void gotMoved();
    std::string getSymbol() const;
};

class Pawn : Piece
{
private:

public:
    Pawn(Color color);
};


class Rook : Piece
{
private:

public:
    Rook(Color color);
};

class Knight : Piece
{
private:

public:
    Knight(Color color);
};

class Bishop : Piece
{
private:

public:
    Bishop(Color color);
};

class Queen : Piece
{
private:

public:
    Queen(Color color);
};

class King : Piece
{
private:

public:
    King(Color color);
};
