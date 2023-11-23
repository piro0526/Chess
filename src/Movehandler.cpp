#include "Movehandler.hpp"

void MoveHandler::setNext(std::unique_ptr<MoveHandler> nextMoveHandler)
{
    _nextMoveHandler = std::move(nextMoveHandler);
};

bool CastlingMoveHandler::handleMove(Board& board, PieceMetadata metadata, Move move)
{
    if(isCastlingMove(metadata, move))
    {
        int rank = move.getStart().getRank();
        int file = move.getStart().getFile();
        int yDistance = move.getStart().getFile() - move.getEnd().getFile();
        int direction = yDistance < 0 ? 1 : -1;
        Move rookMove(move.getEnd(), Spot(rank, file + direction));
        Move kingMove(move.getEnd(), Spot(rank, file + 3 * direction));
        board.movePiece(rookMove);
        board.movePiece(kingMove);

        return true;
    }
    if(_nextMoveHandler != nullptr)
    {
        return _nextMoveHandler->handleMove(board, metadata, move);
    }
    else
    {
        return false;
    }
};

bool CastlingMoveHandler::isCastlingMove(PieceMetadata metadata, Move move)
{

};

bool EnPassantMoveHandler::handleMove(Board& board, PieceMetadata metadata, Move move)
{

};

bool EnPassantMoveHandler::isEnPassantMove(PieceMetadata metadata, Move move)
{

};

bool PromotionMoveHandler::handleMove(Board& board, PieceMetadata metadata, Move move)
{

};

bool PromotionMoveHandler::isPromotionMove(PieceMetadata metadata, Move move)
{

};

bool RegularMoveHandler::handleMove(Board& board, PieceMetadata metadata, Move move)
{

};

bool RegularMoveHandler::isRegularMove(PieceMetadata metadata, Move move)
{

};