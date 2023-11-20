#pragma once
#include "MoveValidator.hpp"
#include <memory>

class MoveValidatorFactory
{
public:
    std::unique_ptr<MoveValidator> createMoveValidator(std::string validatorType) const;
};