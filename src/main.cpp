#include "ChessGame.hpp"

int main()
{
    std::unique_ptr<Player> black = std::make_unique<stdinPlayer>(BLACK);
    std::unique_ptr<Player> white = std::make_unique<stdinPlayer>(WHITE);
    ChessGame game(std::move(white), std::move(black));
    game.start();

    return 0;
}