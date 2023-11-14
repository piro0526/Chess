


class MoveValidator
{
private:

public:
    virtual bool isMoveValid(Board board);
};

class DiagonalMoveValidator : MoveValidator
{
public:
};

class HorizonalMoveValidator : MoveValidator
{
public:
};

class VerticalMoveValidator : MoveValidator
{
public:
};

class PawnMoveValidator : MoveValidator
{
public:
};

class KightMoveValidator : MoveValidator
{
public:
};

class SingleMoveValidator : MoveValidator
{
public:
};