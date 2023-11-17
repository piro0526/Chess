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
    Piece(Color color) : _color(color){};
    bool canMakeMove(Board board, Move move) const;
    void addMoveValidator(MoveValidator MoveValidator);
    bool isAllyPiece(Piece piece);
    void gotMoved();
    std::string getSymbol() const;
};

class Pawn : public Piece
{
private:

public:
    Pawn(Color color) : Piece(color){};
};


class Rook : public Piece
{
private:

public:
    Rook(Color color) : Piece(color){};
};

class Knight : public Piece
{
private:

public:
    Knight(Color color) : Piece(color){};
};

class Bishop : public Piece
{
private:

public:
    Bishop(Color color) : Piece(color){};
};

class Queen : public Piece
{
private:

public:
    Queen(Color color) : Piece(color){};
};

class King : public Piece
{
private:

public:
    King(Color color) : Piece(color){};
};
