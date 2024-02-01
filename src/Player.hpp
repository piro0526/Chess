#pragma once
#include "Piece.hpp"
#include <iostream>
#include <map>

class Player
{
private:
    Color _color;
public:
    Player() : Player(WHITE){};
    Player(Color color): _color(color){};
    virtual std::string getPlayerInput(std::map<std::string, std::string> message){return "";};
    Color getColor();
};

class stdinPlayer : public Player
{
public:
    stdinPlayer(Color color): Player(color){};
    std::string getPlayerInput(std::map<std::string, std::string> message);
};