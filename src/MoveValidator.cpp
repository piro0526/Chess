#include "MoveValidator.hpp"
#include "Board.hpp"


bool MoveValidator::IsMoveValid(Board& board, Move move) const
{
    if(board.IsOutofRange(move))
    {
        return false;
    }

    if(board.IsSpotEmpty(move.get_start()))
    {
        return false;
    }

    if(board.GetPiece(move.get_start())->IsAllyPiece(board.GetPiece(move.get_end())))
    {
        return false;
    }

    return true;
}


bool DiagonalMoveValidator::IsMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::IsMoveValid(board, move))
    {
        return false;
    }

    Spot start_spot = move.get_start();
    Spot end_spot = move.get_end();
    int rankDistance = move.get_end().get_rank()-move.get_start().get_rank();
    int fileDistance = move.get_end().get_file()-move.get_start().get_file();

    if(abs(rankDistance) != abs(fileDistance) || rankDistance == 0 || fileDistance == 0)
    {
        return false;
    }

    int rankDirection = rankDistance > 0 ? 1 : -1;
    int fileDirection = fileDistance > 0 ? 1 : -1;

    for(int i=1; i<abs(rankDistance); i++)
    {
        if(!board.IsSpotEmpty(Spot(start_spot.get_rank() + rankDirection*i, start_spot.get_file() + fileDirection*i)))
        {
            return false;
        }
    }

    return true;
};

bool HorizonalMoveValidator::IsMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::IsMoveValid(board, move))
    {
        return false;
    }

    Spot start_spot = move.get_start();
    Spot end_spot = move.get_end();
    int rankDistance = move.get_end().get_rank()-move.get_start().get_rank();
    int fileDistance = move.get_end().get_file()-move.get_start().get_file();

    if(rankDistance == 0 || fileDistance != 0)
    {
        return false;
    }

    int rankDirection = rankDistance > 0 ? 1 : -1;

    for(int i=1; i<abs(rankDistance); i++)
    {
        if(!board.IsSpotEmpty(Spot(start_spot.get_rank() + rankDirection*i, start_spot.get_file())))
        {
            return false;
        }
    }

    return true;
};

bool VerticalMoveValidator::IsMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::IsMoveValid(board, move))
    {
        return false;
    }

    Spot start_spot = move.get_start();
    Spot end_spot = move.get_end();
    int rankDistance = move.get_end().get_rank()-move.get_start().get_rank();
    int fileDistance = move.get_end().get_file()-move.get_start().get_file();

    if(rankDistance != 0 || fileDistance == 0)
    {
        return false;
    }

    int fileDirection = fileDistance > 0 ? 1 : -1;

    for(int i=1; i<abs(fileDistance); i++)
    {
        if(!board.IsSpotEmpty(Spot(start_spot.get_rank(), start_spot.get_file() + fileDirection*i)))
        {
            return false;
        }
    }

    return true;
};

bool PawnMoveValidator::IsMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::IsMoveValid(board, move))
    {
        return false;
    }

    Spot start_spot = move.get_start();
    Spot end_spot = move.get_end();
    int rankDistance = end_spot.get_rank()-start_spot.get_rank();
    int fileDistance = end_spot.get_file()-start_spot.get_file();

    int side = board.GetPiece(start_spot)->get_color();


    if(rankDistance == side && std::abs(fileDistance) == 1 && !board.IsSpotEmpty(end_spot))
    {
        return true;
    }
    if(rankDistance == side && fileDistance == 0 && board.IsSpotEmpty(end_spot))
    {
        return true;
    }
    if(rankDistance == side*2 && fileDistance == 0 && board.IsSpotEmpty(Spot(start_spot.get_rank() + side, start_spot.get_file())) && board.GetPiece(start_spot)->get_moved_amount()==0)
    {
        return true;
    }
    return false;
};

bool KightMoveValidator::IsMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::IsMoveValid(board, move))
    {
        return false;
    }

    Spot start_spot = move.get_start();
    Spot end_spot = move.get_end();
    int rankDistance = move.get_end().get_rank()-move.get_start().get_rank();
    int fileDistance = move.get_end().get_file()-move.get_start().get_file();

    if(abs(rankDistance) + abs(fileDistance) != 3 || rankDistance == 0 || fileDistance == 0)
    {
        return false;
    }

    return true;
};

bool SingleMoveValidator::IsMoveValid(Board& board, Move move) const
{
    if(!MoveValidator::IsMoveValid(board, move))
    {
        return false;
    }

    Spot start_spot = move.get_start();
    Spot end_spot = move.get_end();
    int rankDistance = move.get_end().get_rank()-move.get_start().get_rank();
    int fileDistance = move.get_end().get_file()-move.get_start().get_file();

    if(abs(rankDistance) > 1 || abs(fileDistance) > 1)
    {
        return false;
    }

    return true;
};