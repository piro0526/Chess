#include "ChessGame.hpp"


ChessGame::ChessGame()
{
    _whitePlayer = stdinPlayer(WHITE);
    _blackPlayer = stdinPlayer(BLACK);
    init();
};

ChessGame::ChessGame(Player whitePlayer, Player blackPlayer)
{
    _whitePlayer = whitePlayer;
    _blackPlayer = blackPlayer;
    init();
};

void ChessGame::init()
{
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
    Player _currentPlayer = _whitePlayer;
    StateInfo gameState(0, "");

    while(gameState.getStateCode() <= 1)
    {
        viewBoard();
        playTurn(currentPlayer);
        gameState = _stateChecker.checkState(metadata, swapPlayers(currentPlayer).getColor());
        if(gameState.getStateCode() != 0)
        {
            std::cout << gameState.getStateDescription() << std::endl;
        }
        currentPlayer = swapPlayers(currentPlayer);
        if(gameState.getStateCode() == 2)
        {
            viewBoard();
        }
    }
};

void ChessGame::playTurn(Player player)
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
            undo(move, startPiece, endPiece);
            playturn(player);
        }
    }
};

Move ChessGame::getPlayerInput(Player player)
{
    return player.nextMove(_board.getFEN());
};

Spot ChessGame::parseCoordinates(std::string strCoodinates)
{
    int x = int(strCoodinates[0]) - int("a");
    int y = int(strCoodinates[1]);
    return Spot(x, y);
};

void ChessGame::undo()
{
    _board.undo();
};

Player ChessGame::swapPlayer(Player player)
{
    if(player.getColor() == WHITE)
    {
        return _blackPlayer;
    }
    else
    {
        return _whitePlayer;
    }
};