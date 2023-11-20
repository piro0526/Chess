#include "MoveValidatorFactory.hpp"

std::unique_ptr<MoveValidator> MoveValidatorFactory::createMoveValidator(std::string validatorType) const
{
    if(validatorType == "Diagonal")
    {
        return std::unique_ptr<MoveValidator>(new DiagonalMoveValidator());
    }
    else if(validatorType == "Horizonal")
    {
        return std::unique_ptr<MoveValidator>(new HorizonalMoveValidator());
    }
    else if(validatorType == "Vertical")
    {
        return std::unique_ptr<MoveValidator>(new VerticalMoveValidator());
    }
    else if(validatorType == "Pawn")
    {
        return std::unique_ptr<MoveValidator>(new PawnMoveValidator());
    }
    else if(validatorType == "Kight")
    {
        return std::unique_ptr<MoveValidator>(new KightMoveValidator());
    }
    else if(validatorType == "Single")
    {
        return std::unique_ptr<MoveValidator>(new SingleMoveValidator());
    }
    else
    {
        return nullptr;
    }
};