#pragma once
#include "Piece.hpp"
#include <memory>

class PieceFactory
{
public:
    std::unique_ptr<Piece> createPiece(std::string pieceType, Color color) const;
};