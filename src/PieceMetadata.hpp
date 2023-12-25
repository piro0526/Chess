#pragma once
#include "Board.hpp"

class PieceMetadata
{
private:
    Board _board;
public:
    bool canPieceMove(Spot pieceSpot, Color color);
    bool isSpotThreatened(Color color, Spot defendingSpot);
    bool isMoveValid(Move move);
    Spot findKingLocation(Color color);
};