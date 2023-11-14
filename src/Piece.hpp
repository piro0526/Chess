#pragma once
#include "Board.hpp"

typedef int Color;
static const Color BLACK = -1;
static const Color WHITE = 1;

class Piece
{
private:
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
};