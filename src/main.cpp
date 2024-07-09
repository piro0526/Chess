#include "ChessGame.hpp"

int main()
{
    auto black = std::make_unique<CUI>(-1);
    auto white = std::make_unique<CUI>(1);
    ChessGame game(std::move(white), std::move(black));
    game.Start();

    return 0;
}