#pragma once
#include "Piece.hpp"
#include "Spot.hpp"
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <algorithm>

static const int BOARD_SIZE = 8;

class Board
{
private:
    std::array<std::array<std::unique_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> _rawBoard;
    std::array<std::array<std::string, BOARD_SIZE>, BOARD_SIZE> _configuretion;
    std::vector<std::unique_ptr<Piece>>  _capturedPieces;

public:
    Board();
    void init();
    bool isOutofRange(Move move) const;
    bool isOutofRange(Spot spot) const;
    bool isSpotEmpty(Spot spot) const;
    void setPiece(std::unique_ptr<Piece> piece, Spot spot);
    bool movePiece(Move move);
    void capturePiece(std::unique_ptr<Piece> piece);
    void unCapturePiece(std::unique_ptr<Piece> piece);
    void resetTile(Spot spot);
    void viewBoard();
    std::unique_ptr<Piece> getPiece(Spot spot) const;
};