#include "Player.hpp"

Color Player::getColor()
{
    return _color;
};

std::string stdinPlayer::getPlayerInput(std::map<std::string, std::string> message)
{
    if(message["errorMessage"] != "")
    {
        std::cout << message["errorMessage"] << std::endl;
    }
    std::cout << message["FEN"] << std::endl;
    std::string input;
    getline(std::cin, input);
    
    return input;
}

