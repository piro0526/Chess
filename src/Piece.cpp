#include "Piece.hpp"
#include "Board.hpp"
#include "MoveValidator.hpp"


Piece::Piece(Color color)
{
    color_ = color;
};

bool Piece::CanMakeMove(Board& board, Move move) const
{
    for(const auto& moveValidator : move_varidators_)
    {
        if(moveValidator->IsMoveValid(board, move))
        {
            return true;
        }
    }
    return false;
};

void Piece::AddMoveValidator(std::unique_ptr<MoveValidator> moveValidator)
{
    move_varidators_.emplace_back(std::move(moveValidator));
};

bool Piece::IsAllyPiece(std::shared_ptr<Piece> piece)
{
    if(piece == nullptr)
    {
        return false;
    }
    return color_ == piece->get_color();
};

void Piece::GotMoved()
{
    moved_amount_++;
};

std::string Piece::get_symbol() const
{
    return symbol_;
};

Color Piece::get_color() const
{
    return color_;
};

int Piece::get_moved_amount() const
{
    return moved_amount_;
}


Pawn::Pawn(Color color) : Piece(color)
{
    symbol_ = "Pawn";
    AddMoveValidator(std::move(std::make_unique<PawnMoveValidator>()));
};

Rook::Rook(Color color) : Piece(color)
{
    symbol_ = "Rook";
    AddMoveValidator(std::move(std::make_unique<HorizonalMoveValidator>()));
    AddMoveValidator(std::move(std::make_unique<VerticalMoveValidator>()));
};

Knight::Knight(Color color) : Piece(color)
{
    symbol_ = "Knight";
    AddMoveValidator(std::move(std::make_unique<KightMoveValidator>()));
};

Bishop::Bishop(Color color) : Piece(color)
{
    symbol_ = "Bishop";
    AddMoveValidator(std::move(std::make_unique<DiagonalMoveValidator>()));
};

Queen::Queen(Color color) : Piece(color)
{
    symbol_ = "Queen";
    AddMoveValidator(std::move(std::make_unique<HorizonalMoveValidator>()));
    AddMoveValidator(std::move(std::make_unique<DiagonalMoveValidator>()));
    AddMoveValidator(std::move(std::make_unique<VerticalMoveValidator>()));
};

King::King(Color color) : Piece(color)
{
    symbol_ = "King";
    AddMoveValidator(std::move(std::make_unique<SingleMoveValidator>()));
};