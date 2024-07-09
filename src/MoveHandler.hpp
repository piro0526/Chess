#pragma once
#include "Board.hpp"
#include "Action.hpp"
#include "PieceMetadata.hpp"
#include <iostream>

class IMoveHandler
{
public:
    virtual ~IMoveHandler(){};
    virtual void SetNext(const std::shared_ptr<IMoveHandler>& next_move_handler)=0;
    virtual int HandleMove(Board& board, PieceMetadata& metadata, Action action)=0;
};

class MoveHandler : public IMoveHandler
{
protected:
    std::shared_ptr<IMoveHandler> next_move_handler_;
public:
    void SetNext(const std::shared_ptr<IMoveHandler>& next_move_handler);
};

class CastlingMoveHandler : public MoveHandler
{
public:
    int HandleMove(Board& board, PieceMetadata& metadata, Action action);
    bool IsCastlingMove(Board& board, PieceMetadata& metadata, Move move);

};

class EnPassantMoveHandler : public MoveHandler
{
public:
    int HandleMove(Board& board, PieceMetadata& metadata, Action action);
    bool IsEnPassantMove(Board& board, Move move);
};

class PromotionMoveHandler : public MoveHandler
{
public:
    int HandleMove(Board& board, PieceMetadata& metadata, Action action);
    bool IsPromotionMove(Board& board, PieceMetadata& metadata, Move move);
};

class RegularMoveHandler : public MoveHandler
{
public:
    int HandleMove(Board& board, PieceMetadata& metadata, Action action);
};