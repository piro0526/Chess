#pragma once
#include "Board.hpp"

class IMoveHandler
{
public:
    virtual void setNext(IMoveHandler nextMoveHandler);
    virtual bool handleMove(Board board, PieceMetadata metadata, Move move);
};

class MoveHandler
{
public:
    void setNext(IMoveHandler nextMoveHandler);
};

