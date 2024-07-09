#include "Board.hpp"
#include "Piece.hpp"

Board::Board()
{
    InitBoard();
};

void Board::InitBoard()
{
    PieceFactory fac;

    for(int i=0; i<BOARD_SIZE; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {
            SetPiece(nullptr, Spot(i,j));
        }
    }

    int index = 0;
    Rank r=BOARD_SIZE-1;
    File f=0;
    for(int i=0; i<configuretion_.length(); i++)
    {
        std::shared_ptr<Piece> piece;
        if(configuretion_[i] == 'p'){
            piece = fac.CreatePiece("Pawn", BLACK);
        }else if(configuretion_[i] == 'k'){
            piece = fac.CreatePiece("King", BLACK);
        }else if(configuretion_[i] == 'b'){
            piece = fac.CreatePiece("Bishop", BLACK);
        }else if(configuretion_[i] == 'n'){
            piece = fac.CreatePiece("Knight", BLACK);
        }else if(configuretion_[i] == 'r'){
            piece = fac.CreatePiece("Rook", BLACK);
        }else if(configuretion_[i] == 'q'){
            piece = fac.CreatePiece("Queen", BLACK);
        }else if(configuretion_[i] == 'P'){
            piece = fac.CreatePiece("Pawn", WHITE);
        }else if(configuretion_[i] == 'K'){
            piece = fac.CreatePiece("King", WHITE);
        }else if(configuretion_[i] == 'Q'){
            piece = fac.CreatePiece("Queen", WHITE);
        }else if(configuretion_[i] == 'B'){
            piece = fac.CreatePiece("Bishop", WHITE);
        }else if(configuretion_[i] == 'N'){
            piece = fac.CreatePiece("Knight", WHITE);
        }else if(configuretion_[i] == 'R'){
            piece = fac.CreatePiece("Rook", WHITE);
        }else if(configuretion_[i] == '/'){
            f = 0;
            r--;
            continue;
        }else if(std::isdigit(configuretion_[i])){
            f += int(configuretion_[i]-'0');
            continue;
        }

        SetPiece(piece, Spot(r,f));
        f++;
    }
};

bool Board::IsOutofRange(Move move) const
{
    return IsOutofRange(move.get_start()) || IsOutofRange(move.get_end());
};

bool Board::IsOutofRange(Spot spot) const
{
    return spot.get_file() < 0 || spot.get_file() >= BOARD_SIZE || spot.get_rank() < 0 || spot.get_rank() >= BOARD_SIZE;
};

bool Board::IsSpotEmpty(Spot spot) const
{
    return raw_board_[spot.get_rank()][spot.get_file()] == nullptr;
};

void Board::SetPiece(const std::shared_ptr<Piece>& piece, Spot spot)
{
    raw_board_[spot.get_rank()][spot.get_file()] = piece;
};

bool Board::MovePiece(Move move)
{
    if(IsOutofRange(move))
    {
        return false;
    };

    std::shared_ptr<Piece> piece = GetPiece(move.get_start());

    if(piece == nullptr)
    {
        return false;
    }

    if(!IsSpotEmpty(move.get_end()))
    {
        CapturePiece(GetPiece(move.get_end()));
        ResetTile(move.get_end());
    }
    SetPiece(piece, move.get_end());
    SetPiece(nullptr, move.get_start());

    return true;
};

void Board::CapturePiece(std::shared_ptr<Piece> piece)
{
    captured_pieces_.push_back(piece);
};

void Board::UnCapturePiece(std::shared_ptr<Piece> piece)
{
    std::remove(std::begin(captured_pieces_), std::end(captured_pieces_), piece);
};

void Board::ResetTile(Spot spot)
{
    raw_board_[spot.get_rank()][spot.get_file()] = nullptr;
};

std::shared_ptr<Piece> Board::GetPiece(Spot spot) const
{
    return raw_board_[spot.get_rank()][spot.get_file()];
};

std::shared_ptr<Piece> Board::PopPiece()
{
    std::shared_ptr<Piece> p = captured_pieces_.back();
    captured_pieces_.pop_back();
    return p;
}
