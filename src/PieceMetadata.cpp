#include "PieceMetadata.hpp"
#include <iostream>


bool PieceMetadata::CanPieceMove(Spot piece_spot, Color color)
{
    if(board_->IsSpotEmpty(piece_spot))
    {
        return false;
    }

    for(int f=0; f<BOARD_SIZE; f++)
    {
        for(int r=0; r<BOARD_SIZE; r++)
        {
            Spot end_spot(r, f);
            if(board_->GetPiece(piece_spot)->get_symbol()=="King")
            {
                if(IsMoveValid(Move(piece_spot, end_spot)) && IsSpotThreatened(color, end_spot).size()>0)
                {
                    return true;
                }
            }
            else if(IsMoveValid(Move(piece_spot, end_spot)))
            {
                return true;
            }
        }
    }

    return false;
};

std::vector<Spot> PieceMetadata::IsSpotThreatened(Color defendingcolor, Spot defending_spot)
{
    std::vector<Spot> ememy_spots;
    for(int f=0; f<BOARD_SIZE; f++)
    {
        for(int r=0; r<BOARD_SIZE; r++)
        {
            Spot enemy_spot(r, f);
            std::shared_ptr<Piece> enemyPiece = board_->GetPiece(enemy_spot);

            if(!board_->IsSpotEmpty(enemy_spot))
            {
                if(enemyPiece->get_color() == -defendingcolor && IsMoveValid(Move(enemy_spot, defending_spot))){
                    ememy_spots.push_back(enemy_spot);
                }
            }
        }
    }

    return ememy_spots;
};

bool PieceMetadata::IsMoveValid(Move move)
{
    std::shared_ptr<Piece> piece = board_->GetPiece(move.get_start());

    if(board_->IsSpotEmpty(move.get_start()))
    {
        std::cout << "!empty!" << std::endl;
        std::cout << (piece == nullptr) << std::endl;
        return false;
    }

    return piece->CanMakeMove(*board_, move);
};

Spot PieceMetadata::FindKingLocation(Color color)
{
    for(int f=0; f<BOARD_SIZE; f++)
    {
        for(int r=0; r<BOARD_SIZE; r++)
        {
            std::shared_ptr<Piece> temp = board_->GetPiece(Spot(r, f));

            if(temp != nullptr)
            {
                if(temp->get_symbol() == "King" && temp->get_color() == color)
                {
                    return Spot(r, f);
                }
            }
        }
    }

    return Spot();
};