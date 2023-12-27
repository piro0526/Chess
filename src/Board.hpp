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
private:
    std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> _rawBoard;
    std::array<std::array<std::string, BOARD_SIZE>, 2> _configuretion = {{
        {"Pawn", "Pawn", "Pawn", "Pawn", "Pawn", "Pawn", "Pawn", "Pawn"},
        {"Rook", "Knight", "Bishop", "Queen", "King", "Bishop", "Knight", "Rook"}
        }};
    std::vector<std::shared_ptr<Piece>>  _capturedPieces;
    std::vector<std::tuple<Move, std::shared_ptr<Piece>, std::shared_ptr<Piece>>> _history;
    int _turns;
public:
    Board();
    void initBoard();
    bool isOutofRange(Move move) const;
    bool isOutofRange(Spot spot) const;
    bool isSpotEmpty(Spot spot) const;
    void setPiece(std::shared_ptr<Piece> piece, Spot spot);
    bool movePiece(Move move);
    void capturePiece(std::shared_ptr<Piece> piece);
    void unCapturePiece(std::shared_ptr<Piece> piece);
    void resetTile(Spot spot);
    void viewBoard();
    std::shared_ptr<Piece> getPiece(Spot spot) const;
    int getTurn() const;
    std::string getFEN() const;
};