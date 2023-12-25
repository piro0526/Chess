#include "PieceMetadata.hpp"


bool PieceMetadata::canPieceMove(Spot pieceSpot, Color color)
{
    if(_board.isSpotEmpty(pieceSpot))
    {
        return false;
    }

    for(int f=0; f<BOARD_SIZE; f++)
    {
        for(int r=0; r<BOARD_SIZE; r++)
        {
            Spot endSpot(r, f);
            if(_board.getPiece(pieceSpot)->getSymbol()=="King")
            {
                if(isMoveValid(Move(pieceSpot, endSpot)) && !isSpotThreatened(color, endSpot))
                {
                    return true;
                }
            }
            else if(isMoveValid(Move(pieceSpot, endSpot)))
            {
                return true;
            }
        }
    }
    
    return false;
};

bool PieceMetadata::isSpotThreatened(Color defendingcolor, Spot defendingSpot)
{
    for(int f=0; f<BOARD_SIZE; f++)
    {
        for(int r=0; r<BOARD_SIZE; r++)
        {
            Spot enemySpot(r, f);
            std::shared_ptr<Piece> enemyPiece = _board.getPiece(enemySpot);

            if(!_board.isSpotEmpty(enemySpot) && enemyPiece->getColor() == -defendingcolor && isMoveValid(Move(enemySpot, defendingSpot)))
            {
                return true;
            }
        }
    }

    return false;
};

bool PieceMetadata::isMoveValid(Move move)
{
    std::shared_ptr<Piece> piece = _board.getPiece(move.getStart());

    if(_board.isSpotEmpty(move.getStart()))
    {
        return false;
    }

    return piece->canMakeMove(_board, move);
};

Spot PieceMetadata::findKingLocation(Color color)
{
    for(int f=0; f<BOARD_SIZE; f++)
    {
        for(int r=0; r<BOARD_SIZE; r++)
        {
            std::shared_ptr<Piece> temp = _board.getPiece(Spot(r, f));

            if(temp->getSymbol() == "King" && temp->getColor() == color)
            {
                return Spot(r, f);
            }
        }
    }

    return ;
};