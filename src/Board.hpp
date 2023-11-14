#include "Piece.hpp"


class Board
{
private:
    Piece _rawboard[BOARD_SIZE][BOARD_SIZE];
    std::string _configuration[][];
    int height;
    int width;
    std::vector<Piece> = _capturedPieces

public:
    Board();
    void init();
    bool isOutofRange(Move move);
    bool isOutofRange(Spot spot);
    setPiece(Piece piece, Spot spot);
}