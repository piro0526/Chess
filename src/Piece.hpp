#pragma once
#include "Move.hpp"
#include <memory>
#include <string>
#include <vector>

typedef int Color;
static const Color BLACK = -1;
static const Color WHITE = 1;

class Board;
class MoveValidator;

class Piece
{
protected:
    std::string _symbol;
    Color _color;
    std::vector<std::shared_ptr<MoveValidator>> _moveVaridators;
    int _movedAmount;
public:
    Piece(Color color);
    bool canMakeMove(Board& board, Move move) const;
    void addMoveValidator(std::shared_ptr<MoveValidator> moveValidator);
    bool isAllyPiece(std::shared_ptr<Piece> piece);
    void gotMoved();
    std::string getSymbol() const;
    Color getColor() const;
    int getMovedAmount() const;
};

class Pawn : public Piece
{
private:

public:
    Pawn(Color color);
};


class Rook : public Piece
{
private:

public:
    Rook(Color color);
};

class Knight : public Piece
{
private:

public:
    Knight(Color color);
};

class Bishop : public Piece
{
private:

public:
    Bishop(Color color);
};

class Queen : public Piece
{
private:

public:
    Queen(Color color);
};

class King : public Piece
{
private:

public:
    King(Color color);
};
