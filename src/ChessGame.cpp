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

void ChessGame::start()
{

};

Move ChessGame::playTurn(Player player)
{
    Move move = getPlayerInput(player);
    Spot startSpot = move.getStart();
    Piece startPiece = *_board.getPiece(move.getStart());
    Piece endPiece = *_board.getPiece(move.getEnd());
    
    if(_board.isSpotEmpty(startSpot) || !_board.getPiece(startSpot)->getColor() == player.getColor() || !_moveHandler.handlemove(_metadata, move))
    {
        playTurn(player);
    }
    else
    {
        StateInfo gameState = stateChecker.checkIlleagalState(metadata, player.getColor());
        if(gameState.getStateCode() != 0)
        {
            undoMove(move, startPiece, endPiece);
            playturn(player);
        }
    }
};

Move ChessGame::getPlayerInput(Player player)
{
    return player.nextMove();
};

Spot ChessGame::parseCoordinates(std::string strCoodinates)
{
    int x = int(strCoodinates[0]) - int("a");
    int y = int(strCoodinates[1]);
    return Spot(x, y);
};

void ChessGame::undo(Move move, std::shared_ptr<Piece> startPiece, std::shared_ptr<Piece> endPiece)
{
    if (endPiece != nullptr)
    {
        _board.unCapturePiece(endPiece);
    }
    _board.setPiece(startPiece, move.getStart());
    _board.setPiece(endPiece, move.getEnd());
};