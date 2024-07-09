#pragma once
#include "Piece.hpp"
#include "Action.hpp"
#include <iostream>
#include <map>

class Interface
{
protected:
    Color color_;
public:
    Interface(Color color): color_(color){};
    virtual ~Interface(){};
    Color get_color();
    virtual std::string Input(std::string) = 0;
};

class CUI : public Interface
{
public:
    CUI(Color color): Interface(color){};
    std::string Input(std::string);
};