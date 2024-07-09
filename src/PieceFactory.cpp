#include "PieceFactory.hpp"

std::unique_ptr<Piece> PieceFactory::CreatePiece(std::string piece_type, Color color) const
{
    if(piece_type == "Pawn")
    {
        return std::make_unique<Pawn>(color);
    }
    else if(piece_type == "Rook")
    {
        return std::make_unique<Rook>(color);
    }
    else if(piece_type == "Knight")
    {
        return std::make_unique<Knight>(color);
    }
    else if(piece_type == "Bishop")
    {
        return std::make_unique<Bishop>(color);
    }
    else if(piece_type == "Queen")
    {
        return std::make_unique<Queen>(color);
    }
    else if(piece_type == "King")
    {
        return std::make_unique<King>(color);
    }
    else
    {
        return nullptr;
    }
};