#include "PieceFactory.hpp"

std::unique_ptr<Piece> PieceFactory::createPiece(std::string pieceType, Color color) const
{
    if(pieceType == "Pawn")
    {
        return std::make_unique<Pawn>(color);
    }
    else if(pieceType == "Rook")
    {
        return std::make_unique<Rook>(color);
    }
    else if(pieceType == "Knight")
    {
        return std::make_unique<Knight>(color);
    }
    else if(pieceType == "Bishop")
    {
        return std::make_unique<Bishop>(color);
    }
    else if(pieceType == "Queen")
    {
        return std::make_unique<Queen>(color);
    }
    else if(pieceType == "King")
    {
        return std::make_unique<King>(color);
    }
    else
    {
        return nullptr;
    }
};