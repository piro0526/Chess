#include "ChessGame.hpp"


ChessGame::ChessGame()
{

};

void ChessGame::init()
{
    _whitePlayer = Player(WHITE);
    _blackPlayer = Player(BLACK);
    _board = Board();
    metadata = PieceMetadata();
    _check.pushback(std::make_unique<Checkstate()>);
    _check.pushback(std::make_unique<CheckMateState()>);
    _check.pushback(std::make_unique<StaleMatestate()>);
    _stateChecker = std::make_unique<GameStateChecker()>;

    MoveHandler reg = std::make_unique<RegulerMoveHandler()>;
    MoveHandler enPassant = std::make_unique<EnPassantMoveHandler()>;
    MoveHandler promotion = std::make_unique<PromotionMoveHandler()>;
    MoveHandler castling = std::make_unique<CastlingMoveHandler()>;
    castling.setNext(promotion);
    castling.setNext(enPassant);
    castling.setNext(castling);
    _moveHandler = castling;

};

Move ChessGame::playTurn(Player player)
{
    
};

Move ChessGame::getPlayerInput(Player player)
{
    
};

Spot ChessGame::parseCoordinates(std::string strCoodinates)
{
    
};

void ChessGame::undo()
{
    
};

Player ChessGame::swapPlayer(Player cuurentPlayer)
{
    
};