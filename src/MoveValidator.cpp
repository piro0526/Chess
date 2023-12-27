#include "MoveValidator.hpp"
#include "Board.hpp"


bool MoveValidator::isMoveValid(Board& board, Move move) const
{
    if(board.isOutofRange(move))
    {
        return false;
    };
    if(board.isSpotEmpty(move.getStart()))
    {
        return false;
    };
    if(board.getPiece(move.getStart())->isAllyPiece(board.getPiece(move.getEnd())))
    {
        return false;
    };

    return true;
}


bool DiagonalMoveValidator::isMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::isMoveValid(board, move))
    {
        return false;
    };
    
    Spot startSpot = move.getStart();
    Spot endSpot = move.getEnd();
    int rankDistance = move.getEnd().getRank()-move.getStart().getRank();
    int fileDistance = move.getEnd().getFile()-move.getStart().getFile();

    if(abs(rankDistance) != abs(fileDistance) || rankDistance == 0 || fileDistance == 0)
    {
        return false;
    }

    int rankDirection = rankDistance > 0 ? 1 : -1;
    int fileDirection = fileDistance > 0 ? 1 : -1;

    for(int i=1; i<abs(rankDistance); i++)
    {
        if(!board.isSpotEmpty(Spot(startSpot.getRank() + rankDirection*i, startSpot.getFile() + fileDirection*i)))
        {
            return false;
        }
    }

    return true;
};

bool HorizonalMoveValidator::isMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::isMoveValid(board, move))
    {
        return false;
    };
    
    Spot startSpot = move.getStart();
    Spot endSpot = move.getEnd();
    int rankDistance = move.getEnd().getRank()-move.getStart().getRank();
    int fileDistance = move.getEnd().getFile()-move.getStart().getFile();

    if(rankDistance == 0 || fileDistance != 0)
    {
        return false;
    }

    int rankDirection = rankDistance > 0 ? 1 : -1;

    for(int i=1; i<abs(rankDistance); i++)
    {
        if(!board.isSpotEmpty(Spot(startSpot.getRank() + rankDirection*i, startSpot.getFile())))
        {
            return false;
        }
    }

    return true;
};

bool VerticalMoveValidator::isMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::isMoveValid(board, move))
    {
        return false;
    };
    
    Spot startSpot = move.getStart();
    Spot endSpot = move.getEnd();
    int rankDistance = move.getEnd().getRank()-move.getStart().getRank();
    int fileDistance = move.getEnd().getFile()-move.getStart().getFile();

    if(rankDistance != 0 || fileDistance == 0)
    {
        return false;
    }

    int fileDirection = fileDistance > 0 ? 1 : -1;

    for(int i=1; i<abs(fileDistance); i++)
    {
        if(!board.isSpotEmpty(Spot(startSpot.getRank(), startSpot.getFile() + fileDirection*i)))
        {
            return false;
        }
    }

    return true;
};

bool PawnMoveValidator::isMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::isMoveValid(board, move))
    {
        return false;
    };
    
    Spot startSpot = move.getStart();
    Spot endSpot = move.getEnd();
    int rankDistance = move.getEnd().getRank()-move.getStart().getRank();
    int fileDistance = move.getEnd().getFile()-move.getStart().getFile();

    if(abs(fileDistance) == 1 || abs(fileDistance) == 2)
    {
        return false;
    }

    int side = board.getPiece(startSpot)->getColor();

    if(fileDistance == side && abs(rankDistance) == 1 && board.getPiece(endSpot))
    {
        return true;
    }
    if(fileDistance == side && rankDistance == 0 && !board.getPiece(endSpot))
    {
        return true;
    }
    if(fileDistance == side*2 && rankDistance == 0 && !board.getPiece(Spot(startSpot.getRank() + side, startSpot.getFile())) && board.getPiece(startSpot)->getMovedAmount()==0)
    {
        return true;
    }

    return false;
};

bool KightMoveValidator::isMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::isMoveValid(board, move))
    {
        return false;
    };
    
    Spot startSpot = move.getStart();
    Spot endSpot = move.getEnd();
    int rankDistance = move.getEnd().getRank()-move.getStart().getRank();
    int fileDistance = move.getEnd().getFile()-move.getStart().getFile();

    if(abs(rankDistance) + abs(fileDistance) != 3 || rankDistance == 0 || fileDistance == 0)
    {
        return false;
    }

    return true;
};

bool SingleMoveValidator::isMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::isMoveValid(board, move))
    {
        return false;
    };
    
    Spot startSpot = move.getStart();
    Spot endSpot = move.getEnd();
    int rankDistance = move.getEnd().getRank()-move.getStart().getRank();
    int fileDistance = move.getEnd().getFile()-move.getStart().getFile();

    if(abs(rankDistance) > 1 && abs(fileDistance) > 1)
    {
        return false;
    }

    return true;
};