#pragma once
#include "Piece.hpp"
#include <memory>

class PieceFactory
{
public:
    std::unique_ptr<Piece> CreatePiece(std::string piece_type, Color color) const;
};