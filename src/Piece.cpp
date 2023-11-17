#include "Piece.hpp"


Piece::Piece()
{

};

bool Piece::canMakeMove(Board board, Move move) const
{
    for(const auto& moveValidator : _moveVaridators)
    {
        if(moveValidator.isMoveValid(board, move))
        {
            return ture;
        }
    }
};

void Piece::addMoveValidator(MoveValidator MoveValidator)
{

};

bool Piece::isAllyPiece(Piece piece)
{

};

void Piece::gotMoved()
{

};

std::string Piece::getSymbol() const
{

};
