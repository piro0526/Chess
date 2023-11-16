#include "Board.hpp"

Board::Board()
{

};

void Board::init()
{
    
};

bool Board::isOutofRange(Move move) const
{
    return isOutofRange(move.getStart()) || isOutofRange(move.getEnd());
};

bool Board::isOutofRange(Spot spot) const
{
    return spot.getFile() < 0 || spot.getFile() >= BOARD_SIZE || spot.getRank() < 0 || spot.getRank() >= BOARD_SIZE;
};

bool Board::isSpotEmpty(Spot spot) const
{
    return _rawBoard[spot.getRank()][spot.getFile()] == nullptr;
};

void Board::setPiece(std::unique_ptr<Piece> piece, Spot spot)
{
    _rawBoard[spot.getRank()][spot.getFile()] = piece;
};

bool Board::movePiece(Move move)
{
    if(isOutofRange(move))
    {
        return false;
    };

    std::unique_ptr<Piece> piece = getPiece(move.getStart());

    if(piece == nullptr)
    {
        return false;
    }

    if(!isSpotEmpty(move.getEnd()))
    {
        capturePiece(getPiece(move.getEnd()));
        resetTile(move.getEnd());
    }
    
    setPiece(piece, move.getEnd());

    return true;
};

void Board::capturePiece(std::unique_ptr<Piece> piece)
{
    _capturedPieces.push_back(piece);
};

void Board::unCapturePiece(std::unique_ptr<Piece> piece)
{
    std::remove(std::begin(_capturedPieces), std::end(_capturedPieces), piece);
};

void Board::resetTile(Spot spot)
{
    _rawBoard[spot.getRank()][spot.getFile()] = nullptr;
};

void Board::viewBoard()
{
    return;
};