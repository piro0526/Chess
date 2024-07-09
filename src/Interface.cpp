#include "Interface.hpp"

Color Interface::get_color()
{
    return color_;
};

std::string CUI::Input(std::string game_state)
{
    std::cout <<  game_state << std::endl;
    std::string input;
    std::cout <<  "input move" << std::endl;
    std::cin >> input;
    return input;
}

