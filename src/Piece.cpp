#include "Piece.hpp"


Piece::Piece(Color color)
{
    _color = color;
};

bool Piece::canMakeMove(Board board, Move move) const
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

void Piece::addMoveValidator(std::shared_ptr<MoveValidator> moveValidator)
{
    _moveVaridators.push_back(moveValidator);
};

bool Piece::isAllyPiece(std::shared_ptr<Piece> piece)
{
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

bool Piece::hasBeenMoved() const
{
    return !_movedAmount;
};


Pawn::Pawn(Color color) : Piece(color)
{
    addMoveValidator(std::make_unique<PawnMoveValidator>());
};

Rook::Rook(Color color) : Piece(color)
{
    addMoveValidator(std::make_unique<HorizonalMoveValidator>());
    addMoveValidator(std::make_unique<VerticalMoveValidator>());
};

Knight::Knight(Color color) : Piece(color)
{
    addMoveValidator(std::make_unique<KightMoveValidator>());
};

Bishop::Bishop(Color color) : Piece(color)
{
    addMoveValidator(std::make_unique<DiagonalMoveValidator>());
};

Queen::Queen(Color color) : Piece(color)
{
    addMoveValidator(std::make_unique<HorizonalMoveValidator>());
    addMoveValidator(std::make_unique<DiagonalMoveValidator>());
    addMoveValidator(std::make_unique<VerticalMoveValidator>());
};

King::King(Color color) : Piece(color)
{
    addMoveValidator(std::make_unique<SingleMoveValidator>());
};