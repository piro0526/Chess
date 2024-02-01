#include "MoveHandler.hpp"

void MoveHandler::setNext(std::unique_ptr<IMoveHandler> nextMoveHandler)
{
    _nextMoveHandler = std::move(nextMoveHandler);
};

bool CastlingMoveHandler::handleMove(Board& board, PieceMetadata& metadata, Move move)
{
    if(isCastlingMove(board, metadata, move))
    {
        Rank rank = move.getStart().getRank();
        File file = move.getStart().getFile();
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

    
    return false;
};

bool CastlingMoveHandler::isCastlingMove(Board& board, PieceMetadata& metadata, Move move)
{
    Spot startSpot = move.getStart();
    Spot endSpot = move.getEnd();
    if(board.isSpotEmpty(endSpot))
    {
        return false;
    }
    std::shared_ptr<Piece> piece1 = board.getPiece(startSpot);
    std::shared_ptr<Piece> piece2 = board.getPiece(endSpot);

    if(piece1->getSymbol() != "King" || piece2->getSymbol() != "Rook" || piece1->getMovedAmount() > 0 || piece2->getMovedAmount() > 0 || piece1->getColor() == piece2->getColor())
    {
        return false;
    }

    int yDistance = endSpot.getFile() - startSpot.getFile();
    int direction = yDistance > 0 ? 1 : -1;

    for(int i=0; i<4; i++)
    {
        Rank rank = startSpot.getRank();
        File file = startSpot.getFile() + 1 * direction;
        if(metadata.isSpotThreatened(piece1->getColor(), Spot(rank, file)) || (!board.isSpotEmpty(Spot(rank, file)) && file != startSpot.getFile() && file != endSpot.getFile()))
        {
            return false;
        }
    }

    return true;
};

bool EnPassantMoveHandler::handleMove(Board& board, PieceMetadata& metadata, Move move)
{
    if(isEnPassantMove(board, move))
    {
        board.movePiece(move);
        Rank rank = move.getStart().getRank();
        File file = move.getEnd().getFile();
        board.resetTile(Spot(rank, file));

        return true;
    }
    if(_nextMoveHandler != nullptr)
    {
        return _nextMoveHandler->handleMove(board, metadata, move);
    }


    
    return false;
};

bool EnPassantMoveHandler::isEnPassantMove(Board& board, Move move)
{    
    Spot startSpot = move.getStart();
    Spot endSpot = move.getEnd();
    if (board.isOutofRange(move) || !(board.getPiece(startSpot)->getSymbol() == "Pawn"))
    {
        return false;
    }
    std::shared_ptr<Piece> pawn = board.getPiece(startSpot);

    int xDistance = endSpot.getRank() - startSpot.getRank();
    int yDistance = endSpot.getFile() - startSpot.getFile();

    int side = pawn->getColor() == WHITE ? -1 : 1;
    
    if(xDistance != side || abs(yDistance) != 1 || !board.isSpotEmpty(endSpot))
    {
        return false;
    }

    if(board.isOutofRange(move))
    {
        return false;
    }

    std::shared_ptr<Piece> enemyPawn = board.getPiece(Spot(startSpot.getRank(), endSpot.getFile()));

    if(!(enemyPawn->getSymbol() == "Pawn") || pawn->isAllyPiece(enemyPawn) || enemyPawn->getMovedAmount() != 1)
    {
        return false;
    }

    return true;
}

bool PromotionMoveHandler::handleMove(Board& board, PieceMetadata& metadata, Move move)
{
    if(isPromotionMove(board, metadata, move))
    {
        return true;
    }
    if(_nextMoveHandler != nullptr)
    {
        return _nextMoveHandler->handleMove(board, metadata, move);
    }
    
    return false;
};

bool PromotionMoveHandler::isPromotionMove(Board& board, PieceMetadata& metadata, Move move)
{
    if(!metadata.isMoveValid(move))
    {
        return false;
    }

    Spot startSpot = move.getStart();
    Spot endSpot = move.getEnd();
    std::shared_ptr<Piece> piece = board.getPiece(startSpot);

    if(!(piece->getSymbol() == "Pawn"))
    {
        return false;
    }

    int edge = piece->getColor() == WHITE ? 0 : BOARD_SIZE - 1;

    return endSpot.getFile() == edge;
};

bool RegularMoveHandler::handleMove(Board& board, PieceMetadata& metadata, Move move)
{
    
    if (metadata.isMoveValid(move) && !board.getPiece(move.getStart())->isAllyPiece(board.getPiece(move.getEnd())))
    {
        board.movePiece(move);
        return true;
    }
    if (_nextMoveHandler != nullptr)
    {
        return _nextMoveHandler->handleMove(board, metadata, move);
    }

    return false;
};