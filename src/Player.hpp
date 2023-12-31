#pragma once
#include "Piece.hpp"

class Player
{
private:
    Color _color;
public:
    Player() : Player(WHITE){};
    Player(Color color): _color(color){};
    virtual Move nextMove(std::string FEN){return Move();};
    Color getColor();
};

class stdinPlayer : public Player
{
public:
    stdinPlayer(Color color): Player(color){};
    Move nextMove(std::string FEN);
};