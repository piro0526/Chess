#pragma once
#include "Move.hpp"
#include "PieceFactory.hpp"
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <algorithm>

static const int BOARD_SIZE = 8;

class Piece;
class MoveValidator;

class Board
{
protected:
    std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> raw_board_;
    std::string configuretion_ = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    std::vector<std::shared_ptr<Piece> >  captured_pieces_;
public:
    Board();
    void InitBoard();
    bool IsOutofRange(Move move) const;
    bool IsOutofRange(Spot spot) const;
    bool IsSpotEmpty(Spot spot) const;
    void SetPiece(const std::shared_ptr<Piece>& piece, Spot spot);
    bool MovePiece(Move move);
    void CapturePiece(std::shared_ptr<Piece> piece);
    void UnCapturePiece(std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> PopPiece();
    void ResetTile(Spot spot);
    std::shared_ptr<Piece> GetPiece(Spot spot) const;
};