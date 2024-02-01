#include "ChessGame.hpp"

int main()
{
    std::unique_ptr<Player> black = std::make_unique<stdinPlayer>(-1);
    std::unique_ptr<Player> white = std::make_unique<stdinPlayer>(1);
    ChessGame game(std::move(white), std::move(black));
    game.start();

    return 0;
}