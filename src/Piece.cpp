#include "Piece.hpp"


Piece::Piece(Color color)
{
    _color = color;
};

bool Piece::canMakeMove(Board board, Move move) const
{
    for(const auto& moveValidator : _moveVaridators)
    {
        if(moveValidator.isMoveValid(board, move))
        {
            return true;
        }
    }
    
    return false;
};

void Piece::addMoveValidator(MoveValidator MoveValidator)
{
    _moveVaridators.push_back(MoveValidator);
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
    addMoveValidator()
};