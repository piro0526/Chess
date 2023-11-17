#pragma once
#include "Piece.hpp"

class PieceFactory
{
public:
    std::unique_ptr<Piece> createPiece(std::string pieceType, Color color) const;
};