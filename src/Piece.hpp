#pragma once
#include "Move.hpp"
#include <memory>
#include <string>
#include <vector>
#include <iostream>

typedef int Color;
static const Color BLACK = -1;
static const Color WHITE = 1;

class Board;
class MoveValidator;

class Piece
{
protected:
    std::string symbol_;
    Color color_;
    std::vector<std::shared_ptr<MoveValidator> > move_varidators_;
    int moved_amount_;
public:
    Piece(Color color);
    bool CanMakeMove(Board& board, Move move) const;
    void AddMoveValidator(std::unique_ptr<MoveValidator> moveValidator);
    bool IsAllyPiece(std::shared_ptr<Piece> piece);
    void GotMoved();
    std::string get_symbol() const;
    Color get_color() const;
    int get_moved_amount() const;
};

class Pawn : public Piece
{
public:
    Pawn(Color color);
};


class Rook : public Piece
{
public:
    Rook(Color color);
};

class Knight : public Piece
{
public:
    Knight(Color color);
};

class Bishop : public Piece
{
public:
    Bishop(Color color);
};

class Queen : public Piece
{
public:
    Queen(Color color);
};

class King : public Piece
{
public:
    King(Color color);
};
