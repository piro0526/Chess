#include "ChessGame.hpp"


ChessGame::ChessGame()
{
    _whitePlayer = std::make_shared<stdinPlayer>(WHITE);
    _blackPlayer = std::make_shared<stdinPlayer>(BLACK);
    init();
};

ChessGame::ChessGame(std::unique_ptr<Player> whitePlayer, std::unique_ptr<Player> blackPlayer)
{
    _whitePlayer = std::move(whitePlayer);
    _blackPlayer = std::move(blackPlayer);
    init();
};

void ChessGame::init()
{
    _board = Board();
    _metadata = PieceMetadata();
    std::vector<std::unique_ptr<GameStateCheck>> checks;
    checks.push_back(std::move(std::make_unique<CheckState>()));
    checks.push_back(std::move(std::make_unique<CheckMateState>()));
    checks.push_back(std::move(std::make_unique<StaleMateState>()));
    _stateChecker = std::move(std::make_unique<GameStateChecker>(checks));

    std::unique_ptr<MoveHandler> reg = std::make_unique<RegularMoveHandler>();
    std::unique_ptr<MoveHandler> enPassant = std::make_unique<EnPassantMoveHandler>();
    std::unique_ptr<MoveHandler> promotion = std::make_unique<PromotionMoveHandler>();
    std::unique_ptr<MoveHandler> castling = std::make_unique<CastlingMoveHandler>();
    castling->setNext(std::move(promotion));
    promotion->setNext(std::move(enPassant));
    enPassant->setNext(std::move(reg));
    _moveHandler = std::move(castling);
};

void ChessGame::start()
{
    std::shared_ptr<Player> _currentPlayer = _whitePlayer;
    StateInfo gameState(0, "");

    while(gameState.getStateCode() <= 1)
    {
        playTurn(_currentPlayer);
        gameState = _stateChecker->checkState(_board, _metadata, swapPlayer(_currentPlayer)->getColor());
        if(gameState.getStateCode() != 0)
        {
            std::cout << gameState.getStateDescription() << std::endl;
        }
        _currentPlayer = swapPlayer(_currentPlayer);
        if(gameState.getStateCode() == 2)
        {
            std::cout << "GG" << std::endl;
            //viewBoard();
        }
    }
};

void ChessGame::playTurn(std::shared_ptr<Player> player)
{
    Move move = getPlayerInput(player);
    Spot startSpot = move.getStart();
    std::shared_ptr<Piece> startPiece = _board.getPiece(move.getStart());
    std::shared_ptr<Piece> endPiece = _board.getPiece(move.getEnd());
    
    if(_board.isSpotEmpty(startSpot) || !_board.getPiece(startSpot)->getColor() == player->getColor() || !_moveHandler->handleMove(_board, _metadata, move))
    {
        playTurn(player);
    }
    else
    {
        StateInfo gameState = _stateChecker->checkIllegalStates(_board, _metadata, player->getColor());
        if(gameState.getStateCode() != 0)
        {
            undo(move, startPiece, endPiece);
            playTurn(player);
        }
    }
};

Move ChessGame::getPlayerInput(std::shared_ptr<Player> player)
{
    return player->nextMove(_board.getFEN());
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
            _board.unCapturePiece(endPiece);
        _board.setPiece(startPiece, move.getStart());
        _board.setPiece(endPiece, move.getEnd());
};

std::shared_ptr<Player> ChessGame::swapPlayer(std::shared_ptr<Player> player)
{
    if(player->getColor() == WHITE)
    {
        return _blackPlayer;
    }
    else
    {
        return _whitePlayer;
    }
};