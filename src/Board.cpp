#include "Board.hpp"

Board::Board()
{

};

void Board::init()
{
    
};

bool Board::isOutofRange(Move move) const
{
    if(move.getEnd().getFile() < 0 || move.getEnd().getFile() >= BOARD_SIZE)
    {
        return true;
    }
    
    if(move.getEnd().getRank() < 0 || move.getEnd().getRank() >= BOARD_SIZE)
    {
        return true;
    }

    return false;
};

bool Board::isOutofRange(Spot spot) const
{
    if(spot.getFile() < 0 || spot.getFile() >= BOARD_SIZE)
    {
        return true;
    }
    
    if(spot.getRank() < 0 || spot.getRank() >= BOARD_SIZE)
    {
        return true;
    }

    return false;
};

bool Board::isSpotEmpty(Spot spot) const
{
    if(_rawboard[spot.getRank()][spot.getFile()].getSymbol() == "EMPTY")
    {
        return true;
    };
};

void Board::setPiece(Piece piece, Spot spot)
{
    _rawboard[spot.getRank()][spot.getFile()] = piece;
};

void Board::movePiece(Move move)
{
    if(_rawboard[spot.getRank()][spot.getFile()].getSymbol() == "EMPTY")
    {
        
    };
};

void Board::capturePiece(Piece piece)
{

};

void Board::unCapturePiece(Piece piece)
{

};

void Board::resetTile(Spot spot)
{

};

void Board::viewBoard()
{

};