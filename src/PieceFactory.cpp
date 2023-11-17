#include "PieceFactory.hpp"

std::unique_ptr<Piece> PieceFactory::createPiece(std::string pieceType, Color color) const
{
    if(pieceType == "Pawn")
    {
        return std::unique_ptr<Piece>(new Pawn(color));
    }
    else if(pieceType == "Rook")
    {
        return std::unique_ptr<Piece>(new Rook(color));
    }
    else if(pieceType == "Knight")
    {
        return std::unique_ptr<Piece>(new Knight(color));
    }
    else if(pieceType == "Bishop")
    {
        return std::unique_ptr<Piece>(new Bishop(color));
    }
    else if(pieceType == "Queen")
    {
        return std::unique_ptr<Piece>(new Queen(color));
    }
    else if(pieceType == "King")
    {
        return std::unique_ptr<Piece>(new King(color));
    }
    else
    {
        return nullptr;
    }
};