#pragma once
#include "Board.hpp"

class PieceMetadata
{
private:
    std::unique_ptr<Board> _board;
public:
    PieceMetadata(){};
    PieceMetadata(Board *board):_board(board){};
    bool canPieceMove(Spot pieceSpot, Color color);
    bool isSpotThreatened(Color color, Spot defendingSpot);
    bool isMoveValid(Move move);
    Spot findKingLocation(Color color);
};