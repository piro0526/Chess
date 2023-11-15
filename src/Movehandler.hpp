#pragma once
#include "Board.hpp"

class IMoveHandler
{
public:
    virtual void setNext(IMoveHandler nextMoveHandler);
    virtual bool handleMove(Board board, PieceMetadata metadata, Move move);
};

class MoveHandler : IMoveHandler
{
protected:
    IMoveHandler _nextMoveHandler;
public:
    void setNext(IMoveHandler nextMoveHandler);
};

class CastlingMoveHandler : MoveHandler
{
public:
    bool handleMove(Board board, PieceMetadata metadata, Move move);
    bool isCastlingMove(Board board, Move move);

};

class EnPassantMoveHandler : MoveHandler
{
public:
    bool handleMove(Board board, PieceMetadata metadata, Move move);
    bool isEnPassantMove(Board board, Move move);
};

class PromotionMoveHandler : MoveHandler
{
public:
    bool handleMove(Board board, PieceMetadata metadata, Move move);
    bool isPromotionMove(Board board, Move move);
};

class RegularMoveHandler : MoveHandler
{
public:
    bool handleMove(Board board, PieceMetadata metadata, Move move);
};