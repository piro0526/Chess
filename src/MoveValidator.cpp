#include "MoveValidator.hpp"


bool DiagonalMoveValidator::isMoveValid(Board board, Move move) const
{
    if(board.isOutofRange(move)){return false;};
    
    int rank_dist = move.getEnd().getRank()-move.getStart().getRank();
    int file_dist = move.getEnd().getFile()-move.getStart().getFile();

    if(abs(move.getEnd().getRank()-move.getStart().getRank()) == abs(move.getEnd().getFile()-move.getStart().getFile()))
    {
        return false;
    }

    for(int i=1; i<rank_dist; i++)
    {
        if()
        {

        }
    }

    return abs(move.getEnd().getRank()-move.getStart().getRank()) == abs(move.getEnd().getFile()-move.getStart().getFile());
};

bool HorizonalMoveValidator::isMoveValid(Board board, Move move) const
{
    if(board.isOutofRange(move)){return false;};
    
    return move.getEnd().getFile() == move.getStart().getFile();
};

bool VerticalMoveValidator::isMoveValid(Board board, Move move) const
{
    if(board.isOutofRange(move)){return false;};
    
    return move.getEnd().getRank() == move.getStart().getRank();
};

bool PawnMoveValidator::isMoveValid(Board board, Move move) const
{
    if(board.isOutofRange(move)){return false;};
    

};

bool KightMoveValidator::isMoveValid(Board board, Move move) const
{
    if(board.isOutofRange(move)){return false;};
    

};

bool SingleMoveValidator::isMoveValid(Board board, Move move) const
{
    if(board.isOutofRange(move)){return false;};
    

};