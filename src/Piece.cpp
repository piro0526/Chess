#include "Piece.hpp"
#include "Board.hpp"
#include "MoveValidator.hpp"


Piece::Piece(Color color)
{
    _color = color;
};

bool Piece::canMakeMove(Board& board, Move move) const
{
    for(const auto& moveValidator : _moveVaridators)
    {
        if(moveValidator->isMoveValid(board, move))
        {
            return true;
        }
    }
    
    return false;
};

void Piece::addMoveValidator(std::unique_ptr<MoveValidator> moveValidator)
{
    _moveVaridators.emplace_back(std::move(moveValidator));
};

bool Piece::isAllyPiece(std::shared_ptr<Piece> piece)
{
    if(piece == nullptr)
    {
        return false;
    }
    return _color == piece->getColor();
};

void Piece::gotMoved()
{
    _movedAmount++;
};

std::string Piece::getSymbol() const
{
    return _symbol;
};

Color Piece::getColor() const
{
    return _color;
};

int Piece::getMovedAmount() const
{
    return _movedAmount;
}


Pawn::Pawn(Color color) : Piece(color)
{
    _symbol = "Pawn";
    addMoveValidator(std::move(std::make_unique<PawnMoveValidator>()));
};

Rook::Rook(Color color) : Piece(color)
{
    _symbol = "Rook";
    addMoveValidator(std::move(std::make_unique<HorizonalMoveValidator>()));
    addMoveValidator(std::move(std::make_unique<VerticalMoveValidator>()));
};

Knight::Knight(Color color) : Piece(color)
{
    _symbol = "Knight";
    addMoveValidator(std::move(std::make_unique<KightMoveValidator>()));
};

Bishop::Bishop(Color color) : Piece(color)
{
    _symbol = "Bishop";
    addMoveValidator(std::move(std::make_unique<DiagonalMoveValidator>()));
};

Queen::Queen(Color color) : Piece(color)
{
    _symbol = "Queen";
    addMoveValidator(std::move(std::make_unique<HorizonalMoveValidator>()));
    addMoveValidator(std::move(std::make_unique<DiagonalMoveValidator>()));
    addMoveValidator(std::move(std::make_unique<VerticalMoveValidator>()));
};

King::King(Color color) : Piece(color)
{
    _symbol = "King";
    addMoveValidator(std::move(std::make_unique<SingleMoveValidator>()));
};