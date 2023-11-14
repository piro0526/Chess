#pragma once
#include "Piece.hpp"
#include "Spot.hpp"
#include <string>
#include <vector>

static const int BOARD_SIZE = 8;

class Board
{
private:
    Piece _rawboard[BOARD_SIZE][BOARD_SIZE];
    std::string _configuration[BOARD_SIZE][BOARD_SIZE];
    int height;
    int width;
    std::vector<Piece>  _capturedPieces;

public:
    Board();
    void init();
    bool isOutofRange(Move move) const;
    bool isOutofRange(Spot spot) const;
    bool isSpotEmpty(Spot spot) const;
    void setPiece(Piece piece, Spot spot);
    void movePiece(Move move);
    void capturePiece(Piece piece);
    void unCapturedPiece(Piece piece);
    void resetTile(Spot spot);
    void viewBoard();
};