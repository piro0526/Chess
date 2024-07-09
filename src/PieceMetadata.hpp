#pragma once
#include "Board.hpp"

class PieceMetadata
{
protected:
    Board *board_;
public:
    PieceMetadata(){};
    PieceMetadata(Board *board):board_(board){};
    bool CanPieceMove(Spot piece_spot, Color color);
    std::vector<Spot> IsSpotThreatened(Color color, Spot defending_spot);
    bool IsMoveValid(Move move);
    Spot FindKingLocation(Color color);
};