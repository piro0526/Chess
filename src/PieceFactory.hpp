#pragma once
#include "Piece.hpp"

class PieceFactory
{
public:
    Piece createPiece(std::string pieceType, Color color) const;
};