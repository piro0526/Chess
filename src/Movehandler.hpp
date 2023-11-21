#pragma once
#include "Board.hpp"

class IMoveHandler
{
public:
    virtual void setNext(std::unique_ptr<IMoveHandler> nextMoveHandler)=0;
    virtual bool handleMove(Board board, PieceMetadata metadata, Move move)=0;
};

class MoveHandler : public IMoveHandler
{
protected:
    std::unique_ptr<IMoveHandler> _nextMoveHandler;
public:
    void setNext(std::unique_ptr<IMoveHandler> nextMoveHandler);
};

class CastlingMoveHandler : public MoveHandler
{
public:
    bool handleMove(Board board, PieceMetadata metadata, Move move);
    bool isCastlingMove(Board board, Move move);

};

class EnPassantMoveHandler : public MoveHandler
{
public:
    bool handleMove(Board board, PieceMetadata metadata, Move move);
    bool isEnPassantMove(Board board, Move move);
};

class PromotionMoveHandler : public MoveHandler
{
public:
    bool handleMove(Board board, PieceMetadata metadata, Move move);
    bool isPromotionMove(Board board, Move move);
};

class RegularMoveHandler : public MoveHandler
{
public:
    bool handleMove(Board board, PieceMetadata metadata, Move move);
};